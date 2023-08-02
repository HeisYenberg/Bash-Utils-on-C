CC = gcc -Wall -Werror -Wextra

all : my_grep test run_test

my_grep :
	$(CC) my_grep.c parsing.c grep_flags.c -o my_grep

test :
	$(CC)  test.c -o test

run_test :
	./test

rebuild : clean my_grep test

run_test_mac : clean my_grep_mac test run_test

s21_grep_mac :
	$(CC) my_grep.c parsing.c grep_flags.c -D MAC -o my_grep

clang :
	clang-format -style=Google -i  *.c *.h

clean :
	rm -rf my_grep test