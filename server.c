#include "server.h"
#include "pipe_networking.h"
#include "client_server.h"
#include "semaphore.h"
#include "logins.h"
/*
WORKING:
–––––––––––
DESCRIPTION/NOTES


–––––––––––
ARGUMENTS


–––––––––––
RETURN VALUE


*/
//{
//  printf("err %d\n",errno);
//  printf("%s\n",strerror(errno));
//  exit(1);
//}




int create_server(){
  int f = fork();
  if (f == 0){
    listen_to_connections(10);
  }
  else{
    FILE * guest_storage = fopen("guest_storage.dat","w");
    fclose(guest_storage);
    FILE * key_storage = fopen("key_storage.dat","w");
    fclose(key_storage);
    FILE * pp_list = fopen("open_connections.txt","w");
    fclose(pp_list);
    
    create_semaphore();
    printf("server created\n");
  }
  
  
  
  //for now won't write anything in files, just create them
//  fwrite(&upstream,sizeof(int),1,key_storage);
//  int upstream = server_setup();
//  printf("%d\n",upstream);
  return f;
}

void close_server(int connector_pid){
  remove("guest_storage.dat");
  remove("key_storage.dat");
  kill(connector_pid, SIGKILL); //kills the loop waiting for connections
  char ** pp_list = (char **) calloc(sizeof(char*),100);
  pp_list = get_private_pipes();
  for (int i = 0;i<100;i++){
    char * pp = pp_list[i];
    if (pp != NULL){
      remove(pp);
    }
  }
  remove("open_connections.txt");
}






void open_screen(char * pp_name){
  char * usr = (char*) calloc(sizeof(char),64);
  char * passwd = (char*) calloc(sizeof(char),64);
  char * sign_log = (char*) calloc(sizeof(char),1);
  char * message = (char*) calloc(sizeof(char),200);
  int i = 0;
  while (i == 0){
    sprintf(message,"signing up (1) \nOR \nloggin in (2) ?\n");
//    printf("sending : %s\n",message);
    send_recieve(pp_name,message);
//    fgets(sign_log,64,stdin);
    recieve_message(pp_name,sign_log);
    sscanf(sign_log,"%[^\n]",sign_log);
    if (strcmp(sign_log,"1") == 0){
      i = sign_in(pp_name);
    }
    else if (strcmp(sign_log,"2") == 0){
      i = login(pp_name,usr,passwd);
    }
  }
}

int read_close(){ //if server terminal types close then server shuts down
  printf("type (close) to shut down server\n");
  char * message = (char *) calloc(sizeof(char),200);
  fgets(message,64,stdin);
  sscanf(message,"%[^\n]",message);
  if (strcmp(message,"close") == 0){
    return 0;
  }
  return 1;
}

//if 1, found. if 0, not found
int in_list(char * pp,char ** pp_list){
  for (int i = 0;i<100;i++){
    char * p = pp_list[i];
    if (p != NULL){
      if (strcmp(pp,p) == 0){
        return 1;
      }
    }
  }
  return 0;
}

int in_lobby(char * pp_name){
  struct stored_key *semkey;
  semkey = get_semaphore("online users semaphore");
  int val = -1;
  if (strcmp(semkey->name,"online users semaphore") == 0){
    int sem_ds = semget(semkey->key,1,0);
    union semun data;
    val = semctl(sem_ds,0,GETVAL,data);
  }else{
    printf("key not found");
  }
  char * message = (char *) calloc(sizeof(char),200);
  sprintf(message,"%d\n",val);
  send_only(pp_name,message);
  return val;
}

void add_to_list(char * pp,char ** pp_list){
  int i = 0;
  char * p = pp_list[i];
  while (p != NULL){
    p = pp_list[i];
    i += 1;
  }
  pp_list[i] = pp;
}

int main(){
  int connector_pid = create_server();
  int f = fork();
  if (f == 0){
    char ** pp_list = (char **) calloc(sizeof(char*),100); //lifetime connections to the server
    char ** logged_pp_list = (char **) calloc(sizeof(char*),100); //pipes that have logged in
    char ** disconnected_pp_list = (char **) calloc(sizeof(char*),100); //connections that have exited
    
    logged_pp_list = get_private_pipes();
    disconnected_pp_list = get_private_pipes();
    while (1){
      pp_list = get_private_pipes();
      for (int i = 0;i<100;i++){
        char * pp = pp_list[i];
        if (pp != NULL){
//          printf("%s\n",pp);
//          printf("%d\n",in_list(pp,disconnected_pp_list));
          if (in_list(pp,disconnected_pp_list) == 0){
            if (in_list(pp,logged_pp_list) == 0){
              printf("logging in %s\n",pp);
              open_screen(pp);
              add_to_list(pp,logged_pp_list);
              printf("successfully logged in %s\n",pp);
            }
            else{
              printf("online users: \n");
              in_lobby(pp);
//              printf("here2\n");
            }
          }
//          for (int j = 0;j<100;j++){
//            if (strcmp(pp_list[i],disconnected_pp_list[j]) != 0){ //if not disconnected
//              if (strcmp(pp_list[i],unlogged_pp_list[j]) != 0){ //if the connection is new, user hasn't logged in yet
//                // up semaphore
//                open_screen(pp);
//              }
//            }
//          }
        }
      }
    }
  }
  else{
    int game_active = 1;
    while (game_active == 1){
      game_active = read_close();
    }
    kill(f, SIGKILL);
    close_server(connector_pid);
  }
  return 0;
}



