#pragma once
#include <vector>
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "components.hxx"
#include "blockgraph.hxx"
#include "topologicalSort.hxx"
#include "pagerank.hxx"
#include "pagerankMonolithic.hxx"

using std::vector;




template <class G, class H, class T>
auto pagerankComponents(const G& x, const H& xt, const PagerankOptions<T>& o) {
  auto a = joinUntilSize(components(x, xt), o.minComponentSize);
  auto b = blockgraph(x, a);
  auto bks = topologicalSort(b);
  reorder(a, bks);
  return a;
}


template <class T, class J>
int pagerankLayerwiseLoop(vector<T>& a, vector<T>& r, const vector<T>& f, vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, J&& ns, int N, T p, T E, int L) {
  int v = 0; float l = 0;
  for (int n : ns) {
    int k = pagerankMonolithicLoop(a, r, f, c, vfrom, efrom, vdata, v, v+n, N, p, E, L);
    l += k * (float(n)/N);
    v += n;
  }
  return int(l);
}

template <class T, class J>
int pagerankLayerwiseCore(vector<T>& a, vector<T>& r, vector<T>& f, vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, J&& ns, int N, const vector<T> *q, T p, T E, int L) {
  if (q) copy(r, *q);
  else fill(r, T(1)/N);
  pagerankFactor(f, vfrom, efrom, vdata, 0, N, N, p);
  return pagerankLayerwiseLoop(a, r, f, c, vfrom, efrom, vdata, ns, N, p, E, L);
}


// Find pagerank of components in topological order (pull, CSR).
// @param xt transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankLayerwise(const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations, l;
  int  N = xt.order();
  auto cs = pagerankComponents(x, xt, o);
  auto ks = join(cs);
  auto ns = transform(cs, [](const auto& c) { return c.size(); });
  auto vfrom = sourceOffsets(xt, ks);
  auto efrom = destinationIndices(xt, ks);
  auto vdata = vertexData(xt, ks);
  vector<T> a(N), r(N), f(N), c(N);
  vector<T> *qc = q? new vector<T> : nullptr;
  if (q) *qc = compressContainer(xt, *q, ks);
  float t = measureDuration([&]() { l = pagerankLayerwiseCore(a, r, f, c, vfrom, efrom, vdata, ns, N, qc, p, E, L); }, o.repeat);
  return {decompressContainer(xt, a, ks), l, t};
}
