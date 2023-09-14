#pragma once

#include <iostream>
#include <malloc.h>

#include "assert.h"
#include "easydb/utils/arena.h"
#include "easydb/utils/random.h"

namespace easydb {
namespace {
using Random = easydb::utils::Random;
using Arena = easydb::utils::Arena;
}  // namespace
template <typename Key, typename Value>
class SkipList {
 public:
  SkipList(Arena* arena)
      // TODO: Fix the the Key or Value can not assign to the nullptr
      : arena_(arena),
        head_(NewNode(0, 0, kMaxHeight)),
        max_height_(1),
        rnd_(0xdeadbeef) {
    for (int i = 0; i < kMaxHeight; i++) {
      head_->SetNext(i, nullptr);
    }
  }
  ~SkipList() {}

  struct Node {
   public:
    explicit Node(const Key& key, const Value& value)
        : key_(key), value_(value) {}
    ~Node() { free(next_); }

    // There is different memory synchronization from LevelDB.
    Node* Next(int level) { return next_[level]; }
    void SetNext(int level, Node* node) { next_[level] = node; }

    const Key key_;
    const Value value_;

   private:
    // Memory allocation is different from the levelDB
    // Investigate the better way to allocate memory.
    Node* next_[1];
  };

  Node* NewNode(const Key& key, const Value& value, int height) {
    std::cerr << sizeof(Node) << " " << sizeof(Node*) << std::endl;
    int kNodeAllocationSize = sizeof(Node) + sizeof(Node*) * (height - 1);
    std::cerr << "1" << std::endl;
    std::cerr << kNodeAllocationSize << std::endl;
    char* const node_memory = arena_->AllocateAligned(kNodeAllocationSize);
    std::cerr << "2" << std::endl;
    // std::cerr << node_memory << std::endl;
    std::cerr << static_cast<void*>(node_memory) << std::endl;
    // Node* node = new (node_memory) Node(key, value);
    Node* node = new Node(0, 0);
    std::cerr << "3" << std::endl;
    std::cerr << static_cast<void*>(node) << std::endl;
    std::cerr << &kNodeAllocationSize << std::endl;
    return node;
  }

  int GetMaxHeight() const { return max_height_; }

  int RandomHeight() {
    static const unsigned int kBranching = 4;
    int height = 1;
    while (height < kMaxHeight && rnd_.OneIn(kBranching)) {
      height++;
    }
    assert(height > 0);
    assert(height <= kMaxHeight);
    return height;
  }

  void Insert(const Key& key, const Value& value) {
    Node* prev[kMaxHeight];
    Node* node = FindGreaterOrEqual(key, prev);

    assert(node == nullptr || key != node->key_);

    int height = RandomHeight();
    if (height > GetMaxHeight()) {
      for (int i = GetMaxHeight(); i < height; i++) {
        prev[i] = head_;
      }
      max_height_ = height;
    }

    Node* new_node = NewNode(key, value, height);
    for (int i = 0; i < height; i++) {
      new_node->SetNext(i, prev[i]->Next(i));
      prev[i]->SetNext(i, new_node);
    }
  }

  bool Contains(const Key& key) const {
    Node* node = FindGreaterOrEqual(key, nullptr);
    if (node != nullptr && node->key_ == key) {
      return true;
    }
    return false;
  }

  bool KeyIsAfterNode(const Key& key, Node* node) const {
    return (node != nullptr) && (key < node->key_);
  }

  Node* FindGreaterOrEqual(const Key& key, Node** prev) const {
    Node* node = head_;
    int level = GetMaxHeight() - 1;
    while (true) {
      Node* next = node->Next(level);
      if (KeyIsAfterNode(key, next)) {
        node = next;
      } else {
        if (prev != nullptr) prev[level] = node;
        if (level == 0) {
          return next;
        } else {
          level--;
        }
      }
    }
    return node;
  }

 private:
  // enum { kMaxHeight = 14 };
  static constexpr int kMaxHeight = 14;
  Node* const head_;
  int max_height_;
  Random rnd_;
  Arena* const arena_;
};
}  // namespace easydb