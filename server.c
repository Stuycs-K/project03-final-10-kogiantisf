#include "server.h"
#include "pipe_networking.h"


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



