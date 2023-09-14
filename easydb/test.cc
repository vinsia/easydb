/*
 * Filename: /home/yijian.li/work/d2l/easydb/easydb/test.cc
 * Path: /home/yijian.li/work/d2l/easydb/easydb
 * Created Date: Thursday, September 7th 2023, 8:56:09 am
 * Author: vinsia
 *
 * Copyright (c) 2023 vinsia.cn
 */

template <int N>
class Node {
 public:
  explicit Node(const Key& key, const Value& value)
      : key_(key), value_(value) {}
  ~Node() = default;

  Next(int level) { return next_[level]; }
  SetNext(int level, Node* node) { next_[level] = node; }

  const Key key_;
  const Value value_;

 private:
  Node* next_;
};

int main() {
  auto node1 = Node<3>("1", "2");
  auto node2 = Node<4>("1", "2");
  Node* node[] = {&node1, &node2};
  return 0;
}