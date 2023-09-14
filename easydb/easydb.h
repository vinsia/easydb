#pragma once

#include <string>
#include <unordered_map>

namespace easydb {
class EasyDB {
 public:
  explicit EasyDB(std::string_view db_dir);
  ~EasyDB() = default;
  std::string_view Get(std::string_view key) const;
  const bool Put(std::string_view key, std::string_view value);

 private:
  std::string db_dir_;
  std::unordered_map<std::string, std::string> kv_store_;
};
}  // namespace easydb