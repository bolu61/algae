#include "node.hxx"

#include <vector>

namespace algae {

  // Splay Tree implementation
  // inspired by https://codeforces.com/blog/entry/79524
  struct splay_tree {
    splay_tree(size_t size) : root(-1), p(size, -1), l(size, -1), r(size, -1){};

    enum class side_t : bool {
      left = true,
      right = false
    };

    node emplace(const node & parent, const node & left, const node & right) {
      node u = n++;
      if (!root) {
        root = u;
      } else {
        p.emplace_back(parent);
      };
      l.emplace_back(left);
      r.emplace_back(right);
      return u;
    };

    void splay(const node & u) {
      while (p[u]) {
        if (p[p[u]]) {
          rotate(side(u) == side(p[u]) ? p[u] : u);
        };
        rotate(u);
      };
    };


    private:

    // parent, left child and right child of node
    node root;
    size_t n;
    std::vector<node> p, l, r;

    void rotate(const node & u) {
      node v = p[u];
      side_t s = side(u);
      if (p[v]) {
        attach(side(v), p[v], u);
      } else {
        root = u;
        p[u] = -1;
      };
      attach(side(u), v, child(opposite(side(u)), u));
      attach(opposite(side(u)), u, v);
    };

    void attach(const side_t & s, const node & u, const node & v) {
      p[v] = u;
      child(s, u) = v;
    };

    side_t opposite(const side_t & s) {
      return side_t(!static_cast<bool>(s));
    };

    node & child(const side_t & s, const node & u) {
      switch (s) {
        case side_t::left:
          return l[u];
        case side_t::right:
          return r[u];
      }
    }

    side_t side(const node & u) {
      return side_t(l[p[u]] == u);
    };
  };
} // namespace algae
