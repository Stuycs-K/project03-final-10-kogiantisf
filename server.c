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
    listen_to_connections();
  }
  else{
    FILE * guest_storage = fopen("guest_storage.dat","w");
    fclose(guest_storage);
    FILE * key_storage = fopen("key_storage.dat","w");
    fclose(key_storage);
    create_semaphore();
  }
  
  
  
  //for now won't write anything in files, just create them
//  fwrite(&upstream,sizeof(int),1,key_storage);
//  int upstream = server_setup();
//  printf("%d\n",upstream);
  return f;
}

int close_server(int connector_pid){
  remove("guest_storage.dat");
  remove("key_storage.dat");
  kill(connector_pid, SIGKILL); //kills the loop waiting for connections
  
}






void open_screen(){
  char * usr = (char*) malloc(sizeof(char)*64);
  char * passwd = (char*) malloc(sizeof(char)*64);
  char * sign_log = (char*) malloc(sizeof(char)*1);
  int i = 0;
  while (i == 0){
    printf("signing up (1) \nOR \nloggin in (2) ?\n");
    fgets(sign_log,64,stdin);
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
  while (game_active == 1){
    open_screen();
    game_active = 0;
  }
  close_server(connector_pid);
  return 0;
}



