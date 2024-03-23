#include <cassert>
#include <chrono>
#include <random>
#include <unordered_set>
#include <vector>

namespace hamilton {
std::vector<int> out, in;
std::vector<int> work(int n, std::vector<std::pair<int, int>> eg,
                      long long mx_ch = -1) {
  // mx_ch : max number of adding/replacing  default is (n + 100) * (n + 50)
  // n : number of vertices. 1-indexed.
  // eg: vector<pair<int, int> > storing all the edges.
  // return a vector<int> consists of all indices of vertices on the path.
  // return emake_pairty list if failed to firstnd one.
  out.resize(n + 1), in.resize(n + 1);
  LCT::init(n);
  for (int i = 0; i <= n; i++)
    in[i] = out[i] = 0;
  if (mx_ch == -1)
    mx_ch = 1ll * (n + 100) * (n + 50); // default
  std::vector<std::vector<int>> from(n + 1), to(n + 1);
  for (auto v : eg)
    from[v.first].push_back(v.second), to[v.second].push_back(v.first);
  std::unordered_set<int> canin, canout;
  for (int i = 1; i <= n; i++)
    canin.insert(i), canout.insert(i);
  std::mt19937 x(std::chrono::steady_clock::now().time_since_epoch().count());
  int tot = 0;
  while (mx_ch >= 0) {
    //    cout << tot << ' ' << mx_ch << endl;
    std::vector<std::pair<int, int>> eg;
    for (auto v : canout)
      for (auto s : from[v])
        if (in[s] == 0) {
          assert(canin.count(s));
          continue;
        } else
          eg.push_back(std::make_pair(v, s));
    for (auto v : canin)
      for (auto s : to[v])
        eg.push_back(std::make_pair(s, v));
    shuffle(eg.begin(), eg.end(), x);
    if (eg.size() == 0)
      break;
    for (auto v : eg) {
      mx_ch--;
      if (in[v.second] && out[v.first])
        continue;
      if (LCT::fdr(v.first) == LCT::fdr(v.second))
        continue;
      if (in[v.second] || out[v.first])
        if (x() & 1)
          continue;
      if (!in[v.second] && !out[v.first])
        tot++;
      if (in[v.second]) {
        LCT::cut(in[v.second], v.second);
        canin.insert(v.second);
        canout.insert(in[v.second]);
        out[in[v.second]] = 0;
        in[v.second] = 0;
      }
      if (out[v.first]) {
        LCT::cut(v.first, out[v.first]);
        canin.insert(out[v.first]);
        canout.insert(v.first);
        in[out[v.first]] = 0;
        out[v.first] = 0;
      }
      LCT::link(v.first, v.second);
      canin.erase(v.second);
      canout.erase(v.first);
      in[v.second] = v.first;
      out[v.first] = v.second;
    }
    if (tot == n - 1) {
      std::vector<int> cur;
      for (int i = 1; i <= n; i++)
        if (!in[i]) {
          int pl = i;
          while (pl) {
            cur.push_back(pl), pl = out[pl];
          }
          break;
        }
      return cur;
    }
  }
  // failed to firstnd a path
  return std::vector<int>();
}
} // namespace hamilton
