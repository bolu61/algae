#include <catch2/catch_test_macros.hpp>
#include <algae/tree/k_ary_tree.hxx>

TEST_CASE("k_ary_tree construction", "[k_ary_tree]") {
  algae::k_ary_tree<int, 2> t;
  algae::k_ary_tree<int, 2>::node * a = t.make_root(0);
  algae::k_ary_tree<int, 2>::node * b = t.make_child(a, 0, 1);
  algae::k_ary_tree<int, 2>::node * c = t.make_child(a, 1, 2);
  REQUIRE(a->data == 0);
  REQUIRE(b->data == 1);
  REQUIRE(c->data == 2);
}
