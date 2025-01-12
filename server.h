#ifndef
#define SERVER_H

int activate_server();
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
