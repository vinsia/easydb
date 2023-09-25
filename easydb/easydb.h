#pragma once

#include <string>
#include <unordered_map>

#include "easydb/skiplist.h"
#include "easydb/utils/arena.h"

namespace easydb {
class EasyDB {
 public:
  explicit EasyDB(std::string_view db_dir);
  ~EasyDB() = default;

  std::string_view Get(std::string key) const;
  const bool Put(std::string key, std::string value);

 private:
  const std::string db_dir_;
  utils::Arena arena_ = utils::Arena();
  SkipList<std::string, std::string> skiplist_;
};
}  // namespace easydb
