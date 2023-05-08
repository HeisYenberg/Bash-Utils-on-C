CC = gcc -Wall -Werror -Wextra

all : s21_grep test run_test

s21_grep :
	$(CC) s21_grep.c parsing.c grep_flags.c -o s21_grep

test :
	$(CC)  test.c -o test

run_test :
	./test

rebuild : clean s21_grep test

run_test_mac : clean s21_grep_mac test run_test

s21_grep_mac :
	$(CC) s21_grep.c parsing.c grep_flags.c -D MAC -o s21_grep

clean :
	rm -rf s21_grep test