#include <gtest/gtest.h>
#include "../methods/s21_queue.h"

using s21::queue;

TEST(QueueTest, DefaultConstructor) {
  queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, InitializerListConstructor) {
  queue<int> q{1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, PushPop) {
  queue<int> q;
  q.push(10);
  q.push(20);
  q.push(30);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 30);
  q.pop();
  EXPECT_EQ(q.front(), 20);
  q.pop();
  EXPECT_EQ(q.front(), 30);
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, FrontBackThrows) {
  queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, CopyConstructor) {
  queue<int> q1{1, 2, 3};
  queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_EQ(q2.front(), 1);
  q2.pop();
  EXPECT_EQ(q2.front(), 2);
}

TEST(QueueTest, MoveConstructor) {
  queue<int> q1{10, 20};
  queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 10);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, CopyAssignment) {
  queue<int> q1{1, 2};
  queue<int> q2;
  q2 = q1;
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 1);
  q2.pop();
  EXPECT_EQ(q2.front(), 2);
}

TEST(QueueTest, MoveAssignment) {
  queue<int> q1{5, 6};
  queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2.front(), 5);
}

TEST(QueueTest, Clear) {
  queue<int> q{1, 2, 3};
  q.clear();
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, Swap) {
  queue<int> q1{1, 2}, q2{3};
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 1u);
  EXPECT_EQ(q1.front(), 3);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, InsertManyBack) {
  queue<int> q;
  q.insert_many_back(7, 8, 9);
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), 7);
  q.pop();
  EXPECT_EQ(q.front(), 8);
  q.pop();
  EXPECT_EQ(q.front(), 9);
}
