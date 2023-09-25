#include "easydb/skiplist.h"

#include "easydb/utils/arena.h"
#include "gtest/gtest.h"

namespace easydb {

using Arena = easydb::utils::Arena;

TEST(SkipListTest, Node) {
  {
    auto node = SkipList<int, int>::Node(1, 2);
    EXPECT_EQ(1, node.key);
    EXPECT_EQ(2, node.value);
  }

  {
    typedef SkipList<int, int>::Node Node;
    Arena arena;
    size_t height = 14;
    int kNodeAllocationSize = sizeof(Node) + sizeof(Node*) * (height - 1);
    char* const node_memory = arena.AllocateAligned(kNodeAllocationSize);
    Node* node = new (node_memory) Node(1, 2);
    EXPECT_EQ(1, node->key);
    EXPECT_EQ(2, node->value);
  }
}

TEST(SkipListTest, StringNode) {
  {
    Arena arena;
    auto skip_list = SkipList<std::string, std::string>(&arena);
    skip_list.Insert("key", "value");
    EXPECT_EQ(true, skip_list.Contains("key"));
    EXPECT_EQ(false, skip_list.Contains("value"));
  }
}

TEST(SkipListTest, Init) {
  Arena arena;
  SkipList<int, int> skip_list = SkipList<int, int>(&arena);
  EXPECT_EQ(1, skip_list.GetMaxHeight());
  skip_list.Insert(1, 2);
  EXPECT_TRUE(skip_list.Contains(1));
  EXPECT_TRUE(!skip_list.Contains(2));
}

}  // namespace easydb
