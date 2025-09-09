CC = g++
SRC = s21_matrix_oop.cpp
OBJ = s21_matrix_oop.o
LIB = s21_matrix_oop.a
FLAGS = -Wall -Werror -Wextra -std=c++20 -fPIC -fprofile-arcs -ftest-coverage
TESTFLAGS = -pthread -lgtest -lgmock -lpthread

all: clean test

s21_matrix_oop.a:
	$(CC) -c $(FLAGS) $(SRC) -o $(OBJ)
	ar -rcs $(LIB) $(OBJ)
	ranlib $(LIB)
	rm -rf *.o

test: clean s21_matrix_oop.a
	$(CC) $(FLAGS) s21_matrix_test.cpp $(LIB) $(TESTFLAGS) -o test
	./test

html_coverage: test
	gcov -b -l -p $(SRC)
	gcovr -r . --html --html-details -o coverage_report.html
	@xdg-open coverage_report.html || open coverage_report.html || start coverage_report.html

clean: 
	rm -rf *.out *.o *.gcno *.gcda *.a test coverage_report* *.html *.gcov

valgrind: test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./test