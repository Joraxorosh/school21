#include "tests.h"

// Constructors tests

TEST(map, InitialaizerList) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    EXPECT_EQ(map[1], 15);
    EXPECT_EQ(map[4], 20);
    EXPECT_EQ(map[0], 12);  
}

TEST(map, copyConxtructor) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    s21::map<int, int> mapCopy(map);
    EXPECT_EQ(mapCopy[1], 15);
    EXPECT_EQ(mapCopy[4], 20);
    EXPECT_EQ(mapCopy[0], 12);
}

TEST(map_constructors, moveConxtructor) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    s21::map<int, int> mapCopy(std::move(map));
    EXPECT_EQ(mapCopy[1], 15);
    EXPECT_EQ(mapCopy[4], 20);
    EXPECT_EQ(mapCopy[0], 12);
    EXPECT_TRUE(map.empty());
}

// access tests

TEST(map, brackets) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    EXPECT_EQ(map[1], 15);
    EXPECT_EQ(map[4], 20);
    EXPECT_EQ(map[0], 12);  
}

TEST(map, at) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    EXPECT_EQ(map.at(1), 15);
    EXPECT_EQ(map.at(4), 20);
    EXPECT_EQ(map.at(0), 12);  
}

// iterators tests

TEST(map, begin) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    s21::map<int, int>::iterator it = map.begin();
    EXPECT_EQ(it->second, 12);
    EXPECT_EQ((++it)->second, 15);
    EXPECT_EQ((++it)->second, 20); 
}

TEST(map, end) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    s21::map<int, int>::iterator it = map.end();
    EXPECT_EQ(it->second, 20);
    EXPECT_EQ((--it)->second, 15);
    EXPECT_EQ((--it)->second, 12); 
}

// size tests

TEST(map, emty) {
    s21::map<int, int> map{};
    EXPECT_TRUE(map.empty());
}

TEST(map, filled) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    EXPECT_TRUE(!map.empty());
}

TEST(map, size) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    EXPECT_EQ(map.size(), 3);
}

// modifiers tests

TEST(map, clear) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    map.clear();
    EXPECT_EQ(map.size(), 0);
}

TEST(map, insert) {
    s21::map<int, int> map{{1, 15}, {4, 20}, {0, 12}};
    s21::map<int, int>::iterator it = (map.insert(5, 56).first);
    EXPECT_EQ(it->second, 56);
}

TEST(map, erase) {
    s21::map<int, int> map{{1, 15}};
    s21::map<int, int>::iterator it = map.begin();
    map.erase(it);
    EXPECT_EQ((map.size()), 0);
}
	

TEST(map, swap) {
    s21::map<int, int> map{{1, 15}, {4, 20}};
    s21::map<int, int> map1{{2, 16}, {5, 21}};
    map.swap(map1);
    EXPECT_EQ(map[2], 16);
    EXPECT_EQ(map[5], 21);

    EXPECT_EQ(map1[1], 15);
    EXPECT_EQ(map1[4], 20);
}

TEST(map, merge) {
    s21::map<int, int> map{{1, 15}, {4, 20}};
    s21::map<int, int> map1{{2, 16}, {5, 0}};
    map.merge(map1);
    EXPECT_EQ(map[2], 16);
    EXPECT_EQ(map[5], 0);
    EXPECT_EQ(map[1], 15);
    EXPECT_EQ(map[4], 20);
}


TEST(map, contains) {
    s21::map<int, int> map{{1, 15}};
    EXPECT_EQ((map.contains(1)), true);
    EXPECT_EQ((map.contains(13)), false);
}