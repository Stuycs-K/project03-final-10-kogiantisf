

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



int signup(char* username,char*password);
/*
WORKING: NO
–––––––––––
DESCRIPTION/NOTES

adds the new username and password to
assumes player_info.csv is created

–––––––––––
ARGUMENTS

char* username
the username of the player
(no min/max length)

char* password
the raw password of the player, as typed
(no min/max length)

–––––––––––
RETURN VALUE

1 if added; no issues
0 if error (check errno) in main run
*/

int send_data();
/*
WORKS: NO
-----------
DESCRIPTION

host sends information about the game to the player's programs through a a private pipe

-----------
RETURN VALUE

-1 if there are issues
1 if no known errors
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
1 if no known errors
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
1 if no known errors
*/

struct player{
  char[64] username;
  char[64] password;
  int balance;
  int highest_balance;
  int lowest_balance;
  int hands_won;
  char[64] last_online;
  char[64] join_date;
}

#endif
