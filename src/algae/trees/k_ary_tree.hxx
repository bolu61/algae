#pragma once

#include <algae/trees/tree_container.hxx>
#include <array>
#include <cstddef>
#include <memory>

namespace algae {
  namespace bare {
    template<typename data_type, std::size_t k>
    struct k_ary_tree {
      k_ary_tree * parent;
      std::array<k_ary_tree *, k> children;
      data_type data;

      template<typename... as>
      k_ary_tree(as &&... a) : parent(nullptr), children(), data(std::forward<as>(a)...){};
    };
  } // namespace bare

  template<
    typename data_type,
    std::size_t k,
    typename allocator = std::allocator<void>>
  struct k_ary_tree :
    private tree_container<bare::k_ary_tree<data_type, k>, allocator> {
    using node = algae::bare::k_ary_tree<data_type, k>;

    using tree_container<node, allocator>::root;
    using tree_container<node, allocator>::emplace_root;

    template<typename... arguments>
    node * emplace_child(node * u, std::size_t i, arguments &&... args) {
      node * v = tree_container<node, allocator>::emplace(u->children[i], std::forward<arguments>(args)...);
      v->parent = u;
      return v;
    };
  };
}; // namespace algae
