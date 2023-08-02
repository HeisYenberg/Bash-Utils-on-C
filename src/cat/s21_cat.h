#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <string.h>

typedef struct flags {
  int s, n, b, t, e, v;
  char second_to_last, last;
} Flag;

int read_args(int argc, char **argv, Flag *flags);
int get_flags(char *argv, Flag *flags);
void cat_function(FILE *file, Flag *flag);

#endif