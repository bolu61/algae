#pragma once

#include <array>
#include <cstddef>
#include <memory>

namespace algae {
  namespace {

    template<typename value, std::size_t k>
    struct node {
      node<value, k> * parent;
      std::array<node<value, k> *, k> child;
      value v;
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

    template<typename... arguments>
    node *& make_at(node *& u, arguments &&... args) {
      u = std::allocator_traits<allocator>::allocate(1);

      std::allocator_traits<allocator>::construct(
        alloc,
        u,
        std::forward<arguments>(args)...
      );

      return u;
    };

    private:
    allocator alloc;
    node * r;
  };
}; // namespace algae
