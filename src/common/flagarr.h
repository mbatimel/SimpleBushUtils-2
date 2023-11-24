#ifndef FLAGARR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addflags(char flag, char *arr);
int checkfalgs(char flag, char *arr);
int str_lenght(char *str);
char *return_filename(char **argv, int argc, char *flags);
char *my_strdup(const char *s);
#endif
