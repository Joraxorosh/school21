SHELL:=/bin/bash
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: s21_string.a test gcov_report

s21_string.a: s21_string.o s21_strerror.o s21_sprintf.o
	ar rcs s21_string.a s21_string.o s21_strerror.o s21_sprintf.o
	cp s21_string.a libs21_string.a
	cp s21_string.a ls21_string.a
	ranlib libs21_string.a
	ranlib ls21_string.a

s21_string.o: 
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

s21_strerror.o:
	$(CC) $(CFLAGS) -c s21_strerror.c -o s21_strerror.o

s21_sprintf.o:
	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o

test: s21_string.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_string_test.c s21_sprintf_test.c tests.c s21_string.a -o test.out $(LIBS)
	./test.out
else
	$(CC) $(CFLAGS) s21_string_test.c s21_sprintf_test.c tests.c s21_string.a -o test.out $(LIBS) $(LINUX)
	./test.out
endif

gcov_report: gcov_test.info test
	./test.out
	lcov -t "Tests coverage" -o test.info -c -d .
	genhtml -o report/ gcov_test.info
	open report/index.html 
	rm *.gcno
	rm *.gcda

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "Report" -o gcov_test.info --no-external -c -d .

gcov_test: s21_string.a

ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_string_test.c s21_sprintf_test.c tests.c s21_string.c s21_strerror.c s21_sprintf.c -o gcov_test $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_string_test.c s21_sprintf_test.c tests.c s21_string.c s21_strerror.c s21_sprintf.c -o gcov_test $(LIBS) $(LINUX)
endif

gcov_test.gcda: gcov_test
	chmod +x *
	./gcov_test

open: gcov_report
	open report/index.html

rebuild: clean all

# check:
# 	cppcheck *.c
# 	make test
# ifeq ($(OS), Darwin)
# 	CK_FORK=no leaks --atExit -- ./test.out
# else
# 	valgrind ./test.out --leak-check=full
# endif
# 	make clean

clean:
	rm -rf *.o *.a *.info test.out gcov_test
	rm -rf report
	rm *.gcno
	rm *.gcda
	