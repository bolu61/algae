#include <algae/trees/k_ary_tree.hxx>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("k_ary_tree construction", "[k_ary_tree]") {
  algae::k_ary_tree<int, 2> t;

  SECTION("root construction") {
    t.emplace(nullptr, t.root, 0);
    REQUIRE(t.root->data == 0);
  }

  SECTION("children construction") {
    t.emplace(t.root, 0, 1);
    t.emplace(t.root, 1, 2);
    REQUIRE(t.root->children[0]->data == 1);
    REQUIRE(t.root->children[1]->data == 2);
  }
}
