#pragma once

#include <array>
#include <cstddef>
#include <memory>

namespace algae {
  namespace {

    template<typename data_type, std::size_t k>
    struct node {
      template<typename... as>
      node(as &&... a) : data(std::forward<as>(a)...){};
      node<data_type, k> * parent;
      std::array<node<data_type, k> *, k> child;
      data_type data;
    };

  }; // namespace

  template<
    typename value,
    std::size_t k,
    typename allocator = std::allocator<value>>
  struct k_ary_tree {
    using node = node<value, k>;

    node *& root() {
      return r;
    };

    void attach(node * u, std::size_t c, node * v) {
      u->child[c] = v;
      v->parent = u;
    };

    template<typename... arguments>
    node * make_root(arguments &&... args) {
      node * u = make_node(std::forward<arguments>(args)...);
      root() = u;
      return u;
    };

    template<typename... arguments>
    node * make_child(node * u, std::size_t c, arguments &&... args) {
      node * v = make_node(std::forward<arguments>(args)...);
      attach(u, c, v);
      return v;
    };

    private:

    using alloc_traits = std::allocator_traits<allocator>;
    using alloc = typename alloc_traits::template rebind_traits<node>;

    typename alloc::allocator_type a;
    node * r;

    template<typename... arguments>
    node * make_node(arguments &&... args) {
      node * u = alloc::allocate(a, 1);
      alloc::construct(a, u, std::forward<arguments>(args)...);
      return u;
    };

  };
}; // namespace algae
