#pragma once

#include <memory>

namespace algae {
  template<typename node, typename allocator = std::allocator<node>>
  struct tree {
    node * root;

    template<typename... arguments>
    node * emplace(node * u, node *& v, arguments &&... args);

    void erase(node * u, node *& v);

    private:

    using alloc = typename std::allocator_traits<allocator>::template rebind_traits<node>;
    typename alloc::allocator_type a;
  };

  template<typename node>
  node * parent(node *);

  template<typename node, typename range>
  range children(node *);
} // namespace algae

template<typename node, typename allocator>
template<typename... arguments>
node * algae::tree<node, allocator>::emplace(
  node * u,
  node *& v,
  arguments &&... args
) {
  v = alloc::allocate(a, 1);

  alloc::construct(a, v, std::forward<arguments>(args)...);

  v->parent = u;

  return v;
};

template<typename node, typename allocator>
void algae::tree<node, allocator>::erase(node * u, node *& v) {
  for (node * w : children(v)) {
    erase(v, w);
  };
  v = nullptr;
  allocator::destroy(a, v);
  allocator::deallocate(a, v);
};
