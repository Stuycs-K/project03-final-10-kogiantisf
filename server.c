#include "server.h"
#include "pipe_networking.h"
/*
WORKING:
–––––––––––
DESCRIPTION/NOTES


–––––––––––
ARGUMENTS


–––––––––––
RETURN VALUE


*/
int err(){
  printf("err %d\n",errno);
  printf("%s\n",strerror(errno));
  exit(1);
}




int create_server() {
  FILE * guest_storage = fopen("guest_storage.txt","w");
  FILE * key_storage = fopen("key_storage.txt","w");
  //for now won't write anything in files, just create them
  int upstream = server_setup();
  fwrite(&upstream,sizeof(int),1,key_storage);
  
  fclose(guest_storage);
  fclose(key_storage);
  return 1;
}

int sign_in(){
  char * line_buff = malloc(255);
  printf("username: ");
  fgets(line_buff,255,stdin);
  sscanf(line_buff,"%[^\n]",line_buff);
}

int add_player_info(char* usr,char*passwd){
  FILE* player_info;
  player_info = fopen("player_info.dat","a");
  struct player new_player = malloc(sizeof(struct player)*1);
  new_player.username = usr;
  new_player.password = passwd;
  fwrite(&new_player,sizeof(new_player),1,player_info);
  fclose(player_info);
  return 1;
}

int login(char* username,char*password){
  
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



