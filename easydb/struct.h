#pragma once

#include <cstdint>

namespace easydb {

typedef uint64_t SequenceNumber;

enum ValueType { kTypeDeletion = 0x0, kTypeValue = 0x1 };

}  // namespace easydb
