#ifndef
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
0 if no known errors
*/


int char* display_from_server();
/*
WORKS: NO
-----------
DESCRIPTION

displays the any prompts/messages from the server

-----------
RETURN VALUE

-1 if there are issues
0 if no known errors
*/


#endif