#include "tests.h"

// constructors tests

TEST(set, InitialaizerList) {
    s21::set<int> set{5, 4, 3, 2, 1};
    EXPECT_EQ(*(set.end()), 5);
    EXPECT_EQ(*(--set.end()), 4);
    EXPECT_EQ(*(----set.end()), 3);
    EXPECT_EQ(*(------set.end()), 2);
    EXPECT_EQ(*(--------set.end()), 1);
}

TEST(set, copyConstructor) {
    s21::set<int> setCopy{5, 4, 3, 2, 1};
    s21::set<int> set = setCopy;
    EXPECT_EQ(*(set.end()), 5);
    EXPECT_EQ(*(--set.end()), 4);
    EXPECT_EQ(*(----set.end()), 3);
    EXPECT_EQ(*(------set.end()), 2);
    EXPECT_EQ(*(--------set.end()), 1);
       
}

TEST(set, moveConstructor) {
    s21::set<int> setCopy{5, 4, 3, 2, 1};
    s21::set<int> set = std::move(setCopy);
    EXPECT_EQ(*(set.end()), 5);
    EXPECT_EQ(*(--set.end()), 4);
    EXPECT_EQ(*(----set.end()), 3);
    EXPECT_EQ(*(------set.end()), 2);
    EXPECT_EQ(*(--------set.end()), 1);
    EXPECT_TRUE(setCopy.empty());
}

// iterator tests

TEST(set, iteratorBegin) {
    s21::set<int> set{5, 4, 3, 2, 1};
    EXPECT_EQ(*(set.begin()), 1);
    EXPECT_EQ(*(++set.begin()), 2);
    EXPECT_EQ(*(++++set.begin()), 3);
    EXPECT_EQ(*(++++++set.begin()), 4);
    EXPECT_EQ(*(++++++++set.begin()), 5);
}

// capacity tests
TEST(set, empty) {
    s21::set<int> set{5, 4, 3, 2, 1};
    EXPECT_EQ(set.empty(), false);
}

TEST(set, filled) {
    s21::set<int> set;
    EXPECT_EQ(set.empty(), true);
}

TEST(set, size) {
    s21::set<int> set{5, 4, 3, 2, 1};
    EXPECT_EQ(set.size(), 5);
}

// modifiers

TEST(set, clear) {
    s21::set<int> set{5, 4, 3, 2, 1};
    set.clear();
    EXPECT_EQ(set.empty(), true);
       
}

TEST(set, insert) {
    s21::set<int> set{12, 4, 3, 2, 1};
    std::pair pair{set.insert(6)};
    EXPECT_EQ(*(pair.first), 6);
    EXPECT_EQ(pair.second, true);
       
}

TEST(set, erase) {
    s21::set<int> set{12, 4, 3, 2, 1};
    set.erase(set.end());
    EXPECT_EQ(*(set.end()), 4);
}



TEST(set, swap) {
    s21::set<int> set{12, 4, 3, 2, 1};
    s21::set<int> setNew{13, 14, 15, 16, 20};
    set.swap(setNew);
    EXPECT_EQ(*(set.end()), 20);
    EXPECT_EQ(*(--set.end()), 16);
    EXPECT_EQ(*(----set.end()), 15);
    EXPECT_EQ(*(------set.end()), 14);
    EXPECT_EQ(*(--------set.end()), 13);
}

TEST(set, merge) {
    s21::set<int> set{4, 17, 18};
    s21::set<int> setNew{16, 20};
    set.merge(setNew);
    EXPECT_EQ(*(set.end()), 20);
    EXPECT_EQ(*(--set.end()), 18);
    EXPECT_EQ(*(----set.end()), 17);
    EXPECT_EQ(*(------set.end()), 16);
    EXPECT_EQ(*(--------set.end()), 4);
}

// lookup tests

TEST(set, find) {
    s21::set<int> set{12, 4, 3, 2, 1};
    s21::set<int>::iterator three = set.find(3);
    EXPECT_EQ(*(three), 3);
}

TEST(set, contains) {
    s21::set<int> set{12, 4, 3, 2, 1};
    EXPECT_EQ(set.contains(3), true);
    EXPECT_EQ(set.contains(10), false);
}   
