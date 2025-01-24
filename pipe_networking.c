#include "pipe_networking.h"

//creates private pipe
void create_pp(int client_pid){
  char * pp_name = (char*) malloc(10*sizeof(char));
  sprintf(pp_name,"./%d",client_pid);
  if(mkfifo(pp_name,666) < 0){
    err();
  }
}

void recieve_message(char*pipe_name,char*message){
  int e = open(pipe_name,O_RDONLY);
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
  int e = open(pipe_name,O_WRONLY);
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
