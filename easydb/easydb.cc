#include "easydb/easydb.h"

namespace easydb {
EasyDB::EasyDB(std::string_view db_dir)
    : db_dir_(db_dir), skiplist_(SkipList<std::string, std::string>(&arena_)) {}

std::string_view EasyDB::Get(std::string key) const {
  auto* node = skiplist_.FindGreaterOrEqual(key, nullptr);
  if (node->key != key) {
    return "";
  }
  return node->value;
}

const bool EasyDB::Put(std::string key, std::string value) {
  skiplist_.Insert(key, value);
  return true;
}

}  // namespace easydb
