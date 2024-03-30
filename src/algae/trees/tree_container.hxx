#pragma once

#include <memory>

namespace algae {
  template<typename tree_type, typename allocator = std::allocator<tree_type>>
  class tree_container {
    using alloc = typename std::allocator_traits<
      allocator>::template rebind_traits<tree_type>;

    typename alloc::allocator_type a;

    public:

    tree_type * root;

    tree_container() : root(nullptr), a(){};

    template<typename... arguments>
    tree_container(arguments &&... args) :
      root(nullptr),
      a(std::forward(args)...){};

    tree_container(tree_type * root, const alloc::allocator_type & a) :
      root(nullptr),
      a(a){};

    template<typename... arguments>
    tree_type * emplace_root(arguments &&... args) {
      this->root = alloc::allocate(a, 1);
      alloc::construct(a, this->root, std::forward<arguments>(args)...);
      return this->root;
    };

    template<typename... arguments>
    tree_type * emplace(tree_type *& u, arguments &&... args) {
      u = alloc::allocate(a, 1);
      alloc::construct(a, u, std::forward<arguments>(args)...);
      return u;
    };

    void erase(tree_type *& u) {
      allocator::destroy(a, u);
      allocator::deallocate(a, u);
      u = nullptr;
    };
  };
}; // namespace algae
