
#include "errors.h"

void error_print(int errorcode) {
  switch (errorcode) {
    case 1:
      fprintf(stderr, "No such file or directory\n");
      break;
    case 2:
      fprintf(stderr, "flag file\n");
      break;
    case 3:
      fprintf(stderr, "empty file\n");
      break;
    case 4:
      fprintf(stderr, "unknown flag\n");
      break;
    case 5:
      fprintf(stderr,
              "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
              "[-C[num]]\n[-e pattern] [-f file] [--binary-files=value] "
              "[--color=when]\n[--context[=num]] [--directories=action] "
              "[--label] [--line-buffered]\n[--null] [pattern] [file ...]\n");
      break;
    case 6:
      fprintf(stderr, "Regular expression compilation error\n");
      break;
    case 7:
      fprintf(stderr, "\n");
      break;
    default:
      break;
  }
}
