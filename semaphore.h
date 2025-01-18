#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/sem.h>

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

int get_line(char * line, FILE * f);


void view();

int * get_random(int length);

void create_semaphore();

void rem();

#endif
