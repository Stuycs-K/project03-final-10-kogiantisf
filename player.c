#include "player.h"
#include "client_server.h"
#include "pipe_networking.h"

int connect_to_server(char * pp_name){
  printf("sending pp\n");
  send_pp_name(pp_name);
  printf("sent pp\n");
  return 0;
}


int main(){
  char * pp_name = (char *) calloc(sizeof(char),20);
  sprintf(pp_name, "./%d_pipe", getpid());
  
  create_pp(pp_name); //creates private pipe
  
  connect_to_server(pp_name);
  
  char * message = (char *) calloc(sizeof(char),200);
  while (1){
    printf("waiting for message\n");
    recieve_message(pp_name,message);
    printf("%s\n",message);
    fgets(message,64,stdin);
    sscanf(message,"%[^\n]",message);
    send_message(pp_name,message);
  }
  return 0;
}
