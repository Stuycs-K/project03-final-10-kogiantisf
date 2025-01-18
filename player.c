#include "player.h"
#include "pipe_networking.h"

int err();


int connect_to_server(){
  int * to_server;
  *to_server = open("./public_pipe",O_WRONLY); //somehow will get file_descriptor of pipe
  printf("got here\n");
  int * from_server;
  *from_server = 4;
//  *from_server = client_handshake(to_server);
  return *from_server;
}

int main(){
  connect_to_server();
}
