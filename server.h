#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef
#define SERVER_H
#define WKP "poker"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 100

#define SYN 0
#define SYN_ACK 1
#define ACK 2
#define MESSAGE 3
#define EXIT 4

int server_setup();
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
0 if no known errors
*/


int send_data();
/*
WORKS: NO
-----------
DESCRIPTION

host sends information about the game to the player's programs through a pipe

-----------
RETURN VALUE

-1 if there are issues
0 if no known errors
*/

int read_new_connections();
/*
WORKS: NO
-----------
DESCRIPTION

likely used in a fork, constantly monitors if any new players have joined - using select
-----------
RETURN VALUE

-1 if there are issues
0 if no known errors
*/

int kick_from_game();
/*
WORKS: NO
-----------
DESCRIPTION

kills the specified process/connection
-----------
RETURN VALUE

-1 if there are issues
0 if no known errors
*/

#endif
