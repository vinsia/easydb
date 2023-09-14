#include "easydb/easydb.h"

namespace easydb {
EasyDB::EasyDB(std::string_view db_dir) : db_dir_(db_dir) {}

std::string_view EasyDB::Get(std::string_view key) const {
  return kv_store_.at(std::string(key));
}

const bool EasyDB::Put(std::string_view key, std::string_view value) {
  auto status = kv_store_.emplace(std::string(key), std::string(value));
  return status.second;
}

}  // namespace easydb