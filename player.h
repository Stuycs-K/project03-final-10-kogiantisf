#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef PLAYER_H
#define PLAYER_H

int connect_to_server();
/*
WORKS: NO
-----------
DESCRIPTION

starts the 3-way handshake to the server

-----------
RETURN VALUE

-1 if there are issues
1 if no known errors
*/


int display_from_server();
/*
WORKS: NO
-----------
DESCRIPTION

displays the any prompts/messages from the server

-----------
RETURN VALUE

-1 if there are issues
1 if no known errors
*/
#endif
