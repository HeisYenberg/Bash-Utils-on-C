#ifndef MY_GREP_H
#define MY_GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e, i, v, c, l, n, h, s, f, o;
  int files, read_pattern, read_pattern_e, error;
} Flag;

int check_for_pattern(int *patterns, int place, Flag flags);
void grep_function(regex_t regex, char *argv, Flag *flags);
regex_t read_argv(int argc, char **argv, Flag *flags, int *patterns);
int get_flags(char *argv, Flag *flags, char **mult_patterns, int *patterns,
              int position);
int grep_output(char *argv, char *search_string, Flag *flags);
void grep_flag_f(Flag *flags, char *argv, char **mult_patterns);
void grep_flag_e(Flag *flags, char *argv, char **mult_patterns);
int grep_flag_o(regex_t regex, char *search_string, char *argv, Flag *flags);
void print_error(char incorrect_flag);

#endif  // MY_GREP_H