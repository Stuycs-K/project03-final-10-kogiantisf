#include "pipe_networking.h"

//creates private pipe
void create_pp(char * pp_name){
  umask(0000);
  if(mkfifo(pp_name,0666) < 0){
    err();
  }
}

void recieve_message(char*pipe_name,char*message){
  int e = open(pipe_name,O_RDONLY);
  if (e < 0){
    err();
  }
  int bytes_read = read(e, message, 200);
//  printf("%d\n",bytes_read);
  if (bytes_read < 0) {
    printf("no message read\n");
  }
  close(e);
}

void send_message(char*pipe_name,char*message){
  int e = open(pipe_name,O_WRONLY);
  if (e < 0){
    err();
  }
  int i = 0;
//  while (*(message+i) != '\0'){
  int bytes_written = write(e,(message+i),200);
//  printf("%d\n",bytes_written);
//    i += 1;
//  }
  close(e);
}
