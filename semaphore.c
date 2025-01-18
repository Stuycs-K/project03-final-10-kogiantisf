#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/sem.h>

int err();

int get_line(char * line, FILE * f){ //line is malloced already
  int r_error = 1; // for inital condition of while loop
  char char_buff[2]; //initialize char_buff reads one character at a time
  *(char_buff+1) = '\0'; //make second index null, so its printable
  int i = 0; //incerement index

  while (r_error == 1){ // if r_error = 1, it is good to read; if r_error = 0, you have reached EOF
    r_error = fread(char_buff, 1*sizeof(char),1,f); // reads one character, puts into line_buff
    if (*(char_buff) == '\n'){ // if there is a newline, return just up to (excluding) the newline
      *(line + i) = '\0'; //add null so it's printable
      return 0; //breaks from loop and returns value that something was read
    }
    else{
      *(line+i) = *(char_buff); //adds read character to line;
      i += 1; //increment
    }
  }
  return 1; // at EOF so return must show we wont read anymore, there is no \n plus compiler gets mad
}


void view(){
  printf("\n");
  FILE * f;
  f = fopen("story.txt","r");
  if (f==NULL){
    err();
  }
  char * line = (char*) malloc(sizeof(char)*100);
  int error = get_line(line,f);
  printf("%s\n",line);
  while (error > 0){
    error = get_line(line,f);
    printf("%s\n",line);
  }
  free(line);
  fclose(f);
}

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
  FILE * f = fopen("key_storage.dat","a");
//  fwrite(shmkey,sizeof(int),1,f);
  fwrite(semkey,sizeof(int),1,f);
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
