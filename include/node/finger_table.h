#pragma once
#include "../common/constants.h"
#include "node.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>

namespace load_balancer::node {
class Node;
};

namespace load_balancer::finger_table {
using load_balancer::node::Node;
class FingerEntries {
  Node *successor = nullptr;

public:
  FingerEntries() = default;
  int value = 0;
  Node *get_successor() const { return successor; }
  void set_successor(Node *node) { successor = node; }
};

class FingerTable {
private:
  std::vector<FingerEntries> entries;
  int start_value = 0;

public:
  explicit FingerTable(int start_value_) {
    entries.resize(log2(load_balancer::constants::BUCKETS));
    start_value = start_value_;
    for (int i = 0; i < entries.size(); i++) {
      entries[i].value = start_value + pow(2, i);
    }
  }
  void update_successor_for_nth_finger(int n, Node *node) {
    assert(n < entries.size());
    entries[n].set_successor(node);
  }

  const FingerEntries *get_nth_finger(int n) {
    assert(n < entries.size());
    return &entries[n];
  }

  Node *get_successor_for_node_with_value_n(int n) const {
    // Each entry is binary multiplied, as in ith entry shows the successor for
    // (2^i)%BUCKETS
    return entries[log2(n)].get_successor();
  }

  const int number_of_entries() { return entries.size(); }
};

} // namespace load_balancer::finger_table
