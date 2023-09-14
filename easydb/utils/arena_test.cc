/*
 * Created Date: 2023-09-13 23:49:43
 * Author: vinsia
 * Copyright (c) 2023 vinsia.cn
 */

#include "easydb/utils/arena.h"

#include "gtest/gtest.h"

namespace easydb::utils {

struct Node {
  Node(int value) : value(value){};
  int value;
  Node* next[1];
};

TEST(ArenaTest, Simple) {
  Arena arena;
  EXPECT_EQ(0, arena.MemoryUsage());
  arena.Allocate(48);
  EXPECT_EQ(4096, arena.MemoryUsage());
  arena.Allocate(2048);
  EXPECT_EQ(4096, arena.MemoryUsage());
  arena.Allocate(2048);
  EXPECT_EQ(8192, arena.MemoryUsage());
}

TEST(ArenaTest, Complex) {
  Arena arena;
  EXPECT_EQ(0, arena.MemoryUsage());
  char* test_char_1 = nullptr;
  char* test_char_2 = nullptr;

  test_char_1 = arena.Allocate(4);
  for (int i = 0; i < 3; i++) {
    test_char_1[i] = '1';
  }
  test_char_1[3] = '\0';

  test_char_2 = arena.Allocate(8);
  for (int i = 0; i < 8; i++) {
    test_char_2[i] = '2';
  }
  test_char_2[7] = '\0';

  EXPECT_EQ("111", std::string(test_char_1));
  EXPECT_EQ("2222222", std::string(test_char_2));
  EXPECT_EQ(static_cast<void*>(test_char_1) + 4,
            static_cast<void*>(test_char_2));
}

TEST(ArenaTest, Align) {
  Arena arena;
  {
    char* first = arena.AllocateAligned(1);
    char* second = arena.AllocateAligned(2);
    EXPECT_EQ(static_cast<void*>(first) + 8, static_cast<void*>(second));
  }

  {
    char* first = arena.AllocateAligned(14);
    char* second = arena.AllocateAligned(2);
    EXPECT_EQ(static_cast<void*>(first) + 16, static_cast<void*>(second));
  }
}

TEST(ArenaTest, NodeAlign) {
  Arena arena;
  char* node_memory = arena.AllocateAligned(sizeof(Node) + sizeof(Node*) * 1);
  Node* node = new (node_memory) Node(1);
  node->next[1] = nullptr;
  node->next[2] = node;
  EXPECT_EQ(1, node->value);
  EXPECT_EQ(nullptr, node->next[1]);
  EXPECT_EQ(node, node->next[2]);
}

}  // namespace easydb::utils
