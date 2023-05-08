#include "s21_grep.h"

void grep_flag_f(regex_t regex, Flag *flags, char *argv, char **mult_patterns) {
  if (flags->read_pattern) {
    flags->read_pattern = 0;
    flags->files++;
    regfree(&regex);
  }
  FILE *file = fopen(argv, "r");
  if (file) {
    char file_string[4097];
    int read = 0;
    if (flags->read_pattern_e) read = 1;
    while (fgets(file_string, 4096, file) && !flags->error) {
      *mult_patterns = realloc(
          *mult_patterns, (strlen(*mult_patterns) + 2 + strlen(file_string)));
      if (!*mult_patterns) {
        flags->error = 1;
        break;
      }
      if (read) {
        strcat(*mult_patterns, "|");
        if (file_string[strlen(file_string) - 1] == '\n' &&
            file_string[0] != '\n')
          file_string[strlen(file_string) - 1] = '\0';
        strcat(*mult_patterns, file_string);
      } else {
        read = 1;
        if (file_string[strlen(file_string) - 1] == '\n' &&
            file_string[0] != '\n')
          file_string[strlen(file_string) - 1] = '\0';
        sprintf(*mult_patterns, "%s", file_string);
      }
    }
    fclose(file);
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", argv);
    flags->error = 1;
  }
  flags->read_pattern_e++;
  flags->f = 0;
}

void grep_flag_e(regex_t regex, Flag *flags, char *argv, char **mult_patterns) {
  if (flags->read_pattern) {
    flags->read_pattern = 0;
    flags->files++;
    regfree(&regex);
  }
  *mult_patterns =
      realloc(*mult_patterns, (strlen(*mult_patterns) + strlen(argv) + 2));
  if (*mult_patterns) {
    if (flags->read_pattern_e) {
      strcat(*mult_patterns, "|");
      strcat(*mult_patterns, argv);
    } else
      sprintf(*mult_patterns, "%s", argv);
    flags->read_pattern_e++;
    flags->e = 0;
  } else
    flags->error = 1;
}

int grep_flag_o(regex_t regex, char *search_string, char *argv, Flag *flags) {
  int status = 1;
  regmatch_t pm[1];
  char *buffer = search_string;
  int no_match = regexec(&regex, buffer, 1, pm, 0);
  if (!no_match && !flags->v) {
    if (flags->l) {
#ifdef MAC
      flags->l++;
      if (flags->c) flags->c++;
#else
      printf("%s\n", argv);
#endif
      status = 0;
    } else {
      if (flags->c)
        flags->c++;
      else {
#ifdef MAC
        if (flags->files > 1 && !flags->h && !flags->c) printf("%s:", argv);
        if (flags->n) printf("%d:", flags->n);
#endif
        while (!no_match) {
#ifndef MAC
          if (flags->files > 1 && !flags->h && !flags->c) printf("%s:", argv);
          if (flags->n) printf("%d:", flags->n);
#endif
          for (int i = pm[0].rm_so; i < pm[0].rm_eo; i++) {
            printf("%c", buffer[i]);
          }
          printf("\n");
          no_match = regexec(&regex, buffer += pm[0].rm_eo, 1, pm, REG_NOTEOL);
        }
      }
    }
#ifndef MAC
  } else if (no_match && flags->v) {
    if (flags->l) {
      printf("%s\n", argv);
      status = 0;
    } else if (flags->c)
      flags->c++;
#else
  } else if (no_match && flags->v) {
    if (!grep_output(argv, search_string, flags)) status = 0;
#endif
  }
  return status;
}