#include "player.h"
#include "pipe_networking.h"

int connect_to_server(){
  int * to_server = &4; //somehow will get file_descriptor of pipe
  int * from_server = client_handshake(to_server);
}
