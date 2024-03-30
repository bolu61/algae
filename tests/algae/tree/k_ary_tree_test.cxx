#include <algae/trees/k_ary_tree.hxx>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("k_ary_tree construction", "[k_ary_tree][tree][data_structure]") {
  algae::k_ary_tree<int, 2> t;

  t.emplace_root(0);
  t.emplace_child(t.root, 0, 1);
  t.emplace_child(t.root, 1, 2);
  REQUIRE(t.root != nullptr);
  REQUIRE(t.root->parent == nullptr);
  REQUIRE(t.root->children[0]->parent == t.root);
  REQUIRE(t.root->children[1]->parent == t.root);
  REQUIRE(t.root->children[0]->children[0] == nullptr);
  REQUIRE(t.root->children[0]->children[1] == nullptr);
  REQUIRE(t.root->children[1]->children[0] == nullptr);
  REQUIRE(t.root->children[1]->children[1] == nullptr);
  REQUIRE(t.root->data == 0);
  REQUIRE(t.root->children[0]->data == 1);
  REQUIRE(t.root->children[1]->data == 2);
}
