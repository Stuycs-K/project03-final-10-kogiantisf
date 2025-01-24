#include "player.h"
#include "client_server.h"

int connect_to_server(){
  char * pp_name = (char *) calloc(sizeof(char),10);
  sprintf(pp_name, "%d", getpid());
  printf("sending pp\n");
  send_pp_name(pp_name);
  printf("sent pp\n");
  return 0;
}


int main(){
  connect_to_server();
  return 0;
}
