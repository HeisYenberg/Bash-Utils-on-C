#include "my_cat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    Flag flags = {0, 0, 0, 0, 0, 0, '\0', '\n'};
    if (read_args(argc, argv, &flags)) {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') continue;
        FILE *file = fopen(argv[i], "r");
        if (file)
          cat_function(file, &flags);
        else
          fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      }
    }
  }
}

void cat_function(FILE *file, Flag *flag) {
  for (char ch = '0'; (ch = fgetc(file)) != EOF;) {
    if ((flag->second_to_last == '\n') && flag->last == '\n' && ch == '\n' &&
        flag->s) {
      continue;
    }
    if (flag->last == '\n' && flag->n && !flag->b) printf("%6d\t", flag->n++);
    if (flag->last == '\n' && ch != '\n' && flag->b) printf("%6d\t", flag->b++);
    if (flag->t && ch == '\t') {
      printf("^");
      ch = 'I';
    }
    if (flag->e && ch == '\n') {
      printf("$");
    }
    if (flag->v) {
      if (ch < 32 && ch != 9 && ch != 10) {
        ch += 64;
        printf("^");
      }
      if (ch == 127) {
        ch -= 64;
        printf("^");
      }
    }
    flag->second_to_last = flag->last;
    flag->last = ch;
    printf("%c", ch);
  }
#ifdef MAC
  flag->second_to_last = '\0';
  flag->last = '\n';
  if (flag->b) flag->b = 1;
  if (flag->n) flag->n = 1;
#endif
  fclose(file);
}

int read_args(int argc, char **argv, Flag *flags) {
  int status = 1;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--squeeze-blank") || !strcmp(argv[i], "--number") ||
        !strcmp(argv[i], "--number-nonblank")) {
      if (!strcmp(argv[i], "--squeeze-blank"))
        flags->s = 1;
      else if (!strcmp(argv[i], "--number"))
        flags->n = 1;
      else
        flags->b = 1;
    } else if (argv[i][0] == '-') {
      if (!get_flags(argv[i], flags)) {
        status = 0;
        break;
      }
    }
  }
  return status;
}

int get_flags(char *argv, Flag *flags) {
  int status = 1, end_of_argv = strlen(argv);
  for (int i = 1; i < end_of_argv; i++) {
    if (argv[i] == 's')
      flags->s = 1;
    else if (argv[i] == 'n')
      flags->n = 1;
    else if (argv[i] == 'b')
      flags->b = 1;
    else if (argv[i] == 't') {
      flags->t = 1;
      flags->v = 1;
    } else if (argv[i] == 'T')
      flags->t = 1;
    else if (argv[i] == 'e') {
      flags->e = 1;
      flags->v = 1;
    } else if (argv[i] == 'E')
      flags->e = 1;
    else if (argv[i] == 'v')
      flags->v = 1;
    else {
      fprintf(stderr,
              "cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n",
              argv[i]);
      status = 0;
    }
  }
  return status;
}