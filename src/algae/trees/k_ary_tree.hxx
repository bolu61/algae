#pragma once

#include <algae/trees/tree.hxx>
#include <array>
#include <cstddef>
#include <memory>

namespace algae {
  namespace {
    template<typename data_type, std::size_t k>
    struct node {
      node * parent;
      std::array<node *, k> children;
      data_type data;

      template<typename... as>
      node(as &&... a) : data(std::forward<as>(a)...){};
    };
  } // namespace

  template<
    typename data_type,
    std::size_t k,
    typename allocator = std::allocator<node<data_type, k>>>
  struct k_ary_tree : public tree<node<data_type, k>, allocator> {
    using node = algae::node<data_type, k>;
    using tree<node, allocator>::emplace;
    using tree<node, allocator>::erase;

    template<typename... arguments>
    node * emplace(node * u, std::size_t i, arguments &&... args) {
      return emplace(u, u->children[i], std::forward<arguments>(args)...);
    };
  };

  template<typename data_type, std::size_t k, typename allocator>
  typename k_ary_tree<data_type, k, allocator>::node *&
  parent(typename k_ary_tree<data_type, k, allocator>::node * u) {
    return u->parent;
  }

  template<typename data_type, std::size_t k, typename allocator>
  std::array<typename k_ary_tree<data_type, k, allocator>::node *, k>
  children(typename k_ary_tree<data_type, k, allocator>::node * u) {
    return u->children;
  }
}; // namespace algae
