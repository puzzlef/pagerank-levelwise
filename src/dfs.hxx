#pragma once
#include <vector>
#include "vertices.hxx"

using std::vector;




// DFS
// ---
// Traverses nodes in depth-first manner, listing on entry.

template <class G>
void dfsLoop(vector<int>& a, vector<bool>& vis, const G& x, int u) {
  vis[u] = true;
  a.push_back(u);
  for (int v : x.edges(u))
    if (!vis[v]) dfsLoop(a, vis, x, v);
}

template <class G>
auto dfs(const G& x, int u) {
  vector<int> a;
  auto vis = createContainer(x, bool());
  dfsLoop(a, vis, x, u);
  return a;
}




// DFS-END
// -------
// Traverses nodes in depth-first manner, listing on exit.

template <class G>
void dfsEndLoop(vector<int>& a, vector<bool>& vis, const G& x, int u) {
  vis[u] = true;
  for (int v : x.edges(u))
    if (!vis[v]) dfsEndLoop(a, vis, x, v);
  a.push_back(u);
}

template <class G>
auto dfsEnd(const G& x, int u) {
  vector<int> a;
  auto vis = createContainer(x, bool());
  dfsEndLoop(a, vis, x, u);
  return a;
}
