#include "easydb/memtable.h"

#include "easydb/slice.h"
#include "easydb/struct.h"

namespace easydb {

Memtable::Memtable() {}

void Memtable::Add(SequenceNumber sequence_number, ValueType value_type,
                   const Slice& key, const Slice& value) {
  size_t key_size = key.size();
  size_t value_size = value.size();
  size_t internal_key_size = key_size + 8;
  const size_t encoded_len =
      kKeySizeInBytes + internal_key_size + kKeySizeInBytes + value_size;
  arena_->Allocate(encoded_len);
}

void Memtable::Get(const LookupKey& look_up_key, std::string* value,
                   Status* status) {}

}  // namespace easydb
