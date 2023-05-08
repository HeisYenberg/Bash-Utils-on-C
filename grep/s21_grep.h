#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e, i, v, c, l, n, h, s, f, o;
  int files, read_pattern, read_pattern_e, error;
} Flag;

typedef struct patterns {
  int place;
} Patterns;

int check_for_pattern(Patterns *patterns, int place, Flag flags);
void grep_function(regex_t regex, char *argv, Flag *flags);
regex_t read_argv(int argc, char **argv, Flag *flags, Patterns *patterns);
int get_flags(char *argv, Flag *flags, char **mult_patterns, regex_t regex,
              Patterns *patterns, int position);
int grep_output(char *argv, char *search_string, Flag *flags);
void grep_flag_f(regex_t regex, Flag *flags, char *argv, char **mult_patterns);
void grep_flag_e(regex_t regex, Flag *flags, char *argv, char **mult_patterns);
int grep_flag_o(regex_t regex, char *search_string, char *argv, Flag *flags);

#endif