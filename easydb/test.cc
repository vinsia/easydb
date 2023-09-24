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

int main() {
  easydb::Arena arena;
  easydb::SkipList<int, int> skip_list = easydb::SkipList<int, int>(&arena);
  std::cout << skip_list.GetMaxHeight() << std::endl;
  skip_list.Insert(1, 2);

  std::cout << skip_list.Contains(1) << std::endl;
  std::cout << skip_list.Contains(2) << std::endl;
  return 0;
}
