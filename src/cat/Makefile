CC = gcc -Wall -Werror -Wextra

all : s21_cat test run_test

s21_cat :
	$(CC) s21_cat.c -o s21_cat

test :
	$(CC)  test.c -o test

run_test :
	./test

run_test_mac : clean s21_cat_mac test_mac run_test

s21_cat_mac :
	$(CC) s21_cat.c -D MAC -o s21_cat

test_mac :
	$(CC)  test.c -D MAC -o test

rebuild : clean s21_cat test

clean :
	rm -rf s21_cat test