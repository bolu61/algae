#include <algae/trees/tree_container.hxx>
#include <utility>

namespace algae {
  namespace bare {
    template<typename data_type>
    struct binary_tree {
      binary_tree * parent;
      binary_tree * left;
      binary_tree * right;
      data_type data;

      template<typename... as>
      binary_tree(as &&... a) : parent(nullptr), left(nullptr), right(nullptr), data(std::forward<as>(a)...){};

      bool is_left() {
        return this->parent->left == this;
      };

      bool is_right() {
        return this->parent->right == this;
      };
    };
  } // namespace bare

  template<typename data_type, typename allocator = std::allocator<void>>
  struct binary_tree : tree_container<bare::binary_tree<data_type>, allocator> {
    using node = bare::binary_tree<data_type>;

    using tree_container<node, allocator>::root;
    using tree_container<node, allocator>::emplace_root;

    template<typename... arguments>
    node * emplace_left(node * u, arguments &&... args) {
      node * v = this->emplace(u->left, std::forward<arguments>(args)...);
      v->parent = u;
      return v;
    };

    template<typename... arguments>
    node * emplace_right(node * u, arguments &&... args) {
      node * v = this->emplace(u->right, std::forward<arguments>(args)...);
      v->parent = u;
      return v;
    };
  };
}; // namespace algae
