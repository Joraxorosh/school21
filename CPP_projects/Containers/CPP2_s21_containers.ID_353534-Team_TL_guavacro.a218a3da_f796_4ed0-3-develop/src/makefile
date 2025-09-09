
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 

LIBS =  -L/usr/lib -lgtest -lgtest_main -pthread 

TARGET = test
SRC =  s21_set/tests/tests.cc s21_array/tests/tests.cc s21_map/tests/tests.cc s21_multiset/tests/tests.cc s21_set/tests/tests.cc s21_stack/main_test.cc s21_vector/test_vector.cc s21_queue/tests/tests.cc s21_list/tests/tests.cc
OBJ = $(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tests: clean $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

styleCheck:
	@cp ../materials/linters/.clang-format .
	@find . -type f -name "*.c" -exec clang-format -i {} \;
	@find . -type f -name "*.h" -exec clang-format -i {} \;
	@find . -type f -name "*.inl" -exec clang-format -i {} \;
	@rm ./.clang-format

leakCheck: tests
	valgrind --tool=memcheck --leak-check=yes ./test
