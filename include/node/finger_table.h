#pragma once
#include "../common/constants.h"
#include "node.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>

namespace load_balancer::finger_table {
using load_balancer::node::Node;
class FingerEntries {
  Node *successor = nullptr;

public:
  FingerEntries() = default;
  const Node *get_successor() const { return successor; }
  void set_successor(Node *node) { successor = node; }
};

class FingerTable {
private:
  std::vector<FingerEntries> entries;

public:
  explicit FingerTable() {
    entries.resize(log2(load_balancer::constants::BUCKETS));
  }
  void update_successor_for_nth_finger(int n, Node *node) {
    assert(n < entries.size());
    entries[n].set_successor(node);
  }

  const Node *get_successor_for_node_with_value_n(int n) const {
    // Each entry is binary multiplied, as in ith entry shows the successor for
    // (2^i)%BUCKETS
    return entries[log2(n)].get_successor();
  }
};

} // namespace load_balancer::finger_table
