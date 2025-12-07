#include "../include/node/node.h"
#include <gtest/gtest.h>

using namespace load_balancer::node;

TEST(NodeTest, if_join_for_first_node) {
  // Arrange
  load_balancer::node::Node *node =
      new Node("test_ip", "test_name", 1, nullptr);

  // Act

  // Assert
  EXPECT_EQ(node->find_successor(1), node);
  EXPECT_EQ(node->find_successor(1), node);
}

TEST(NodeTest, if_join_for_second_node) {
  // Arrange
  load_balancer::node::Node *node1 =
      new Node("test_ip", "test_name", 0, nullptr);

  // Act
  load_balancer::node::Node *node2 =
      new Node("test_ip_2", "test_name_2", 1, node1);

  // Assert
  EXPECT_EQ(node2->find_successor(2), node1);
  EXPECT_EQ(node2->find_successor(3), node1);
  EXPECT_EQ(node2->find_successor(5), node1);

  EXPECT_EQ(node1->find_successor(1), node1);
  EXPECT_EQ(node1->find_successor(2), node1);
  EXPECT_EQ(node1->find_successor(4), node1);
}

TEST(NodeTest, if_join_for_thrid_node) {
  // Arrange
  load_balancer::node::Node *node1 =
      new Node("test_ip", "test_name", 0, nullptr);

  // Act
  load_balancer::node::Node *node2 =
      new Node("test_ip_2", "test_name_2", 1, node1);

  load_balancer::node::Node *node3 =
      new Node("test_ip_3", "test_name_3", 3, node1);

  // Assert

  EXPECT_EQ(node3->find_successor(4), node1);
  EXPECT_EQ(node3->find_successor(5), node1);
  EXPECT_EQ(node3->find_successor(7), node1);

  EXPECT_EQ(node2->find_successor(2), node1);
  EXPECT_EQ(node2->find_successor(3), node1);
  EXPECT_EQ(node2->find_successor(5), node1);

  EXPECT_EQ(node1->find_successor(1), node3);
  EXPECT_EQ(node1->find_successor(2), node3);
  EXPECT_EQ(node1->find_successor(4), node1);
}
