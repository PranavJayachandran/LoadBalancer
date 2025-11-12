#pragma once

#include "../node/node.h"
#include <cassert>
#include <string>
#include <vector>

namespace load_balancer::router {
class Router {
private:
  std::vector<load_balancer::node::Node> nodes;
  int get_hash(const std::string &key) {
    // Use some hash function here.
    return 0;
  }

public:
  load_balancer::node::Node get_node(const std::string &key) {
    int hash = get_hash(key);
    assert(hash < static_cast<int>(nodes.size()));
    return nodes[hash];
  }

  void add_node(const std::string &ip, const std::string &node_name) {
    nodes.emplace_back(ip, node_name);
  }
};
} // namespace load_balancer::router
