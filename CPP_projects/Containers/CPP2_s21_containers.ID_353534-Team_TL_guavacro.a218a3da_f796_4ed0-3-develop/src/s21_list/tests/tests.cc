#include <gtest/gtest.h>
#include "../methods/s21_list.h"

using s21::list;

TEST(ListTest, DefaultConstructor) {
  list<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0u);
}

TEST(ListTest, InitializerListConstructor) {
  list<int> l{1, 2, 3};
  EXPECT_EQ(l.size(), 3u);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(ListTest, PushBackFrontPop) {
  list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_front(0);
  EXPECT_EQ(l.front(), 0);
  EXPECT_EQ(l.back(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 1);
  l.pop_back();
  EXPECT_EQ(l.back(), 1);
  l.pop_back();
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, FrontBackThrowIfEmpty) {
  list<int> l;
  EXPECT_THROW(l.front(), std::out_of_range);
  EXPECT_THROW(l.back(), std::out_of_range);
}

TEST(ListTest, CopyConstructor) {
  list<int> l1{1, 2, 3};
  list<int> l2(l1);
  EXPECT_EQ(l2.size(), 3u);
  EXPECT_EQ(l2.front(), 1);
  l2.pop_front();
  EXPECT_EQ(l2.front(), 2);
}

TEST(ListTest, MoveConstructor) {
  list<int> l1{4, 5};
  list<int> l2(std::move(l1));
  EXPECT_EQ(l2.size(), 2u);
  EXPECT_EQ(l2.front(), 4);
  EXPECT_TRUE(l1.empty());
}

TEST(ListTest, CopyAssignment) {
  list<int> l1{1, 2};
  list<int> l2;
  l2 = l1;
  EXPECT_EQ(l2.size(), 2u);
  EXPECT_EQ(l2.front(), 1);
}

TEST(ListTest, MoveAssignment) {
  list<int> l1{1, 2};
  list<int> l2;
  l2 = std::move(l1);
  EXPECT_EQ(l2.size(), 2u);
  EXPECT_TRUE(l1.empty());
}

TEST(ListTest, Clear) {
  list<int> l{1, 2};
  l.clear();
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0u);
  EXPECT_THROW(l.front(), std::out_of_range);
}

TEST(ListTest, Swap) {
  list<int> l1{1, 2}, l2{3};
  l1.swap(l2);
  EXPECT_EQ(l1.size(), 1u);
  EXPECT_EQ(l2.size(), 2u);
  EXPECT_EQ(l1.front(), 3);
  EXPECT_EQ(l2.front(), 1);
}

TEST(ListTest, Iterators) {
  list<int> l{10, 20, 30};
  auto it = l.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(it, l.end());
}

TEST(ListTest, Insert) {
  list<int> l{1, 3};
  auto it = ++l.begin();
  l.insert(it, 2);
  EXPECT_EQ(l.size(), 3u);
  it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, Erase) {
  list<int> l{1, 2, 3};
  auto it = ++l.begin();
  l.erase(it);
  EXPECT_EQ(l.size(), 2u);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(ListTest, EraseLastElement) {
  list<int> l{1};
  auto it = l.begin();
  l.erase(it);
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, InsertMany) {
  list<int> l{1, 4};
  auto it = ++l.begin();
  l.insert_many(it, 2, 3);
  EXPECT_EQ(l.size(), 4u);
  auto i = l.begin();
  EXPECT_EQ(*i++, 1);
  EXPECT_EQ(*i++, 2);
  EXPECT_EQ(*i++, 3);
  EXPECT_EQ(*i++, 4);
}

TEST(ListTest, InsertManyFrontBack) {
  list<int> l;
  l.insert_many_front(2, 1);
  l.insert_many_back(3, 4);
  EXPECT_EQ(l.size(), 4u);
  auto it = l.begin();
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}

TEST(ListTest, InsertManyEmpty) {
  list<int> l{1, 2};
  auto it = l.begin();
  l.insert_many(it);
  EXPECT_EQ(l.size(), 2u);
}

TEST(ListTest, SpliceMiddle) {
  list<int> l1{1, 4};
  list<int> l2{2, 3};
  auto it = ++l1.begin();
  list<int>::const_iterator pos(it.get_node());
  l1.splice(pos, l2);
  EXPECT_EQ(l1.size(), 4u);
  auto i = l1.begin();
  EXPECT_EQ(*i++, 1);
  EXPECT_EQ(*i++, 2);
  EXPECT_EQ(*i++, 3);
  EXPECT_EQ(*i++, 4);
  EXPECT_TRUE(l2.empty());
}

TEST(ListTest, SpliceEnd) {
  list<int> l1{1, 2};
  list<int> l2{3, 4};
  list<int>::const_iterator pos(l1.end().get_node());
  l1.splice(pos, l2);
  EXPECT_EQ(l1.size(), 4u);
  auto it = l1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_TRUE(l2.empty());
}

TEST(ListTest, Reverse) {
  list<int> l{1, 2, 3};
  l.reverse();
  auto it = l.begin();
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 1);
}

TEST(ListTest, Unique) {
  list<int> l{1, 1, 2, 2, 2, 3, 3, 4};
  l.unique();
  EXPECT_EQ(l.size(), 4u);
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}

TEST(ListTest, UniqueAllSame) {
  list<int> l{1, 1, 1, 1};
  l.unique();
  EXPECT_EQ(l.size(), 1u);
  EXPECT_EQ(l.front(), 1);
}

TEST(ListTest, SortAlreadySorted) {
  list<int> l{1, 2, 3, 4};
  l.sort();
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}

TEST(ListTest, SortUnsorted) {
  list<int> l{3, 1, 4, 2};
  l.sort();
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
}

TEST(ListTest, SortWithDuplicates) {
  list<int> l{3, 1, 2, 3, 1};
  l.sort();
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 3);
}
