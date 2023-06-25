#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    Flag flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int patterns[256];
    regex_t regex = read_argv(argc, argv, &flags, patterns);
    if (!flags.error) {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' || check_for_pattern(patterns, i, flags) ||
            i == flags.read_pattern)
          continue;
        grep_function(regex, argv[i], &flags);
      }
    }
    if (flags.read_pattern || flags.read_pattern_e) regfree(&regex);
  } else
    fprintf(stderr,
            "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
            "more information.\n");
}

int check_for_pattern(int *patterns, int position, Flag flags) {
  int status = 0;
  for (int i = 0; i < flags.read_pattern_e; i++) {
    if (patterns[i] == position) status = 1;
  }
  return status;
}

void grep_function(regex_t regex, char *argv, Flag *flags) {
  FILE *file = fopen(argv, "r");
  if (file) {
    char search_string[4097];
    while (fgets(search_string, 4096, file)) {
      if (flags->o) {
        if (!grep_flag_o(regex, search_string, argv, flags)) break;
      } else if (!regexec(&regex, search_string, 0, NULL, 0) && !flags->v) {
        if (!grep_output(argv, search_string, flags)) break;
      } else if (regexec(&regex, search_string, 0, NULL, 0) && flags->v) {
        if (!grep_output(argv, search_string, flags)) break;
      }
      if (flags->n) flags->n++;
    }
#ifdef MAC
    if (flags->files > 1 && !flags->h && flags->c) printf("%s:", argv);
    if (flags->c) {
#else
    if (flags->files > 1 && !flags->h && flags->c && !flags->l)
      printf("%s:", argv);
    if (flags->c && !flags->l) {
#endif
      printf("%d\n", flags->c - 1);
      flags->c = 1;
    }
#ifdef MAC
    if (flags->l > 1) {
      printf("%s\n", argv);
      flags->l = 1;
    }
#endif
    if (flags->n) flags->n = 1;
    fclose(file);
  } else {
    if (!flags->s)
      fprintf(stderr, "grep: %s: No such file or directory\n", argv);
  }
}

int grep_output(char *argv, char *search_string, Flag *flags) {
  int status = 1;
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
      if (!flags->h && flags->files > 1) printf("%s:", argv);
      if (flags->n) printf("%d:", flags->n);
      printf("%s", search_string);
      if (search_string[strlen(search_string) - 1] != '\n') printf("\n");
    }
  }
  return status;
}