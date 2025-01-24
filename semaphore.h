#include "libraries.h"

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

int get_line(char * line, FILE * f);


void view();

int * get_random(int length);

void create_semaphore();

struct stored_key * get_semaphore(char * key_name);

void rem();

#endif
