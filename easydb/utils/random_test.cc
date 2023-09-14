/*
 * Filename: /home/yijian.li/work/d2l/easydb/easydb/utils/random_test.cc
 * Path: /home/yijian.li/work/d2l/easydb/easydb/utils
 * Created Date: Thursday, September 7th 2023, 8:13:27 pm
 * Author: vinsia
 *
 * Copyright (c) 2023 vinsia.cn
 */

#include "easydb/utils/random.h"

#include "gtest/gtest.h"

namespace easydb::utils {
TEST(RandomTest, RandomTest) {
  Random random = Random(0xdeadbeef);
  EXPECT_TRUE(random.Next() >= 1);
  EXPECT_TRUE(random.Next() <= 2147483647L);
}
}  // namespace easydb::utils
