#pragma once

#include<string>
#include<utility>
namespace load_balancer::node{
  class Node{
    std::string ip_;
    std::string node_name_;

    public:
      explicit Node(std::&string ip, std::&string node_name) : ip_(std::move(ip)), node_name_(std::move(node_name)) {}
      const std::string& ip() const noexcept { return ip_; }
      const std::string& node_name const noexcept { return node_name_; }
  }
};
