#include "pipe_networking.h"

//creates private pipe
void create_pp(char * pp_name){
  umask(0000);
  if(mkfifo(pp_name,0666) < 0){
    err();
  }
}


// if first character is
char * modify_message(char*message,char mode){
  char * modified_message = (char *) calloc(sizeof(char),201);
  strcpy(modified_message+1,message);
  modified_message[0] = mode;
  return modified_message;
}

void send_only(char*pipe_name,char*message){
  send_message(pipe_name,modify_message(message,'0'));
}

void send_recieve(char*pipe_name,char*message){
  send_message(pipe_name,modify_message(message,'1'));
}

// returns 1 if wants response
// returns 0 if no response
int recieve_message(char*pipe_name,char*message){
  char * modified_message = (char *) calloc(sizeof(char),201);
  int e = open(pipe_name,O_RDONLY);
  if (e < 0){
    err();
  }
  int bytes_read = read(e, modified_message, 201);

//  printf("%d\n",bytes_read);
  if (bytes_read < 0) {
    printf("no message read\n");
//    err();
  }
  close(e);
  strcpy(message,modified_message+1);
  if (modified_message[0] == '1'){
    return 1;
  }else{
    return 0;
  }
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
//  printf("sending : %s\n",message);
  close(e);
}
