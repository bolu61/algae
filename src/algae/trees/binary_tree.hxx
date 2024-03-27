#include <algae/trees/k_ary_tree.hxx>

namespace algae {
  namespace binary_trees {
    template<typename data_type>
    struct node {
      node * parent;
      node * left;
      node * right;
      data_type data;

      template<typename... as>
      node(as &&... a) : data(std::forward<as>(a)...){};

      bool is_left() {
        return this->parent->left == this;
      };

      bool is_right() {
        return this->parent->right == this;
      };
    };
  } // namespace

  template<typename data_type, typename allocator = std::allocator<data_type>>
  struct binary_tree : tree<binary_trees::node<data_type>, allocator> {
    struct node {
      node * parent;
      node * left;
      node * right;
      data_type data;

      template<typename... as>
      node(as &&... a) : data(std::forward<as>(a)...){};

      bool is_left() {
        return this->parent->left == this;
      };

      bool is_right() {
        return this->parent->right == this;
      };
    };
  };
}; // namespace algae
