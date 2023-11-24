
#include "flagarr.h"
void addflags(char flag, char *arr) {
  int res = checkfalgs(flag, arr);
  if (res == 0) {
    for (int i = 0; i < 10; i++) {
      if (arr[i] == '\0') {
        arr[i] = flag;
        break;
      }
    }
  }
}

int checkfalgs(char flag, char *arr) {
  int check = 0;
  for (int i = 0; i < 10; i++) {
    if (arr[i] == flag) {
      check = 1;
    }
  }
  return check;
}
int str_lenght(char *str) {
  int i = 0;
  for (i = 0; str[i] != '\0'; i++)
    ;
  return i;
}
char *return_filename(char **argv, int argc, char *flags) {
  char *result = (char *)malloc(256 * sizeof(char));
  result[0] = '\0';
  int found = 0;

  for (int i = 1; i < argc; i++) {
    if ((strstr(argv[0], "./s21_cat") != NULL && argv[i][0] != '-')) {
      if (found) {
        strcat(result, " ");
      }
      strcat(result, argv[i]);
      found = 1;
    }
    if (strstr(argv[0], "./s21_grep") != NULL && argv[i][0] != '-') {
      if (strchr(flags, 'f') != NULL) {
        if (found) {
          strcat(result, " ");
        }
        strcat(result, argv[i]);
        found = 1;
      } else if (str_lenght(flags) == 0) {
        if (i > 1) {
          if (found) {
            strcat(result, " ");
          }
          strcat(result, argv[i]);
          found = 1;
        }
      } else {
        if (argv[i - 1][0] != '-') {
          if (found) {
            strcat(result, " ");
          }
          strcat(result, argv[i]);
          found = 1;
        }
      }
    }
  }

  return result;
}
int count_files(const char *filename) {
  int count = 0;
  char *copy = my_strdup(filename);
  char *token = strtok(copy, " ");

  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
  }

  free(copy);
  return count;
}
char *returntemplate(char **argv, int argc) {
  char *result = (char *)malloc(256 * sizeof(char));
  result[0] = '\0';

  for (int i = 0; i < argc; i++) {
    if (strchr(argv[i], '-') == NULL && i != argc - 1 && i != 0 &&
        strstr(argv[i], ".txt") == NULL) {
      strcat(result, argv[i]);
      strcat(result, (i < argc - 2) ? " " : "");
    }
  }

  return result;
}
char *my_strdup(const char *s) {
  size_t len = strlen(s) + 1;
  char *new_str = malloc(len);
  if (new_str == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  strcpy(new_str, s);
  return new_str;
}
