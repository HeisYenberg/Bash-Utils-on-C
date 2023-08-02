CC = gcc -Wall -Werror -Wextra

all : my_cat test run_test

my_cat :
	$(CC) my_cat.c -o my_cat

test :
	$(CC)  test.c -o test

run_test :
	./test

run_test_mac : clean my_cat_mac test_mac run_test

my_cat_mac :
	$(CC) my_cat.c -D MAC -o my_cat

test_mac :
	$(CC)  test.c -D MAC -o test

rebuild : clean my_cat test

clean :
	rm -rf my_cat test