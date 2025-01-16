

#ifndef SERVER_H
#define SERVER_H
struct player{
  int player_id;
  char username[64];
  char password[64];
  int balance;
  int highest_balance;
  int lowest_balance;
  int hands_won;
  char last_online[64];
  char join_date[64];
};
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


int sign_in();











int add_player_info(char* username,char*password);
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

// returns 0 if exists already, 1 if not
int sign_in();

// returns 1 if correct creds, 0 if not
int login(char* username,char*password);

struct stat * get_stat_buffer(char * filepath);

int get_num_players();

//returns index if exists
//otherwise -1
int find_player(char* usr, char*passwd);


void open_screen();

#endif
