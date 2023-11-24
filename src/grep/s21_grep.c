
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/errors.h"
#include "../common/flagarr.h"
#include "flagsworks.h"
#include "multiflags.h"
void findtexteintfile(char *filename, char **template, char *flags);
void findword(char *flags, char *buffer, int *count, int *countn,
              char **template, int *check, char *token, char *filename_copy,
              int *flagfile, char **fileline, int *line, int *flagcountfile);
int count_files(const char *filename);

int main(int argc, char *argv[]) {
  char *filename = NULL;
  char *template = returntemplate(argv, argc);
  char flagdarr[10] = {'\0'};
  int flag = 0;
  if (argc < 3 || template == NULL) {
    error_print(5);
  } else {
    int rez = 0;
    while ((rez = getopt(argc, argv, "eivclnhsof")) != -1 && flag == 0) {
      switch (rez) {
        case 'e':
          addflags('e', flagdarr);
          break;
        case 'i':
          addflags('i', flagdarr);
          break;
        case 'v':
          addflags('v', flagdarr);
          break;
        case 'c':
          addflags('c', flagdarr);
          break;
        case 'l':
          addflags('l', flagdarr);
          break;
        case 'n':
          addflags('n', flagdarr);
          break;
        case 'h':
          addflags('h', flagdarr);
          break;
        case 's':
          addflags('s', flagdarr);
          break;
        case 'f':
          addflags('f', flagdarr);
          break;
        case 'o':
          addflags('o', flagdarr);
          break;
        default:
          error_print(4);
          flag = 1;
          break;
      }
    }
    filename = return_filename(argv, argc, flagdarr);
    if (flag == 0) {
      findtexteintfile(filename, &template, flagdarr);
    }
  }

  free(template);
  free(filename);
  return 0;
}
void findtexteintfile(char *filename, char **template, char *flags) {
  int check = count_files(filename);
  char *token = strtok(filename, " ");

  char *fileline[1000];
  for (int i = 0; i < 1000; i++) {
    fileline[i] = calloc(1000, sizeof(char));
  }
  int line = 0, flagcountfile = 0;
  while (token != NULL) {
    char *filename_copy = my_strdup(token);
    FILE *f = fopen(filename_copy, "rt");

    int count = 0, countn = 1;
    int flagfile = 0;
    char *buffer = calloc(sizeof(char), 1000);
    if (f != NULL) {
      while ((fgets(buffer, 1000, f)) != NULL) {
        findword(flags, buffer, &count, &countn, template, &check, token,
                 filename_copy, &flagfile, fileline, &line, &flagcountfile);
        countn++;
      }
      fclose(f);
    } else if (!f && strchr(flags, 's') == NULL) {
      error_print(3);
    } else if (!f && strchr(flags, 's') != NULL) {
      break;
    }
    free(buffer);

    if (strchr(flags, 'c') != NULL) {
      if (check > 1) {
        printf("%s:", token);
      }
      printf("%d\n", count);
      if (strchr(flags, 'l') != NULL && check == 1) {
        printf("%s\n", filename_copy);
      }
    }
    flagcountfile++;
    free(filename_copy);
    token = strtok(NULL, " ");
  }
  for (int i = 0; i < 1000; i++) {
    free(fileline[i]);
  }
}

void findword(char *flags, char *buffer, int *count, int *countn,
              char **template, int *check, char *token, char *filename_copy,
              int *flagfile, char **fileline, int *line, int *flagcountfile) {
  char *res = calloc(sizeof(char), 1000);
  int resv = 0;

  if (strchr(flags, 'e') != NULL && strchr(flags, 'o') == NULL &&
      strchr(flags, 'v') == NULL) {
    flage(buffer, res, template);
  }

  if (strchr(flags, 'i') != NULL && strchr(flags, 'o') == NULL &&
      strchr(flags, 'v') == NULL) {
    if (res[0] != '\0') {
      multiflagi(res, template);

    } else {
      flagi(buffer, res, template);
    }
  }
  if (strchr(flags, 'v') != NULL) {
    if (res[0] != '\0') {
      multiflagv(res, template, flags);
    } else {
      resv = flagv(buffer, res, template, flags);
    }
  }

  if (strchr(flags, 'c') != NULL) {
    if (strchr(flags, 'l') != NULL) {
      if (*check == 1) {
        *count = *check;
      } else {
        *count = *flagfile;
      }
    } else {
      flagc(buffer, template, count, flags);
    }
  }
  if (strchr(flags, 'l') != NULL) {
    *flagfile += flagl(buffer, template);
    if (*flagfile == 1 && strchr(flags, 'c') == NULL) {
      printf("%s\n", filename_copy);
      *flagfile += 1;
    } else if (*flagfile == 1) {
      *flagfile += 1;
    }
  }

  if ((strchr(flags, 'n') != NULL) && resv == 0) {
    if (res[0] != '\0') {
      multiflagn(res, countn);

    } else {
      if (strchr(flags, 'o') == NULL) {
        flagn(buffer, res, template, countn);
      }
    }
  }
  if (strchr(flags, 'h') != NULL && resv == 0 && strchr(flags, 'o') == NULL) {
    if (res[0] != '\0') {
      multiflagh(res, template, flags);
    } else {
      flagh(buffer, res, template);
    }
  }
  if (strchr(flags, 's') != NULL && strchr(flags, 'o') == NULL &&
      strchr(flags, 'v') == NULL) {
    if (res[0] != '\0') {
      multiflags(res, template, flags);
    } else {
      flagS(buffer, res, template);
    }
  }
  if (strchr(flags, 'f') != NULL) {
    flagf(buffer, res, template, fileline, check, line, flagcountfile);
  }
  if (strchr(flags, 'o') != NULL && strchr(flags, 'v') == NULL) {
    if (res[0] != '\0') {
      multiflago(res, template, flags, countn);
    } else {
      flago(buffer, res, template, flags, countn);
    }
  }

  if (flags[0] == '\0') {
    regex_t regex;
    if (regcomp(&regex, *template, REG_ICASE) != 0) {
      error_print(6);
    }
    if (regexec(&regex, buffer, 0, NULL, 0) != 0) {
      for (int i = 0; i < str_lenght(buffer); i++) {
        res[i] = buffer[i];
      }
    }
    regfree(&regex);
  }

  if (strchr(flags, 'c') == NULL && strchr(flags, 'l') == NULL) {
    if ((*check > 1) && res[0] != '\0' && strchr(flags, 'h') == NULL &&
        strchr(flags, 'f') == NULL) {
      printf("%s:", token);
    }
    printf("%s", res);
  }
  countn = countn + 1;
  free(res);
}
