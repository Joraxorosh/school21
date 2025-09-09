CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
COMMON_FILES = s21_matrix.c
TEST_FLAGS = -std=c11 -g
CHECK_FLAGS = -lcheck -lm -lsubunit -lpthread
GCOVFLAGS = --coverage

all: clean s21_matrix.a test gcov_report

clean:
	@rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug s21_matrix *.log **/*.html *app

s21_matrix.o:
	@$(CC) $(CC_FLAGS) -c $(COMMON_FILES)

s21_matrix.a: s21_matrix.o
	@ar rcs libs21_matrix.a *.o
	@ranlib libs21_matrix.a
	@cp libs21_matrix.a s21_matrix.a
	@echo "Static library built"

test: s21_matrix.a
	@$(CC) $(TEST_FLAGS) s21_test_matrix.c -L. -ls21_matrix $(CHECK_FLAGS) -o test_app
	@./test_app

gcov_report: CC_FLAGS += --coverage
gcov_report: clean s21_matrix.a
	@$(CC) $(CC_FLAGS) $(TEST_FLAGS) $(COMMON_FILES) s21_test_matrix.c -L. -ls21_matrix $(CHECK_FLAGS) -o gcov_app
	@./gcov_app
	@lcov -t "gcov_report" -o coverage.info -c -d .
	@genhtml coverage.info -o report
