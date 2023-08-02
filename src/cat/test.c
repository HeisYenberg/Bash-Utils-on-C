#include <stdio.h>
#include <stdlib.h>

#ifndef MAC
#define TEST 11
#else
#define TEST 6
#endif

void test_cat_one_file(char flags[11][18], int *test);
void test_cat_two_files(char flags[11][18], int *test);
void test_cat_three_files(char flags[11][18], int *test);
void all_at_once(int *test);

int main() {
  char flags[11][18] = {"-s",
                        "-n",
                        "-b",
                        "-t",
                        "-v",
                        "-e",
                        "-E",
                        "-T",
                        "--number",
                        "--number-nonblank",
                        "--squeeze-blank"};
  int test = 1;
  test_cat_one_file(flags, &test);
  test_cat_two_files(flags, &test);
  test_cat_three_files(flags, &test);
#ifndef MAC
  all_at_once(&test);
#endif
  system("rm -rf cat.log my_cat.log");
}

void test_cat_one_file(char flags[11][18], int *test) {
  char my_cat[200], cat[200];
  for (int i = 0; i < TEST; i++) {
    sprintf(my_cat, "./my_cat %s my_cat.c > my_cat.log", flags[i]);
    sprintf(cat, "cat %s my_cat.c > cat.log", flags[i]);
    system(my_cat);
    system(cat);
    if (!system("diff -s -q cat.log my_cat.log"))
      printf("\033[0;32mTEST NUMBER %d %s\nSUCCESS\n", *test, flags[i]);
    else
      printf("\033[0;31mTEST NUMBER %d %s\nFAIL\n", *test, flags[i]);
    (*test)++;
    for (int j = 0; j < TEST; j++) {
      sprintf(my_cat, "./my_cat %s %s my_cat.c > my_cat.log", flags[i],
              flags[j]);
      sprintf(cat, "cat %s %s my_cat.c > cat.log", flags[i], flags[j]);
      system(my_cat);
      system(cat);
      if (!system("diff -s -q cat.log my_cat.log"))
        printf("\033[0;32mTEST NUMBER %d %s %s\nSUCCESS\n", *test, flags[i],
               flags[j]);
      else
        printf("\033[0;31mTEST NUMBER %d %s %s\nFAIL\n", *test, flags[i],
               flags[j]);
      (*test)++;
    }
  }
}

void test_cat_two_files(char flags[11][18], int *test) {
  char my_cat[200], cat[200];
  for (int i = 0; i < TEST; i++) {
    sprintf(my_cat, "./my_cat %s my_cat.c my_cat.h > my_cat.log", flags[i]);
    sprintf(cat, "cat %s my_cat.c my_cat.h > cat.log", flags[i]);
    system(my_cat);
    system(cat);
    if (!system("diff -s -q cat.log my_cat.log"))
      printf("\033[0;32mTEST NUMBER %d %s\nSUCCESS\n", *test, flags[i]);
    else
      printf("\033[0;31mTEST NUMBER %d %s\nFAIL\n", *test, flags[i]);
    (*test)++;
    for (int j = 0; j < TEST; j++) {
      sprintf(my_cat, "./my_cat %s %s my_cat.c my_cat.h > my_cat.log", flags[i],
              flags[j]);
      sprintf(cat, "cat %s %s my_cat.c my_cat.h > cat.log", flags[i], flags[j]);
      system(my_cat);
      system(cat);
      if (!system("diff -s -q cat.log my_cat.log"))
        printf("\033[0;32mTEST NUMBER %d %s %s\nSUCCESS\n", *test, flags[i],
               flags[j]);
      else
        printf("\033[0;31mTEST NUMBER %d %s %s\nFAIL\n", *test, flags[i],
               flags[j]);
      (*test)++;
    }
  }
}

void test_cat_three_files(char flags[11][18], int *test) {
  char my_cat[200], cat[200];
  for (int i = 0; i < TEST; i++) {
    sprintf(my_cat, "./my_cat %s my_cat.c my_cat.h Makefile > my_cat.log",
            flags[i]);
    sprintf(cat, "cat %s my_cat.c my_cat.h Makefile > cat.log", flags[i]);
    system(my_cat);
    system(cat);
    if (!system("diff -s -q cat.log my_cat.log"))
      printf("\033[0;32mTEST NUMBER %d %s\nSUCCESS\n", *test, flags[i]);
    else
      printf("\033[0;31mTEST NUMBER %d %s\nFAIL\n", *test, flags[i]);
    (*test)++;
    for (int j = 0; j < TEST; j++) {
      sprintf(my_cat, "./my_cat %s %s my_cat.c my_cat.h Makefile > my_cat.log",
              flags[i], flags[j]);
      sprintf(cat, "cat %s %s my_cat.c my_cat.h Makefile > cat.log", flags[i],
              flags[j]);
      system(my_cat);
      system(cat);
      if (!system("diff -s -q cat.log my_cat.log"))
        printf("\033[0;32mTEST NUMBER %d %s %s\nSUCCESS\n", *test, flags[i],
               flags[j]);
      else
        printf("\033[0;31mTEST NUMBER %d %s %s\nFAIL\n", *test, flags[i],
               flags[j]);
      (*test)++;
    }
  }
}

void all_at_once(int *test) {
  system(
      "./my_cat -s -n -b -t -T -e -E -v --number --number-nonblank "
      "--squeeze-blank my_cat.c my_cat.h Makefile > my_cat.log");
  system(
      "cat -s -n -b -t -T -e -E -v --number --number-nonblank --squeeze-blank "
      "my_cat.c my_cat.h Makefile > cat.log");
  if (!system("diff -s -q cat.log my_cat.log"))
    printf("\033[0;32mTEST NUMBER %d ALL FLAGS\nSUCCESS\n", *test);
  else
    printf("\033[0;31mTEST NUMBER %d ALL FLAGS\nFAIL\n", *test);
  (*test)++;
}