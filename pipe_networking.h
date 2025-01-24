#include "libraries.h"

#ifndef NETWORKING_H
#define NETWORKING_H


void create_pp(char * pp_name);

int recieve_message(char*pipe_name,char*message);

void send_message(char*pipe_name,char*message);

char * modify_message(char*message,char mode);

void send_only(char*pipe_name,char*message);

void send_recieve(char*pipe_name,char*message);

  
#endif

