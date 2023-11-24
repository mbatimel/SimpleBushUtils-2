
#include "flags.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/flagarr.h"
void workflagb(char *buffer, int *count, char *res) {
  if (*buffer != '\n') {
    if (*count < 10) {
      res[0] = ' ';
      res[1] = ' ';
      res[2] = ' ';
      res[3] = ' ';
      res[4] = ' ';
      res[5] = *count + '0';
      res[6] = '\t';
      for (int i = 0; i < str_lenght(buffer); i++) {
        res[i + 7] = buffer[i];
      }

    } else if (*count < 100 && *count >= 10) {
      res[0] = ' ';
      res[1] = ' ';
      res[2] = ' ';
      res[3] = ' ';
      res[4] = (*count / 10) + '0';
      res[5] = (*count % 10) + '0';
      res[6] = '\t';
      for (int i = 0; i < str_lenght(buffer); i++) {
        res[i + 7] = buffer[i];
      }
    } else if (*count < 1000 && *count >= 100) {
      res[0] = ' ';
      res[1] = ' ';
      res[2] = ' ';
      res[3] = (*count / 100) + '0';
      res[4] = ((*count % 100) / 10) + '0';
      res[5] = (*count % 10) + '0';
      res[6] = '\t';
      for (int i = 0; i < str_lenght(buffer); i++) {
        res[i + 7] = buffer[i];
      }
    }
  } else {
    res[0] = '\n';
    *count -= 1;
  }
}
void workflagbforres(int *count, char *res) {
  char *mezres = calloc(sizeof(char), 256);
  if (*res != '\n') {
    if (*count < 10) {
      mezres[0] = ' ';
      mezres[1] = ' ';
      mezres[2] = ' ';
      mezres[3] = ' ';
      mezres[4] = ' ';
      mezres[5] = *count + '0';
      mezres[6] = '\t';
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i + 7] = res[i];
      }

    } else if (*count < 100 && *count >= 10) {
      mezres[0] = ' ';
      mezres[1] = ' ';
      mezres[2] = ' ';
      mezres[3] = ' ';
      mezres[4] = (*count / 10) + '0';
      mezres[5] = (*count % 10) + '0';
      mezres[6] = '\t';
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i + 7] = res[i];
      }
    } else if (*count < 1000 && *count >= 100) {
      mezres[0] = ' ';
      mezres[1] = ' ';
      mezres[2] = ' ';
      mezres[3] = (*count / 100) + '0';
      mezres[4] = ((*count % 100) / 10) + '0';
      mezres[5] = (*count % 10) + '0';
      mezres[6] = '\t';
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i + 7] = res[i];
      }
    }
  } else {
    mezres[0] = '\n';
    *count -= 1;
  }
  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }

  free(mezres);
}
void workflage(char *buffer, char *res) {
  for (int i = 0; i < str_lenght(buffer); i++) {
    if (i == str_lenght(buffer) - 1 && buffer[i] == '\n') {
      res[i] = '$';
    } else {
      res[i] = buffer[i];
    }
  }
  res[str_lenght(res)] = '\n';
}
void workflageforres(char *res) {
  char *mezres = calloc(sizeof(char), 256);
  for (int i = 0; i < str_lenght(res); i++) {
    if (i == str_lenght(res) - 1 && res[i] == '\n') {
      mezres[i] = '$';
    } else {
      mezres[i] = res[i];
    }
  }

  mezres[str_lenght(mezres)] = '\n';
  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }
  free(mezres);
}
void workflagn(char *buffer, int *count, char *res) {
  if (*count < 10) {
    res[0] = ' ';
    res[1] = ' ';
    res[2] = ' ';
    res[3] = ' ';
    res[4] = ' ';
    res[5] = *count + '0';
    res[6] = '\t';
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i + 7] = buffer[i];
    }

  } else if (*count < 100 && *count >= 10) {
    res[0] = ' ';
    res[1] = ' ';
    res[2] = ' ';
    res[3] = ' ';
    res[4] = (*count / 10) + '0';
    res[5] = (*count % 10) + '0';
    res[6] = '\t';
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i + 7] = buffer[i];
    }
  } else if (*count < 1000 && *count >= 100) {
    res[0] = ' ';
    res[1] = ' ';
    res[2] = ' ';
    res[3] = (*count / 100) + '0';
    res[4] = ((*count % 100) / 10) + '0';
    res[5] = (*count % 10) + '0';
    res[6] = '\t';
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i + 7] = buffer[i];
    }
  }
}
void workflagnforres(int *count, char *res) {
  char *mezres = calloc(sizeof(char), 256);
  if (*count < 10) {
    mezres[0] = *count + '0';
    mezres[1] = '\t';
    for (int i = 0; i < str_lenght(res); i++) {
      mezres[i + 2] = res[i];
    }
  } else {
    mezres[0] = (*count / 10) + '0';
    mezres[1] = (*count % 10) + '0';
    mezres[2] = '\t';
    for (int i = 0; i < str_lenght(res); i++) {
      mezres[i + 3] = res[i];
    }
  }
  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }
  free(mezres);
}
int workflags(char *buffer, char *res, int *countnull) {
  int flag = 0;
  if (buffer[0] == '\n') {
    if (*countnull == 0) {
      *countnull = 1;
      res[0] = '\n';

    } else {
      flag = 1;
    }

  } else {
    *countnull = 0;
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
  }
  res[str_lenght(buffer)] = '\0';
  return flag;
}
int workflagsforres(char *res, int *countnull) {
  char *mezres = calloc(sizeof(char), 256);
  int flag = 0;
  if ((res[0] == '\n') || (str_lenght(res) < 3 && strchr(res, '$')) ||
      ((str_lenght(res) == 8))) {
    if (*countnull == 0) {
      *countnull = 1;
      for (int i = 0; i < str_lenght(res); i++) {
        mezres[i] = res[i];
      }
    } else {
      flag = 1;
    }

  } else if ((*res != '\n') || (str_lenght(res) > 2)) {
    *countnull = 0;
    for (int i = 0; i < str_lenght(res); i++) {
      mezres[i] = res[i];
    }
  }
  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }

  free(mezres);
  return flag;
}
void workflagt(char *buffer, char *res) {
  int j = 0;
  if (strchr(buffer, '\t') != NULL) {
    for (int i = 0; i < str_lenght(buffer); i++) {
      if (buffer[i] == '\t') {
        res[j] = '^';
        res[j + 1] = 'I';
        j += 2;

      } else {
        res[j] = buffer[i];
        j++;
      }
    }
    res[j] = '\0';
  } else {
    for (int i = 0; i < str_lenght(buffer); i++) {
      res[i] = buffer[i];
    }
    res[str_lenght(buffer)] = '\0';
  }
}
void workflagtforres(char *res, char *flags) {
  char *mezres = calloc(sizeof(char), 256);
  int counttab = 0;

  if ((strchr(flags, 'b') != NULL) || (strchr(flags, 'n') != NULL)) {
    counttab = 1;
  }

  int j = 0;
  if (strchr(res, '\t') != NULL) {
    for (int i = 0; i < str_lenght(res); i++) {
      if (res[i] == '\t') {
        if (counttab == 1) {
          counttab = 0;
          mezres[j] = res[i];
          j++;
        } else {
          mezres[j] = '^';
          mezres[j + 1] = 'I';
          j += 2;
        }

      } else {
        mezres[j] = res[i];
        j++;
      }
    }

  } else {
    for (int i = 0; i < str_lenght(res); i++) {
      mezres[i] = res[i];
    }
  }
  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }
  free(mezres);
}

