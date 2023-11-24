
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/errors.h"
#include "../common/flagarr.h"
#include "flags.h"

void print_file(char *name, char *flags);
void parstext(char *flags, char *buffer, int *count, int *countnull,
              int *countchar);

int main(int argc, char *argv[]) {
  char *filename = NULL;

  char flagdarr[10] = {'\0'};
  int flag = 0;
  if (argc == 1) {
    error_print(1);
  } else {
    int rez = 0;
    while ((rez = getopt(argc, argv, "benETvst")) != -1 && flag == 0) {
      switch (rez) {
        case 'b':
          addflags('b', flagdarr);
          break;
        case 'e':
          addflags('e', flagdarr);
          break;
        case 'n':
          addflags('n', flagdarr);
          break;
        case 's':
          addflags('s', flagdarr);
          break;
        case 't':
          addflags('t', flagdarr);
          break;
        case 'T':
          addflags('T', flagdarr);
          break;
        case 'E':
          addflags('E', flagdarr);
          break;
        case 'v':
          addflags('v', flagdarr);
          break;
        default:
          error_print(4);
          flag = 1;
          break;
      }
    }
    filename = return_filename(argv, argc, flagdarr);
    if (flag == 0) {
      print_file(filename, flagdarr);
    }
  }
  free(filename);

  return 0;
}
void print_file(char *name, char *flags) {
  char *token = strtok(name, " ");
  while (token != NULL) {
    char *filename_copy = my_strdup(token);
    FILE *f = fopen(filename_copy, "rt");
    int count = 1, countnull = 0, countchar = 1;

    char *buffer = calloc(sizeof(char), 256);
    if (f != NULL) {
      while ((fgets(buffer, 256, f)) != NULL) {
        parstext(flags, buffer, &count, &countnull, &countchar);
        count++;
      }
      fclose(f);
    } else {
      error_print(3);
    }

    free(buffer);
    free(filename_copy);
    token = strtok(NULL, " ");
  }
}
void parstext(char *flags, char *buffer, int *count, int *countnull,
              int *countchar) {
  char *res = calloc(sizeof(char), 256);
  res[0] = 0;
  int flag = 0;

  if ((strchr(flags, 'n') != NULL) && (strchr(flags, 'b') == NULL)) {
    if (res[0] != '\0') {
      workflagnforres(countchar, res);
    } else {
      workflagn(buffer, countchar, res);
    }
  }

  if (strchr(flags, 't') != NULL) {
    addflags('v', flags);
    if (res[0] != '\0') {
      workflagtforres(res, flags);

    } else {
      workflagt(buffer, res);
    }
  }
  if (strchr(flags, 's') != NULL) {
    if (res[0] != '\0') {
      flag = workflagsforres(res, countnull);

    } else {
      flag = workflags(buffer, res, countnull);
    }
  }
  if (strchr(flags, 'E') != NULL) {
    if (res[0] != '\0') {
      workflageforres(res);
    } else {
      workflage(buffer, res);
    }
  }
  if (strchr(flags, 'T') != NULL) {
    if (res[0] != '\0') {
      workflagtforres(res, flags);
    } else {
      workflagt(buffer, res);
    }
  }
  if (strchr(flags, 'v') != NULL) {
    if (res[0] != '\0') {
      workflagVforres(res);

    } else {
      workflagV(buffer, res);
    }
  }
  if (strchr(flags, 'b') != NULL) {
    if (res[0] != '\0') {
      workflagbforres(count, res);
    } else {
      workflagb(buffer, count, res);
    }
  }
  if (strchr(flags, 'e') != NULL) {
    addflags('v', flags);
    if (res[0] != '\0') {
      workflageforres(res);
    } else {
      workflage(buffer, res);
    }
  }

  if (flags[0] == '\0') {
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
  }

  if (flag == 0) {
    printf("%s", res);
    *countchar = *countchar + 1;
  }
  free(res);
}
