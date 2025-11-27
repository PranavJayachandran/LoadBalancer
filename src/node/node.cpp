
#include "../../include/node/node.h"
#include "../../include/node/finger_table.h"

using namespace load_balancer::node;
using namespace load_balancer::finger_table;

Node::Node(const std::string &ip, const std::string &node_name,
           int node_position)
    : ip_(ip), node_name_(node_name), node_position_(node_position) {
  finger_table_ = new FingerTable(node_position);
}

const std::string &Node::ip() const noexcept { return ip_; }

const std::string &Node::node_name() const noexcept { return node_name_; }

bool Node::is_between(int value, int start, int end) {
  if (start < end) {
    return value >= start && value <= end;
  }
  return value >= end || value <= start;
}

Node *Node::get_successor() {
  return finger_table_->get_successor_for_node_with_value_n(node_position_ + 1);
}

Node *Node::find_successor(int id) {
  Node *n_dash = find_predecessor(id);
  return n_dash->get_successor();
}

Node *Node::find_predecessor(int id) {
  Node *n_dash = this;
  while (!is_between(id, n_dash->node_position_,
                     n_dash->get_successor()->node_position_)) {
    n_dash = n_dash->closest_preceding_finger(id);
  }
  return n_dash;
}

Node *Node::closest_preceding_finger(int id) {
  for (int i = finger_table_->number_of_entries() - 1; i >= 0; i--) {
    const FingerEntries *nth_finger = finger_table_->get_nth_finger(i);
    if (is_between(nth_finger->value, node_position_, id)) {
      return nth_finger->get_successor();
    }
  }
  return this;
}
