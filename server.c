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

void ask_usr_psswd(usr,psswd){
  printf("username: ");
  fgets(usr,64,stdin);
  sscanf(usr,"%[^\n]",usr);
  
  printf("password: ");
  fgets(psswd,64,stdin);
  sscanf(psswd,"%[^\n]",psswd);
}

int sign_in(){
  char * usr = (char*) malloc(sizeof(char)*64);
  char * passwd = (char*) malloc(sizeof(char)*64);
  ask_usr_psswd(usr,psswd);
  return add_player_info(usr,psswd);
  free(usr);
  free(psswd);
}

int add_player_info(char* usr,char*passwd){
  FILE* player_info;
  player_info = fopen("player_info.dat","a");
  if (player_info == NULL){
    err();
  }
  struct player new_player;
  new_player.username = usr;
  new_player.password = passwd;
  fwrite(&new_player,sizeof(new_player),1,player_info);
  fclose(player_info);
  return 1;
}

int login(char* username,char*password){
  char * usr = (char*) malloc(sizeof(char)*64);
  char * passwd = (char*) malloc(sizeof(char)*64);
  ask_usr_psswd(usr,psswd);
  
}

char * get_name_password(char * usr, char* pssd,int player_id){
  FILE* player_info;
  player_info = fopen("player_info.dat","r");
  if (player_info == NULL){
    err();
  }
  fseek(player_id*sizeof(new_player)*1);
  fread()
}
struct stat * get_stat_buffer(char * filepath){
  struct stat * stat_buffer;
  stat_buffer = malloc(sizeof(struct stat));
  stat(filepath, stat_buffer);
  return stat_buffer;
}
long get_file_size(struct stat * stat_buffer){
  long size = stat_buffer->st_size;
  return size;
}
  
int get_num_players(){
  struct stat * sp = get_stat_buffer("./nyc_pop.dat");
  int size = get_file_size(sp); //size is the number of bytes +1
  size -= 1;
  return size /  sizeof(struct new_player);
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



