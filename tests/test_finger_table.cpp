#include "../include/node/finger_table.h"
#include "../include/node/node.h"
#include <gtest/gtest.h>
#include <stdlib.h>
#include <string>

using namespace load_balancer::finger_table;

TEST(FingerTableTest, updates_successor_for_nth_finger) {

  // Arrange
  FingerTable *finger_table = new FingerTable(1);
  const std::string test_ip = "test_ip";
  const std::string test_name = "test_name";
  load_balancer::node::Node *node = new Node(test_ip, test_name, 1, nullptr);
  int n = log2(rand() % load_balancer::constants::BUCKETS);

  // Act
  // This would add mean the nth (0 indexed) entry would be node -> succesor for
  // 2^n would be node
  finger_table->update_successor_for_nth_finger(n, node);

  // Assert
  EXPECT_EQ(finger_table->get_successor_for_node_with_value_n(pow(2, n)), node);
}

TEST(FingerTableTest,
     get_successor_for_node_with_value_n_Works_for_k_minus_one_th_power_of_2) {

  // Arrange
  FingerTable *finger_table = new FingerTable(1);
  const std::string test_ip = "test_ip";
  const std::string test_name = "test_name";
  load_balancer::node::Node *node = new Node(test_ip, test_name, 1, nullptr);
  load_balancer::node::Node *node2 = new Node(test_ip, test_name, 1, nullptr);
  int n = log2(rand() % (load_balancer::constants::BUCKETS - 1));

  // Act
  // This would add mean the 2nd (0 indexed) entry would be node -> succesor for
  // 2^1 would be node
  finger_table->update_successor_for_nth_finger(n, node2);
  finger_table->update_successor_for_nth_finger(n - 1, node);

  // Assert
  EXPECT_EQ(finger_table->get_successor_for_node_with_value_n(pow(2, n - 1)),
            node);
}

TEST(
    FingerTableTest,
    get_successor_for_node_with_value_n_Works_for_all_values_between_k_minus_oneth_and_kth_power_of_2) {

  // Arrange
  FingerTable *finger_table = new FingerTable(1);
  const std::string test_ip = "test_ip";
  const std::string test_name = "test_name";
  load_balancer::node::Node *node = new Node(test_ip, test_name, 1, nullptr);
  load_balancer::node::Node *node2 = new Node(test_ip, test_name, 1, nullptr);
  int n = log2(rand() % (load_balancer::constants::BUCKETS - 1));

  // Act
  // This would add mean the 2nd (0 indexed) entry would be node -> succesor for
  // 2^1 would be node
  finger_table->update_successor_for_nth_finger(n, node2);
  finger_table->update_successor_for_nth_finger(n - 1, node);

  // Assert
  for (int i = n + 1; i <= n; i++) {
    EXPECT_EQ(finger_table->get_successor_for_node_with_value_n(pow(2, i)),
              node);
  }
}
