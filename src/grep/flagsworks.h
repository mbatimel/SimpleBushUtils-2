#ifndef FLAGSWORKS_H
char *returntemplate(char **argv, int argc);

void flage(char *buffer, char *res, char **template);
void flagi(char *buffer, char *res, char **template);
int flagv(char *buffer, char *res, char **template, char *flags);
void flagc(char *buffer, char **template, int *count, char *flags);
void flagn(char *buffer, char *res, char **template, int *countn);
void flagh(char *buffer, char *res, char **template);
void flago(char *buffer, char *res, char **template, char *flags, int *countn);
int flagl(char *buffer, char **template);
void flagf(char *buffer, char *res, char **template, char **fileline,
           int *check, int *line, int *flagcountfile);
void flagS(char *buffer, char *res, char **template);
#endif
