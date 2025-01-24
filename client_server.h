#include "libraries.h"

#ifndef CONNECT_SERVER_H
#define CONNECT_SERVER_H

int listen_to_connections();
int send_pp_name(char * pp_name);
void store_private_pipe(char* pp_name);
char ** get_private_pipes();

#endif
