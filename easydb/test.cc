/*
 * Filename: /home/yijian.li/work/d2l/easydb/easydb/test.cc
 * Path: /home/yijian.li/work/d2l/easydb/easydb
 * Created Date: Thursday, September 7th 2023, 8:56:09 am
 * Author: vinsia
 *
 * Copyright (c) 2023 vinsia.cn
 */
#include <glog/logging.h>
#include <iostream>

#include "easydb/skiplist.h"
#include "easydb/utils/arena.h"

using easydb::utils::Arena;

struct Node {
  int value_[1];
};

class TestNode {
 public:
  explicit TestNode(Arena* arena, int size)
      : arena_(arena), node_(NewNode(size)){};

  Node* NewNode(int size) {
    std::cout << "2" << std::endl;
    int kNodeAllocationSize = sizeof(Node) + sizeof(int) * (size - 1);
    char* const node_memory = arena_->AllocateAligned(kNodeAllocationSize);
    Node* node = new (node_memory) Node();
    return node;
  }

 private:
  Node* const node_;
  Arena* const arena_;
};

int main() {
  easydb::Arena arena;
  TestNode test_node(&arena, 10);
  std::cout << "1" << std::endl;
  return 0;
  // easydb::SkipList<int, int> skip_list = easydb::SkipList<int, int>(&arena);
  // std::cout << skip_list.GetMaxHeight() << std::endl;
  // skip_list.Insert(1, 2);

  // std::cout << skip_list.Contains(1) << std::endl;
  // std::cout << skip_list.Contains(2) << std::endl;
  // return 0;
}
