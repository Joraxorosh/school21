CC=gcc
CC_FLAGS=-c -Wall -Werror -Wextra -std=c11
BUILD_NAME=s21_grep

all: build

build: s21_grep

rebuild: clean build

s21_grep: s21_grep.o
	${CC} s21_grep.o -o ${BUILD_NAME}

s21_grep.o: s21_grep.c
	${CC} s21_grep.c ${CC_FLAGS} -o s21_grep.o

clean:
	rm -rf ./*.o
	rm -rf ./${BUILD_NAME}

test: test_grep.sh
	./test_grep.sh