#pragma once

#include <string>

#include "easydb/slice.h"
#include "easydb/status.h"
#include "easydb/struct.h"
#include "easydb/utils/arena.h"

namespace easydb {

constexpr size_t kKeySizeInBytes = 8;

class MemTableKey;
class LookupKey;
class KeyComparator;

class MemtableKey {
 public:
  explicit MemtableKey(const Slice& key, const Slice& value)
      : key_(key), value_(value){};

  ~MemtableKey() = default;

 private:
  const Slice& key_;
  const Slice& value_;
};

class Memtable {
 public:
  explicit Memtable();
  ~Memtable() = default;

  void Add(SequenceNumber sequence_number, ValueType value_type,
           const Slice& key, const Slice& value);

  void Get(const LookupKey& look_up_key, std::string* value, Status* status);

 private:
  using Arena = easydb::utils::Arena;

  Arena* arena_;
};

}  // namespace easydb
