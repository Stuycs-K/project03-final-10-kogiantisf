#include "pipe_networking.h"

int err(){
  printf("err %d\n",errno);
  printf("%s\n",strerror(errno));
  exit(1);
}



//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  if(mkfifo("./WKP",666) < 0){
    err();
  }
  int * data = (int*) malloc(1*sizeof(int));
  from_client = open("./WKP",O_RDONLY);
  while (*data == 0){
    if(read("./WKP",data,sizeof(int))<0){
      err();
    }
  }
  close(from_client);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  char * pp_name = (char*) malloc(100*sizeof(char));
  sprintf(pp_name,"./%d",getpid());
  if(mkfifo(pp_name,666) < 0){
    err();
  }
  if ((from_client = open(pp_name,O_RDWR))<0){
    err();
  }
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  char * pp_name = (char*) malloc(100*sizeof(char));
  sprintf(pp_name,"./%d",getpid());
  if ((from_client = open(pp_name,O_RDWR))<0){
    err();
  }
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
