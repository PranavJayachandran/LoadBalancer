#include "../../include/node/node.h"
#include "../../include/node/finger_table.h"

using namespace load_balancer::node;
using namespace load_balancer::finger_table;

Node::Node(const std::string &ip, const std::string &node_name,
           int node_position, Node *node)
    : ip_(ip), node_name_(node_name), node_position_(node_position) {
  finger_table_ = new FingerTable(node_position);
  // If this is not the first entry
  if (node != nullptr) {
    init_finger_table(node);
    update_others();
  } else {
    for (int i = 0; i < finger_table_->number_of_entries(); i++) {
      finger_table_->update_successor_for_nth_finger(i, this);
    }
    predecessor = this;
  }
}

const std::string &Node::ip() const noexcept { return ip_; }

const std::string &Node::node_name() const noexcept { return node_name_; }

bool Node::is_between(int value, int start, int end) {
  if (start < end) {
    return value > start && value <= end;
  }
  return value > start || value <= end;
}

void Node::init_finger_table(Node *node) {
  FingerEntries *first_finger = finger_table_->get_nth_finger(0);
  Node *successor = node->find_successor(first_finger->value);
  finger_table_->update_successor_for_nth_finger(0, successor);

  predecessor = successor->predecessor;
  successor->predecessor = this;

  for (int i = 1; i < finger_table_->number_of_entries(); i++) {
    FingerEntries *current_finger = finger_table_->get_nth_finger(i);
    FingerEntries *prev_finger = finger_table_->get_nth_finger(i - 1);

    if (is_between(current_finger->value, node_position_,
                   prev_finger->get_successor()->node_position_)) {
      finger_table_->update_successor_for_nth_finger(
          i, prev_finger->get_successor());
    } else {
      finger_table_->update_successor_for_nth_finger(
          i, node->find_successor(current_finger->value));
    }
  }
}

void Node::update_others() {
  for (int i = 0; i < finger_table_->number_of_entries(); i++) {
    int val = (node_position_ - (int)pow(2, i) + constants::BUCKETS) %
              constants::BUCKETS;
    Node *p = find_predecessor(val);

    if (p != this) {
      p->update_finger_table(this, i);
    }
  }
}

void Node::update_finger_table(Node *s, int i) {
  FingerEntries *ith_finger = finger_table_->get_nth_finger(i);

  if (is_between(s->node_position_, node_position_,
                 ith_finger->get_successor()->node_position_) ||
      s->node_position_ == node_position_) {

    finger_table_->update_successor_for_nth_finger(i, s);

    Node *p = predecessor;
    if (p != this && p != s) {
      p->update_finger_table(s, i);
    }
  }
}

Node *Node::get_successor() {
  return finger_table_->get_nth_finger(0)->get_successor();
}

Node *Node::find_successor(int id) {
  id = (id % constants::BUCKETS + constants::BUCKETS) % constants::BUCKETS;

  Node *n_prime = find_predecessor(id);
  return n_prime->get_successor();
}

Node *Node::find_predecessor(int id) {
  id = (id % constants::BUCKETS + constants::BUCKETS) % constants::BUCKETS;

  Node *n_prime = this;
  Node *succ = n_prime->get_successor();

  while (!is_between(id, n_prime->node_position_, succ->node_position_)) {
    n_prime = n_prime->closest_preceding_finger(id);
    succ = n_prime->get_successor();

    if (n_prime == this && succ == this) {
      break;
    }
  }
  return n_prime;
}

Node *Node::closest_preceding_finger(int id) {
  id = (id % constants::BUCKETS + constants::BUCKETS) % constants::BUCKETS;

  for (int i = finger_table_->number_of_entries() - 1; i >= 0; i--) {
    const FingerEntries *nth_finger = finger_table_->get_nth_finger(i);
    Node *finger_node = nth_finger->get_successor();

    if (is_between(finger_node->node_position_, node_position_, id)) {
      return finger_node;
    }
  }
  return this;
}

void Node::add_successors(Node *node) {
  for (int i = 0; i < finger_table_->number_of_entries(); i++) {
    int value = (node_position_ + (int)pow(2, i)) % constants::BUCKETS;
    Node *successor = node->find_successor(value);
    finger_table_->update_successor_for_nth_finger(i, successor);
  }
}
