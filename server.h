#include "libraries.h"

#ifndef SERVER_H
#define SERVER_H

int create_server();

/*
WORKS: NO
-----------
DESCRIPTION

the "host" runs this function to create the server - and open connections
creates file to store temporary keys/operations
creates a semaphore to keep track of connections

-----------
RETURN VALUE

-1 if there are issues
1 if no known errors
*/

void close_server(int connector_pid);

void open_screen();

#endif
