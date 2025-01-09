/*
WORKING:
–––––––––––
DESCRIPTION/NOTES


–––––––––––
ARGUMENTS


–––––––––––
RETURN VALUE


*/


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
int signin(char* username,char*password){
  FILE* player_info;
  player_info = fopen("player_info.csv","w");
  
  
  fclose(player_info);
}


/*
WORKING: implemented later
–––––––––––
DESCRIPTION/NOTES
 
hashes the player's password as protection measure
–––––––––––
ARGUMENTS

char* password
the raw password of the player, as typed
(no min/max length)
–––––––––––
RETURN VALUE
 
NULL if error
char* is hashed password for storage in player_info.csv
*/
char * hash(char * password){
  return password;
}
