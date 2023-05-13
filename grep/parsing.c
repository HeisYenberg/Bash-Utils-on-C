#include "s21_grep.h"

regex_t read_argv(int argc, char **argv, Flag *flags, Patterns *patterns) {
  regex_t regex;
  int reg_flag = 0, error = 0;
  char *mult_patterns = calloc(100, sizeof(char));
  for (int i = 1; i < argc; i++) {
    if (flags->e) {
      if (flags->read_pattern_e < 256)
        patterns[flags->read_pattern_e].place = i;
      else
        flags->error = 1;
      grep_flag_e(regex, flags, argv[i], &mult_patterns);
    } else if (flags->f) {
      if (flags->read_pattern_e < 256)
        patterns[flags->read_pattern_e].place = i;
      else
        flags->error = 1;
      grep_flag_f(regex, flags, argv[i], &mult_patterns);
    } else if (argv[i][0] == '-') {
      if (!get_flags(argv[i], flags, &mult_patterns, regex, patterns, i)) {
        flags->error = 1;
      }
    } else if (!flags->f && !flags->read_pattern && !flags->read_pattern_e) {
      error = regcomp(&regex, argv[i], reg_flag);
      flags->read_pattern = i;
    } else
      flags->files += 1;
  }
  if (flags->i && !reg_flag) reg_flag |= REG_ICASE;
  if (flags->read_pattern_e) reg_flag |= REG_EXTENDED;
  reg_flag |= REG_NEWLINE;
  if (flags->read_pattern_e) {
    error = regcomp(&regex, mult_patterns, reg_flag);
  }
  if (error) flags->error = 1;
  if (mult_patterns) free(mult_patterns);
  return regex;
}

int get_flags(char *argv, Flag *flags, char **mult_patterns, regex_t regex,
              Patterns *patterns, int position) {
  int status = 1, i = 1, end_of_arg = strlen(argv);
  for (; i < end_of_arg; i++) {
    if (argv[i] == 'e') {
      flags->e = 1;
      break;
    } else if (argv[i] == 'i')
      flags->i = 1;
    else if (argv[i] == 'v')
      flags->v = 1;
    else if (argv[i] == 'c')
      flags->c = 1;
    else if (argv[i] == 'l')
      flags->l = 1;
    else if (argv[i] == 'n')
      flags->n = 1;
    else if (argv[i] == 'h')
      flags->h = 1;
    else if (argv[i] == 's')
      flags->s = 1;
    else if (argv[i] == 'f') {
      flags->f = 1;
      break;
    } else if (argv[i] == 'o')
      flags->o = 1;
    else {
      status = 0;
      break;
    }
  }
  if (!status && !flags->error) {
    fprintf(stderr,
            "grep: invalid option -- '%c'\nUsage: grep [OPTION]... PATTERNS "
            "[FILE]...\n",
            argv[i]);
  }
  if (flags->e && i != (end_of_arg - 1)) {
    if (flags->e < 256)
      patterns[flags->read_pattern_e].place = position;
    else
      flags->error = 1;
    grep_flag_e(regex, flags, argv + (i + 1), mult_patterns);
  }
  if (flags->f && i != (end_of_arg - 1) && !flags->s && !flags->error) {
    if (flags->e < 256)
      patterns[flags->read_pattern_e].place = position;
    else
      flags->error = 1;
    grep_flag_f(regex, flags, argv + (i + 1), mult_patterns);
  }
  return status;
}