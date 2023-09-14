#include "easydb/skiplist.h"

#include "easydb/utils/arena.h"
#include "gtest/gtest.h"

namespace easydb {

using Arena = easydb::utils::Arena;

TEST(SkipListTest, Init) {
  Arena arena;
  SkipList<int, int> skip_list = SkipList<int, int>(&arena);
  // EXPECT_EQ(1, skip_list.GetMaxHeight());
  // skip_list.Insert(1, 2);
  // EXPECT_TRUE(skip_list.Contains(1));
  // EXPECT_TRUE(!skip_list.Contains(2));
}

}  // namespace easydb