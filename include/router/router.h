#pragma once

#include<vector>
#include<string>
#include "../node/node.h"

namespace load_balancer::router {
  class Router{
    private:
      std::vector<load_balancer::node::Node> nodes;
      int get_hash(const std::string& key){
        //Use some hash function here.
        return 0;
      }
    public:
      load_balancer::node::Node get_node(const string& key){
        int hash = get_hash(key);
        assert(hash < static_cast<int>(node.size()));
        return nodes[hash];
      }

      void add_node(const string& ip, const string& node_name){
        nodes.emplace_back(ip, node_name);
      }
  }
}
