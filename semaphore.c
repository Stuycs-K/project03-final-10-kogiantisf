#include "semaphore.h"

int * get_random(int length){
  FILE * f = fopen("/dev/random", "r");
  int * buff = (int *) malloc(length*sizeof(int));
  if(f == NULL) err();
  int n;
//  printf("r_file: %u\n",r_file);
  n = fread(buff,length*sizeof(int),length,f);
  // printf("Bytes read: %u",n);
  // printf("'''%d'''\n",buff[0]);
  return buff;
}

void create_semaphore(){
//  int * shmkey;
//  int * shmid = (int *) malloc(sizeof(int)*1);
//  shmkey = get_random(1);
//  printf("shkey: %d\n",*shmkey);
//  *shmid = shmget(*shmkey,sizeof(int),IPC_CREAT | 0640);
//  printf("shmid: %d\n", *shmid);
//  printf("shared memory created\n");

  int * semkey;
  int * semid = (int *) malloc(sizeof(int)*1);
  semkey = get_random(1);
  printf("semkey:%d\n",*semkey);
  *semid = semget(*semkey,1,IPC_CREAT | 0640);
  printf("semid: %d\n", *semid);
  printf("semaphore created\n");
//
//
  struct stored_key online_count;
  online_count.key = *semkey;
  strcpy(online_count.name,"online users semaphore");
  FILE * f = fopen("key_storage.dat","a");
//  fwrite(shmkey,sizeof(int),1,f);
  fwrite(&online_count,sizeof(struct stored_key),1,f);
  fclose(f);
  printf("ids/keys written\n");

  union semun data;
  data.val = 0;
  int error = semctl(*semid,0,SETVAL,data);
  if (error < 0){
    err();
  }
//
//
//  FILE * f_story = fopen("story.txt","w");
//  fclose(f_story);
//  return semkey;

}


void rem(){
  FILE * f = fopen("key_storage.dat","r");
  if (f == NULL){
    err();
  }
  int * shmkey = (int*) malloc(sizeof(int));
  int * semkey = (int*) malloc(sizeof(int));

  int error;

  error = fread(shmkey,sizeof(int),1,f);
  if (error < 0){
    err();
  }
  printf("shmkey: %d\n",*shmkey);

  error = fread(semkey,sizeof(int),1,f);
  if (error < 0){
    err();
  }
  printf("semkey: %d\n",*semkey);

  fclose(f);
  semctl(*semkey,IPC_RMID,0);
  printf("semaphore removed\n");
  shmctl(*shmkey, IPC_RMID,0);
  printf("shared memory removed\n");
}

struct stored_key * get_semaphore(char * key_name){
  
  FILE * key_storage = fopen("key_storage.dat","r");
  struct stored_key *semkey;
  int r = fread(semkey,sizeof(struct stored_key),1,key_storage);
  while (r > 0 && strcmp(semkey->name,key_name) != 0){
    fread(semkey,sizeof(struct stored_key),1,key_storage);
  }
  printf("%d\n",r);

  fclose(key_storage);

  int val = -1;
  if (strcmp(semkey->name,key_name) == 0){
    return semkey;
  }else{
    printf("key not found");
  }
  return NULL;
}






//int main(int argc, char * argv[]){
//  for (int i = 1;i < argc;i++){
//    if (strcmp(argv[i],"create") == 0){
//      create();
//    }
//    else if (strcmp(argv[i],"remove") == 0){
//      rem();
//    }
//    else if (strcmp(argv[i],"view") == 0){
//      view();
//    }
//  }
//  create();
//  rem();
////  view();
//
//
//  printf("\n");
//  return 0;
//}
