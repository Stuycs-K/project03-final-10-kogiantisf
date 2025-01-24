#include "libraries.h"

#ifndef NETWORKING_H
#define NETWORKING_H


void create_pp(int client_pid);

int recieve_message(char*pipe_name,char*message);

int send_message(char*pipe_name,char*message);

#endif

