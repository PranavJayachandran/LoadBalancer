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

  void init_finger_table(Node *node);
  bool is_between(int value, int start, int end);
  Node *get_successor();
  Node *closest_preceding_finger(int id);
  void update_others();
  void update_finger_table(Node *node, int entry);

public:
  Node *predecessor;
  explicit Node(const std::string &ip, const std::string &node_name,
                int node_position, Node *node);

  const std::string &ip() const noexcept;
  const std::string &node_name() const noexcept;

  Node *find_successor(int id);
  Node *find_predecessor(int id);
  void add_successors(Node *node);
};

} // namespace load_balancer::node
