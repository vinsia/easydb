/*
 * Created Date: 2023-09-13 23:06:41
 * Author: vinsia
 * Copyright (c) 2023 vinsia.cn
 */

#include "easydb/utils/arena.h"

#include <glog/logging.h>

namespace easydb::utils {

namespace {
constexpr size_t kDefaultBlockSize = 4096;
}

Arena::Arena()
    : alloc_ptr_(nullptr), remaining_memory_in_bytes_(0), memory_usage_(0) {}

Arena::~Arena() {
  for (size_t i = 0; i < blocks_.size(); i++) {
    delete[] blocks_[i];
  }
}

char* Arena::Allocate(size_t size) {
  CHECK(size > 0) << "Memory allocate should always grater than 0.";
  CHECK(size < kDefaultBlockSize)
      << "It is not allowed to allocate memory greater than " << size;

  if (size <= remaining_memory_in_bytes_) {
    return AllocateImmediate(size);
  }
  return AllocateWithNewBlock(size);
}

char* Arena::AllocateAligned(size_t size) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
  static_assert((align & (align - 1)) == 0,
                "Pointer size should be a power of 2");
  size_t current_mod = reinterpret_cast<uintptr_t>(alloc_ptr_) & (align - 1);
  size_t slop = (current_mod == 0 ? 0 : align - current_mod);
  size_t needed = size + slop;
  char* result;
  if (needed <= remaining_memory_in_bytes_) {
    result = alloc_ptr_ + slop;
    alloc_ptr_ += needed;
    remaining_memory_in_bytes_ -= needed;
  } else {
    result = AllocateWithNewBlock(size);
  }
  CHECK((reinterpret_cast<uintptr_t>(result) & (align - 1)) == 0)
      << "The memory allocated is not aligned.";
  return result;
}

size_t Arena::MemoryUsage() const {
  return memory_usage_.load(std::memory_order_relaxed);
}

char* Arena::AllocateImmediate(size_t size) {
  // Allocate the memory
  remaining_memory_in_bytes_ -= size;
  // Set the memory position
  char* result = alloc_ptr_;

  alloc_ptr_ += size;
  return result;
}

char* Arena::AllocateWithNewBlock(size_t size) {
  alloc_ptr_ = AllocateNewBlock(kDefaultBlockSize);
  remaining_memory_in_bytes_ = kDefaultBlockSize;

  return AllocateImmediate(size);
}

// char* Arena::AllocateAligned(size_t size) {}

char* Arena::AllocateNewBlock(size_t block_size) {
  char* result = new char[block_size];
  blocks_.push_back(result);

  memory_usage_.fetch_add(block_size, std::memory_order_relaxed);
  return result;
}

}  // namespace easydb::utils