void workflagVforres(char *res) {
  int count = 0;
  char *mezres = calloc(sizeof(char), 256);

  for (int i = 0; i < str_lenght(res); i++) {
    if (res[i] >= 0 && res[i] <= 31 && res[i] != '\n' && res[i] != '\r' &&
        res[i] != '\t') {
      mezres[count] = '^';
      mezres[count + 1] = res[i] + 64;
      count += 2;
    } else if (res[i] == 127) {
      mezres[count] = '^';
      mezres[count + 1] = '?';
      count += 2;
    } else {
      mezres[count] = res[i];
      count++;
    }
  }

  memset(res, 0, 256);

  for (int i = 0; i < str_lenght(mezres); i++) {
    res[i] = mezres[i];
  }

  res[str_lenght(mezres)] = '\0';
  free(mezres);
}

void workflagV(char *buffer, char *res) {
  int count = 0;
  for (int i = 0; i < str_lenght(buffer); i++) {
    if (buffer[i] >= 0 && buffer[i] <= 31 && buffer[i] != '\n' &&
        buffer[i] != '\r' && buffer[i] != '\t') {
      res[count] = '^';
      res[count + 1] = buffer[i] + 64;
      count += 2;
    } else if (buffer[i] == 127) {
      res[count] = '^';
      res[count + 1] = '?';
      count += 2;
    } else {
      res[count] = buffer[i];
      count++;
    }
  }
}
