#include "flagsworks.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/errors.h"
#include "../common/flagarr.h"
#include "multiflags.h"

void flage(char *buffer, char *res, char **template) {
  int j = 0;
  regex_t regex;
  char *template_copy = *template;
  int line_matched = 0;

  while (*template_copy != '\0') {
    while (*template_copy == ' ') {
      template_copy++;
    }

    if (*template_copy == '\0') {
      break;
    }

    char *token = calloc(sizeof(char), 1000);
    int k = 0;

    while (*template_copy != ' ' && *template_copy != '\0') {
      token[k] = *template_copy;
      k++;
      template_copy++;
    }
    token[k] = '\0';

    if (regcomp(&regex, token, 0) != 0) {
      error_print(6);
    }
    if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
      if (!line_matched) {
        for (int i = 0; i < str_lenght(buffer); i++) {
          res[j] = buffer[i];
          j++;
        }
        line_matched = 1;
      }
    }

    regfree(&regex);
    free(token);
  }
}

void flagi(char *buffer, char *res, char **template) {
  regex_t regex;

  if (regcomp(&regex, *template, REG_ICASE) != 0) {
    error_print(6);
  }
  if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
  }
  regfree(&regex);
}
int flagv(char *buffer, char *res, char **template, char *flags) {
  regex_t regex;
  int flag = 0;

  if (strchr(flags, 'i') != NULL) {
    if (regcomp(&regex, *template, REG_ICASE) != 0) {
      error_print(6);
    }
  } else {
    if (regcomp(&regex, *template, 0) != 0) {
      error_print(6);
    }
  }
  if (regexec(&regex, buffer, 0, NULL, 0) != 0) {
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
  } else {
    res[0] = '\0';
    flag = 1;
  }
  regfree(&regex);
  return flag;
}
void flagc(char *buffer, char **template, int *count, char *flags) {
  regex_t regex;
  if (strchr(flags, 'i') != NULL) {
    if (regcomp(&regex, *template, REG_ICASE) != 0) {
      error_print(6);
    }
  } else {
    if (regcomp(&regex, *template, 0) != 0) {
      error_print(6);
    }
  }
  if (strchr(flags, 'v') == NULL) {
    if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
      *count = *count + 1;
    }
  } else {
    if (regexec(&regex, buffer, 0, NULL, 0) != 0) {
      *count = *count + 1;
    }
  }
  regfree(&regex);
}
void flagn(char *buffer, char *res, char **template, int *countn) {
  regex_t regex;
  int j = 0;
  if (regcomp(&regex, *template, 0) != 0) {
    error_print(6);
  }

  if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
    if (*countn < 10) {
      res[0] = *countn + '0';
      res[1] = ':';
      j += 2;
    } else if (*countn < 100) {
      res[0] = (*countn / 10) + '0';
      res[1] = (*countn % 10) + '0';
      res[2] = ':';
      j += 3;
    } else {
      res[0] = (*countn / 100) + '0';
      res[1] = (*countn / 10 % 10) + '0';
      res[2] = (*countn % 100 % 10) + '0';
      res[3] = ':';
      j += 4;
    }
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[j] = buffer[i];
      j++;
    }
  }
  regfree(&regex);
}
void flagh(char *buffer, char *res, char **template) {
  regex_t regex;
  if (regcomp(&regex, *template, 0) != 0) {
    error_print(6);
  }

  if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
  }

  regfree(&regex);
}
void flago(char *buffer, char *res, char **template, char *flags, int *countn) {
  regex_t regex;
  int j = 0;
  int match_count = 0;
  if (strchr(flags, 'i') != NULL) {
    if (regcomp(&regex, *template, REG_ICASE | REG_EXTENDED) != 0) {
      error_print(6);
    }
  } else {
    if (regcomp(&regex, *template, REG_EXTENDED) != 0) {
      error_print(6);
    }
  }
  regmatch_t matches[1];
  while (regexec(&regex, buffer, 1, matches, 0) == 0) {
    match_count++;

    for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
      res[j] = buffer[i];
      j++;
    }

    if (strchr(flags, 'n') != NULL && match_count < 2) {
      multiflagn(res, countn);
    }
    j = str_lenght(res);
    res[j] = '\n';
    j++;
    buffer += matches[0].rm_eo;
  }
  regfree(&regex);
}
int flagl(char *buffer, char **template) {
  int flagfile = 0;
  regex_t regex;

  if (regcomp(&regex, *template, 0) != 0) {
    error_print(6);
  }
  if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
    flagfile = 1;
  }
  regfree(&regex);
  return flagfile;
}
void flagf(char *buffer, char *res, char **template, char **fileline,
           int *check, int *line, int *flagcountfile) {
  *template = *template;
  if (*check == 1) {
    error_print(7);
  } else {
    if (*flagcountfile == 0) {
      for (int i = 0; i < str_lenght(buffer); i++) {
        fileline[*line][i] = buffer[i];
      }
      *line = *line + 1;
    }
    if (*flagcountfile > 0) {
      for (int i = 0; i < *line; i++) {
        if (strcmp(fileline[i], buffer) != 0) {
          for (int j = 0; j < str_lenght(buffer); j++) {
            res[j] = buffer[j];
          }
        }
      }
    }
  }
}
void flagS(char *buffer, char *res, char **template) {
  regex_t regex;

  if (regcomp(&regex, *template, 0) != 0) {
    error_print(6);
  }
  if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
  }
  regfree(&regex);
}
