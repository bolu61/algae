#pragma once

#include <array>
#include <cstddef>
#include <memory>

namespace algae {
  template<
    typename value_type,
    std::size_t k,
    typename allocator = std::allocator<value_type>>
  struct k_ary_tree {
    struct node {
      template<typename... as>
      node(as &&... a) : data(std::forward<as>(a)...){};
      node * parent;
      std::array<node *, k> child;
      value_type data;
    };

    node *& root() {
      return r;
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
      u->child[c] = v;
      v->parent = u;
      return v;
    };

    void erase(node * u, std::size_t i) {
      if (!u) {
        return;
      };
      node * v = u->child[i];
      for (std::size_t j = 0; j < k; j++) {
        erase(v, j);
      }
      u->child[i] = nullptr;
      alloc::destroy(a, v);
      alloc::deallocate(a, v);
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
