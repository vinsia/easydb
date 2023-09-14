/*
 * Created Date: Wednesday, September 13th 2023, 10:51:49 pm
 * Author: vinsia
 *
 * Copyright (c) 2023 vinsia.cn
 */
#pragma once

#include <atomic>
#include <vector>

namespace easydb::utils {

class Arena {
 public:
  Arena();
  ~Arena();

  // Forbidden the copy-constructor and copy-assignment
  // Since the Arena should be a singleton in the Program
  Arena(const Arena&) = delete;
  Arena& operator=(const Arena&) = delete;

  // Allocate Memory
  char* Allocate(size_t size);
  char* AllocateAligned(size_t size);
  size_t MemoryUsage() const;

 private:
  char* AllocateImmediate(size_t size);
  // char* AllocateAligned(size_t size){};
  char* AllocateWithNewBlock(size_t size);
  // Apply the memory from the system
  char* AllocateNewBlock(size_t block_size);

  char* alloc_ptr_;  // Point to the beginning of unallocated memory
  size_t remaining_memory_in_bytes_;
  std::vector<char*> blocks_;  // Point to allocated blocks
  std::atomic<size_t> memory_usage_;
};
}  // namespace easydb::utils
