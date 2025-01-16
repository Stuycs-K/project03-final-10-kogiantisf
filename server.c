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
int err();
//{
//  printf("err %d\n",errno);
//  printf("%s\n",strerror(errno));
//  exit(1);
//}




int create_server() {
//  int upstream = server_setup();
  FILE * guest_storage = fopen("guest_storage.dat","w");
  fclose(guest_storage);
  FILE * key_storage = fopen("key_storage.dat","w");
  //for now won't write anything in files, just create them
//  fwrite(&upstream,sizeof(int),1,key_storage);
  fclose(key_storage);
  return 1;
}

void ask_usr_passwd(char * usr,char * passwd){
  printf("username: ");
  fgets(usr,64,stdin);
  sscanf(usr,"%[^\n]",usr);
  
  printf("password: ");
  fgets(passwd,64,stdin);
  sscanf(passwd,"%[^\n]",passwd);
}

int add_player_info(char* usr,char*passwd){
  FILE* player_info;
  player_info = fopen("player_info.dat","a");
  if (player_info == NULL){
    err();
  }
  struct player new_player;
  strcpy(new_player.username,usr);
  strcpy(new_player.password,passwd);
  fwrite(&new_player,sizeof(struct player),1,player_info);
  fclose(player_info);
  return 1;
}

// returns 0 if exists already, 1 if not
int sign_in(){
  char * usr = (char*) malloc(sizeof(char)*64);
  char * passwd = (char*) malloc(sizeof(char)*64);
  ask_usr_passwd(usr,passwd);
  int p = add_player_info(usr,passwd);
  free(usr);
  free(passwd);
  return p;
}

// returns 1 if correct creds, 0 if not
int login(char* username,char*password){
  char * usr = (char*) malloc(sizeof(char)*64);
  char * passwd = (char*) malloc(sizeof(char)*64);
//  char * curr_usr = (char*) malloc(sizeof(char)*64);
//  char * curr_passwd = (char*) malloc(sizeof(char)*64);
  ask_usr_passwd(usr,passwd);
  
  if (find_player(usr,passwd) != -1){
    return 1;
  }
  return 0;
}

//int get_name_password(char * usr, char* pssd,FILE*player_info){
//  return
//}
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
  struct stat * sp = get_stat_buffer("./player_info.dat");
  int size = get_file_size(sp); //size is the number of bytes +1
  size -= 1;
  return size /  sizeof(struct player);
}

//returns index if exists
//otherwise -1
int find_player(char* usr, char*passwd){
  char * curr_usr = (char*) malloc(sizeof(char)*64);
  char * curr_passwd = (char*) malloc(sizeof(char)*64);
  
  FILE* player_info;
  player_info = fopen("player_info.dat","r");
  if (player_info == NULL){
    err();
  }
  
  
  struct player * p = (struct player *) malloc (sizeof(struct player)*1);
  int read_bytes = 1;
  
  int i = 0;
  while (read_bytes > 0){
    read_bytes = fread(p,sizeof(struct player),1,player_info);
    curr_usr = p->username;
    curr_passwd = p->password;
    if (strcmp(usr,curr_usr) && strcmp(passwd,curr_passwd)){
      fclose(player_info);
//      free(usr);
//      free(passwd);
//      free(curr_usr);
//      free(curr_passwd);
      return i;
    }
    i += 1;
  }
  return -1;
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




void open_screen(){
  char * usr = (char*) malloc(sizeof(char)*64);
  char * passwd = (char*) malloc(sizeof(char)*64);
  char * sign_log = (char*) malloc(sizeof(char)*1);
  printf("signing up (1) \nOR \nloggin in (2) ?\n");
  fgets(sign_log,64,stdin);
  sscanf(sign_log,"%[^\n]",sign_log);
  int i = 1;
  while (i == 1){
    if (strcmp(sign_log,"1")){
      i = sign_in();
    }
    else if (strcmp(sign_log,"2")){
      i = login(usr,passwd);
    }
  }
}


int main(){
  create_server();
  open_screen();
  return 0;
}



