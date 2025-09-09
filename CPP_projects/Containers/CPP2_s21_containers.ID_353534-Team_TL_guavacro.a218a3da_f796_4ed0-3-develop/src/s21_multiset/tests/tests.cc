#include "tests.h"

// constructors tests

TEST(S21_multiset, InitialaizerList) {
    s21::multiset<int> set{5, 4, 4, 2, 1};
    EXPECT_EQ(*(set.end()), 5);
    EXPECT_EQ(*(--set.end()), 4);
    EXPECT_EQ(*(----set.end()), 4);
    EXPECT_EQ(*(------set.end()), 2);
    EXPECT_EQ(*(--------set.end()), 1);
       
}

TEST(S21_multiset, copyConstructor) {
    s21::multiset<int> setCopy{5, 4, 3, 2, 2};
    s21::multiset<int> set = setCopy;
    EXPECT_EQ(*(set.end()), 5);
    EXPECT_EQ(*(--set.end()), 4);
    EXPECT_EQ(*(----set.end()), 3);
    EXPECT_EQ(*(------set.end()), 2);
    EXPECT_EQ(*(--------set.end()), 2);
       
}

TEST(S21_multiset, moveConstructor) {
    s21::multiset<int> setCopy{5, 4, 3, 2, 2};
    s21::multiset<int> set = std::move(setCopy);
    EXPECT_EQ(*(set.end()), 5);
    EXPECT_EQ(*(--set.end()), 4);
    EXPECT_EQ(*(----set.end()), 3);
    EXPECT_EQ(*(------set.end()), 2);
    EXPECT_EQ(*(--------set.end()), 2);
}

// iterator tests

TEST(S21_multiset, iteratorBegin) {
    s21::multiset<int> set{5, 4, 2, 2, 1};
    EXPECT_EQ(*(set.begin()), 1);
    EXPECT_EQ(*(++set.begin()), 2);
    EXPECT_EQ(*(++++set.begin()), 2);
    EXPECT_EQ(*(++++++set.begin()), 4);
    EXPECT_EQ(*(++++++++set.begin()), 5);
       
}

// capacity tests
TEST(S21_multiset, empty) {
    s21::multiset<int> set{5, 4, 3, 2, 1};
    EXPECT_EQ(set.empty(), false);
}

TEST(S21_multiset, filled) {
    s21::multiset<int> set;
    EXPECT_EQ(set.empty(), true);
}

TEST(S21_multiset, size) {
    s21::multiset<int> set{5, 4, 3, 2, 1};
    EXPECT_EQ(set.size(), 5);
}

// modifiers

TEST(S21_multiset, clear) {
    s21::multiset<int> set{5, 4, 3, 2, 1};
    set.clear();
    EXPECT_EQ(set.empty(), true);
       
}

TEST(S21_multiset, insert) {
    s21::multiset<int> set{12, 4, 3, 2, 1};
    std::pair pair{set.insert(4)};
    EXPECT_EQ(*(pair.first), 4);
       
}

TEST(S21_multiset, erase) {
    s21::multiset<int> set{12, 4, 3, 2, 1};
    set.erase(set.end());
    EXPECT_EQ(*(set.end()), 4);
}



TEST(S21_multiset, swap) {
    s21::multiset<int> set{12, 4, 3, 2, 1};
    s21::multiset<int> setNew{13, 14, 15, 16, 20};
    set.swap(setNew);
    EXPECT_EQ(*(set.end()), 20);
    EXPECT_EQ(*(--set.end()), 16);
    EXPECT_EQ(*(----set.end()), 15);
    EXPECT_EQ(*(------set.end()), 14);
    EXPECT_EQ(*(--------set.end()), 13);
}

TEST(S21_multiset, merge) {
    s21::multiset<int> set{16, 18};
    s21::multiset<int> setNew{16, 20};
    set.merge(setNew);
    EXPECT_EQ(*(set.end()), 20);
    EXPECT_EQ(*(--set.end()), 18);
    EXPECT_EQ(*(----set.end()), 16);
    EXPECT_EQ(*(------set.end()), 16);
}

// lookup tests

TEST(S21_multiset, find) {
    s21::multiset<int> set{12, 4, 3, 2, 1};
    s21::multiset<int>::iterator three = set.find(3);
    EXPECT_EQ(*(three), 3);
}

TEST(S21_multiset, contains) {
    s21::multiset<int> set{12, 4, 3, 2, 1};
    EXPECT_EQ(set.contains(3), true);
    EXPECT_EQ(set.contains(10), false);
}   