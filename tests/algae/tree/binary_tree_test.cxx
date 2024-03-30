#include <algae/trees/binary_tree.hxx>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("binary_tree construction", "[binary_tree][tree][data_structure]") {
  algae::binary_tree<int> t;

  t.emplace_root(0);
  t.emplace_left(t.root, 1);
  t.emplace_right(t.root, 2);
  REQUIRE(t.root != nullptr);
  REQUIRE(t.root->parent == nullptr);
  REQUIRE(t.root->left->parent == t.root);
  REQUIRE(t.root->right->parent == t.root);
  REQUIRE(t.root->left->left == nullptr);
  REQUIRE(t.root->left->right == nullptr);
  REQUIRE(t.root->right->left == nullptr);
  REQUIRE(t.root->right->right == nullptr);
  REQUIRE(t.root->data == 0);
  REQUIRE(t.root->left->data == 1);
  REQUIRE(t.root->right->data == 2);
}
