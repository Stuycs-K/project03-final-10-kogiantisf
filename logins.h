#include "libraries.h"

#ifndef LOGINS_H
#define LOGINS_H

void ask_usr_passwd(char * pp_name,char * usr,char * passwd);

int add_player_info(char* usr,char*passwd);

int sign_in(char * pp_name);

int login(char * pp_name,char* username,char*password);

struct stat * get_stat_buffer(char * filepath);

long get_file_size(struct stat * stat_buffer);

int get_num_players();

int find_player(char* usr, char*passwd);

char * hash(char * password);

#endif
