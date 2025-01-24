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
    send_message(pp_name,message);
//    fgets(sign_log,64,stdin);
    recieve_message(pp_name,sign_log);
    sscanf(sign_log,"%[^\n]",sign_log);
    if (strcmp(sign_log,"1") == 0){
      i = sign_in();
    }
    else if (strcmp(sign_log,"2") == 0){
      i = login(usr,passwd);
    }
  }
}





int main(){
  int connector_pid = create_server();
  int game_active = 1;
  char ** pp_list = (char **) calloc(sizeof(char*),100); //lifetime connections to the server
  char ** new_pp_list = (char **) calloc(sizeof(char*),100); //newest connections to server
  char ** disconnected_pp_list = (char **) calloc(sizeof(char*),100); //connections that have exited
  
  while (game_active == 1){
    pp_list = get_private_pipes();
    for (int i = 0;i<100;i++){
      char * pp = pp_list[i];
      if (pp != NULL){
        printf("%s\n",pp);
        game_active = 0;
//        for (int j = 0;j<100;j++){
//          if (strcmp(pp_list[i],disconnected_pp_list[j]) != 0){ //if not disconnected
//            if (strcmp(pp_list[i],new_pp_list[j]) == 0){ //if the connection is new
//              // up semaphore
//              open_screen(pp);
//            }
//          }
//        }
      }
    }
  }
  close_server(connector_pid);
  return 0;
}



