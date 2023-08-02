#include <stdio.h>
#include <stdlib.h>

#define TEST 10

void test_grep_one_file(char flags[10][3], char pattern[10][6], int *test);
void test_grep_two_files(char flags[10][3], char pattern[10][6], int *test);
void test_grep_three_files(char flags[10][3], char pattern[10][6], int *test);

int main() {
  char flags[10][3] = {"-o", "-i", "-v", "-c", "-l",
                       "-n", "-h", "-s", "-e", "-f"};
  char patterns[10][6] = {"read",  "reg",  "int",  "argc", "hello",
                          "flags", "void", "char", "grep", "cat"};
  int test = 1;
  test_grep_one_file(flags, patterns, &test);
  test_grep_two_files(flags, patterns, &test);
  test_grep_three_files(flags, patterns, &test);
  system("rm -rf grep.log my_grep.log");
}

void test_grep_one_file(char flags[10][3], char pattern[10][6], int *test) {
  char my_grep[200], grep[200];
  for (int i = 0; i < TEST; i++) {
    sprintf(my_grep, "./my_grep %s %s my_grep.c > my_grep.log", flags[i],
            pattern[i]);
    sprintf(grep, "grep %s %s my_grep.c > grep.log", flags[i], pattern[i]);
    system(my_grep);
    system(grep);
    int diff = system("diff -s -q grep.log my_grep.log | grep identical");
    if (!diff)
      printf("\033[0;32mTEST NUMBER %d %s %s\nSUCCESS\n", *test, flags[i],
             pattern[i]);
    else
      printf("\033[0;31mTEST NUMBER %d %s %s\nFAIL\n", *test, flags[i],
             pattern[i]);
    (*test)++;
    for (int j = 0; j < TEST; j++) {
      sprintf(my_grep, "./my_grep %s %s %s my_grep.c > my_grep.log", flags[i],
              flags[j], pattern[i]);
      sprintf(grep, "grep %s %s %s my_grep.c > grep.log", flags[i], flags[j],
              pattern[i]);
      system(my_grep);
      system(grep);
      diff = system("diff -s -q grep.log my_grep.log | grep identical");
      if (!diff)
        printf("\033[0;32mTEST NUMBER %d %s %s %s\nSUCCESS\n", *test, flags[i],
               flags[j], pattern[i]);
      else
        printf("\033[0;31mTEST NUMBER %d %s %s %s\nFAIL\n", *test, flags[i],
               flags[j], pattern[i]);
      (*test)++;
    }
  }
}

void test_grep_two_files(char flags[10][3], char pattern[10][6], int *test) {
  char my_grep[200], grep[200];
  for (int i = 0; i < TEST; i++) {
    sprintf(my_grep, "./my_grep %s %s my_grep.c my_grep.h > my_grep.log",
            flags[i], pattern[i]);
    sprintf(grep, "grep %s %s my_grep.c my_grep.h > grep.log", flags[i],
            pattern[i]);
    system(my_grep);
    system(grep);
    int diff = system("diff -s -q grep.log my_grep.log | grep identical");
    if (!diff)
      printf("\033[0;32mTEST NUMBER %d %s %s\nSUCCESS\n", *test, flags[i],
             pattern[i]);
    else
      printf("\033[0;31mTEST NUMBER %d %s %s\nFAIL\n", *test, flags[i],
             pattern[i]);
    (*test)++;
    for (int j = 0; j < TEST; j++) {
      sprintf(my_grep, "./my_grep %s %s %s my_grep.c my_grep.h > my_grep.log",
              flags[i], flags[j], pattern[i]);
      sprintf(grep, "grep %s %s %s my_grep.c my_grep.h > grep.log", flags[i],
              flags[j], pattern[i]);
      system(my_grep);
      system(grep);
      diff = system("diff -s -q grep.log my_grep.log | grep identical");
      if (!diff)
        printf("\033[0;32mTEST NUMBER %d %s %s %s\nSUCCESS\n", *test, flags[i],
               flags[j], pattern[i]);
      else
        printf("\033[0;31mTEST NUMBER %d %s %s %s\nFAIL\n", *test, flags[i],
               flags[j], pattern[i]);
      (*test)++;
    }
  }
}

void test_grep_three_files(char flags[10][3], char pattern[10][6], int *test) {
  char my_grep[200], grep[200];
  for (int i = 0; i < TEST; i++) {
    sprintf(my_grep,
            "./my_grep %s %s my_grep.c my_grep.h Makefile > my_grep.log",
            flags[i], pattern[i]);
    sprintf(grep, "grep %s %s my_grep.c my_grep.h Makefile > grep.log",
            flags[i], pattern[i]);
    system(my_grep);
    system(grep);
    int diff = system("diff -s -q grep.log my_grep.log | grep identical");
    if (!diff)
      printf("\033[0;32mTEST NUMBER %d %s %s\nSUCCESS\n", *test, flags[i],
             pattern[i]);
    else
      printf("\033[0;31mTEST NUMBER %d %s %s\nFAIL\n", *test, flags[i],
             pattern[i]);
    (*test)++;
    for (int j = 0; j < TEST; j++) {
      sprintf(my_grep,
              "./my_grep %s %s %s my_grep.c my_grep.h Makefile > my_grep.log",
              flags[i], flags[j], pattern[i]);
      sprintf(grep, "grep %s %s %s my_grep.c my_grep.h Makefile > grep.log",
              flags[i], flags[j], pattern[i]);
      system(my_grep);
      system(grep);
      diff = system("diff -s -q grep.log my_grep.log | grep identical");
      if (!diff)
        printf("\033[0;32mTEST NUMBER %d %s %s %s\nSUCCESS\n", *test, flags[i],
               flags[j], pattern[i]);
      else
        printf("\033[0;31mTEST NUMBER %d %s %s %s\nFAIL\n", *test, flags[i],
               flags[j], pattern[i]);
      (*test)++;
    }
  }
}