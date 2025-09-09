#include "tests.h"

// Constructors tests

// initialaizer list
TEST(array_constructors, Initialaizerist) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    EXPECT_EQ(array[0], 5);
    EXPECT_EQ(array[1], 4);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 2);
    EXPECT_EQ(array[4], 1);
    
}

TEST(array_constructors, CopyConstructor) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    s21::array<int, 5> arrayCopy(array);
    EXPECT_EQ(arrayCopy[0], 5);
    EXPECT_EQ(arrayCopy[1], 4);
    EXPECT_EQ(arrayCopy[2], 3);
    EXPECT_EQ(arrayCopy[3], 2);
    EXPECT_EQ(arrayCopy[4], 1);
}

TEST(array_constructors, MoveConstructor) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    s21::array<int, 5> arrayCopy(std::move(array));
    EXPECT_EQ(arrayCopy[0], 5);
    EXPECT_EQ(arrayCopy[1], 4);
    EXPECT_EQ(arrayCopy[2], 3);
    EXPECT_EQ(arrayCopy[3], 2);
    EXPECT_EQ(arrayCopy[4], 1);
}

// Elements access tests
TEST(array_constructors, at) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    EXPECT_EQ(array.at(0), 5);
    EXPECT_EQ(array.at(1), 4);
    EXPECT_EQ(array.at(2), 3);
    EXPECT_EQ(array.at(3), 2);
    EXPECT_EQ(array.at(4), 1);
    
}


TEST(array_constructors, front) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    EXPECT_EQ(array.front(), 5);
    
}

TEST(array_constructors, back) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    EXPECT_EQ(array.back(), 1);
    
}



// Iterator tests

TEST(array_iterator, data) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    s21::array<int, 5>::iterator iterator = array.data();
    EXPECT_EQ(*iterator, 5);
    EXPECT_EQ(*(iterator + 1), 4);
    EXPECT_EQ(*(iterator + 2), 3);
    EXPECT_EQ(*(iterator + 3), 2);
    EXPECT_EQ(*(iterator + 4), 1);
    
}

TEST(array_iterator, begin) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    s21::array<int, 5>::iterator iterator = array.begin();
    EXPECT_EQ(*iterator, 5);
    
}

TEST(array_iterator, end) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    s21::array<int, 5>::iterator iterator = array.end();
    EXPECT_EQ(*iterator, 1);
    
}

// Size tests

TEST(array_iterator, size) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    EXPECT_EQ(array.size(), 5);
    
}

TEST(array_iterator, empty) {
    s21::array<int, 0> array;
    EXPECT_EQ(array.empty(), true);
    
}

TEST(array_iterator, filled) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    EXPECT_EQ(array.empty(), false);
    
}

// Modifiers tests

TEST(array_iterator, swap) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    s21::array<int, 5> arrayCopy{10, 9, 8, 7, 6};
    array.swap(arrayCopy);
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 9);
    EXPECT_EQ(array[2], 8);
    EXPECT_EQ(array[3], 7);
    EXPECT_EQ(array[4], 6);

    EXPECT_EQ(arrayCopy[0], 5);
    EXPECT_EQ(arrayCopy[1], 4);
    EXPECT_EQ(arrayCopy[2], 3);
    EXPECT_EQ(arrayCopy[3], 2);
    EXPECT_EQ(arrayCopy[4], 1);
    
}

TEST(array_iterator, fill) {
    s21::array<int, 5> array{5, 4, 3, 2, 1};
    array.fill(12);
    EXPECT_EQ(array[0], 12);
    EXPECT_EQ(array[1], 12);
    EXPECT_EQ(array[2], 12);
    EXPECT_EQ(array[3], 12);
    EXPECT_EQ(array[4], 12);
    
}