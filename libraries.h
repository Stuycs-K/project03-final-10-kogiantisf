#define NULL 0

#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

int err();
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

#endif

