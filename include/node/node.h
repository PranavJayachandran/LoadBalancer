#pragma once

#include <string>

// Forward declaration
namespace load_balancer::finger_table {
class FingerTable;
class FingerEntries;
} // namespace load_balancer::finger_table

namespace load_balancer::node {

class Node {
private:
  int node_position_ = 0;
  std::string ip_;
  std::string node_name_;
  load_balancer::finger_table::FingerTable *finger_table_ = nullptr;

  bool is_between(int value, int start, int end);
  Node *get_successor();

public:
  explicit Node(const std::string &ip, const std::string &node_name,
                int node_position);

  const std::string &ip() const noexcept;
  const std::string &node_name() const noexcept;

  Node *find_successor(int id);
  Node *find_predecessor(int id);
  Node *closest_preceding_finger(int id);
};

} // namespace load_balancer::node
