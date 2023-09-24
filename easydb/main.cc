#include <glog/logging.h>
#include <iostream>

#include "easydb/easydb.h"
#include "easydb/skiplist.h"
#include "easydb/utils/arena.h"
#include "gtest/gtest.h"

void InitGoogleLogging(char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;
}

int main(int argc, char* argv[]) {
  // Initialize Google’s logging library.
  InitGoogleLogging(argv);

  Arena arena;
  SkipList<int, int> skip_list = SkipList<int, int>(&arena);
  std::cerr << "4" << std::endl;
}
