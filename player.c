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
  char * pp_name = (char *) calloc(sizeof(char),10);
  sprintf(pp_name, "./%d", getpid());
  connect_to_server(pp_name);
  char * message = (char *) calloc(sizeof(char),200);
//  while (1){
//    recieve_message(pp_name,message);
//    printf(message);
//    fgets(message,64,stdin);
//    sscanf(message,"%[^\n]",message);
//    send_message(pp_name,message);
//  }
  return 0;
}
