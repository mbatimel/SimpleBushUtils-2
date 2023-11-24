#include "multiflags.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/errors.h"
#include "../common/flagarr.h"
void multiflagn(char *res, int *countn) {
  int j = 0;

  char *mezres = calloc(sizeof(char), 1000);

  if (*countn < 10) {
    mezres[0] = *countn + '0';
    mezres[1] = ':';
    j += 2;
  } else if (*countn < 100) {
    mezres[0] = (*countn / 10) + '0';
    mezres[1] = (*countn % 10) + '0';
    mezres[2] = ':';
    j += 3;
  } else {
    mezres[0] = (*countn / 100) + '0';
    mezres[1] = (*countn / 10 % 10) + '0';
    mezres[2] = (*countn % 100 % 10) + '0';
    mezres[3] = ':';
    j += 4;
  }
  for (int i = 0; i < str_lenght(res); i++) {
    mezres[j] = res[i];
    j++;
  }

  innerres(res, mezres);
  free(mezres);
}
void multiflagc(char *res, int **count) {
  char *mezres = calloc(sizeof(char), 1000);

  if (res[0] != '\0') {
    **count = **count + 1;
  }
  mezres[0] = **count + '0';
  mezres[1] = '\n';
  innerres(res, mezres);
  free(mezres);
}
void innerres(char *res, char *mezres) {
  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }
}
void multiflagv(char *res, char **template, char *flags) {
  regex_t regex;
  char *mezres = calloc(sizeof(char), 1000);

  if (strchr(flags, 'i') != NULL) {
    if (regcomp(&regex, *template, REG_ICASE) != 0) {
      error_print(6);
    }
    if (regexec(&regex, res, 0, NULL, 0) != 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      res[0] = '\0';
    }
  } else {
    if (regcomp(&regex, *template, 0) != 0) {
      error_print(6);
    }
    if (regexec(&regex, res, 0, NULL, 0) != 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      res[0] = '\0';
    }
  }
  regfree(&regex);
  innerres(res, mezres);
  free(mezres);
}
void multiflagh(char *res, char **template, char *flags) {
  regex_t regex;
  char *mezres = calloc(sizeof(char), 1000);
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
    if (regexec(&regex, res, 0, NULL, 0) == 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      res[0] = '\0';
    }
  } else {
    if (regexec(&regex, res, 0, NULL, 0) != 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      res[0] = '\0';
    }
  }
  regfree(&regex);
  innerres(res, mezres);
  free(mezres);
}
void multiflagi(char *res, char **template) {
  regex_t regex;
  char *mezres = calloc(sizeof(char), 1000);
  if (regcomp(&regex, *template, REG_ICASE) != 0) {
    error_print(6);
  }
  if (regexec(&regex, res, 0, NULL, 0) == 0) {
    for (int i = 0; i < str_lenght(res); i++) {
      mezres[i] = res[i];
    }
  }
  regfree(&regex);
  innerres(res, mezres);
  free(mezres);
}
void multiflago(char *res, char **template, char *flags, int *countn) {
  regex_t regex;
  int j = 0;

  char *mezres = calloc(sizeof(char), 1000);
  if (regcomp(&regex, *template, REG_EXTENDED) != 0) {
    error_print(6);
  }
  regmatch_t matches[1];
  if (strchr(flags, 'v') != NULL) {
    if (regexec(&regex, res, 1, NULL, 0) != 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      mezres[0] = '\0';
    }

  } else {
    while (regexec(&regex, res, 1, matches, 0) == 0) {
      for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
        mezres[j++] = res[i];
      }

      mezres[j++] = '\n';

      res += matches[0].rm_eo;
    }
  }
  if (strchr(flags, 'n') != NULL) {
    multiflagn(mezres, countn);
  }
  regfree(&regex);
  innerres(res, mezres);
  free(mezres);
}
void multiflags(char *res, char **template, char *flags) {
  regex_t regex;
  char *mezres = calloc(sizeof(char), 1000);
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
    if (regexec(&regex, res, 0, NULL, 0) == 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      res[0] = '\0';
    }
  } else if (strchr(flags, 'v') != NULL) {
    if (regexec(&regex, res, 0, NULL, 0) != 0) {
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      res[0] = '\0';
    }
  }
  regfree(&regex);
  innerres(res, mezres);
  free(mezres);
}
