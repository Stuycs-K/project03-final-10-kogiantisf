#include "pipe_networking.h"

//creates private pipe
void create_pp(char * pp_name){
  umask(0000);
  if(mkfifo(pp_name,0666) < 0){
    err();
  }
}

void recieve_message(char*pipe_name,char*message){
  int e = open(pipe_name,O_RDWR);
  if (e < 0){
    err();
  }
  int i = 0;
  while (*(message+i) != '\0'){
    write(e,(message+i),1);
    i += 1;
  }
  close(e);
}

void send_message(char*pipe_name,char*message){
  int e = open(pipe_name,O_RDWR);
    if (e < 0){
      err();
    }
    int i = 0;
    while (*(message+i) != '\0'){
      write(e,(message+i),1);
      i += 1;
    }
    close(e);
}
