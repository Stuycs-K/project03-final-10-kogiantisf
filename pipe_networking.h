#include "libraries.h"

#ifndef NETWORKING_H
#define NETWORKING_H


void create_pp(char * pp_name);

void recieve_message(char*pipe_name,char*message);

void send_message(char*pipe_name,char*message);

#endif

