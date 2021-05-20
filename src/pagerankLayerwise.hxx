#pragma once
#include <vector>
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "pagerank.hxx"
#include "pagerankMonolithic.hxx"

using std::vector;




template <class T, class J>
int pagerankLayerwiseLoop(vector<T>& a, vector<T>& r, const vector<T>& f, vector<T>& c, const vector<int>& vfrom, const vector<int>& efrom, const vector<int>& vdata, J&& ns, int N, T p, T E, int L) {
  int v = 0; float l = 0;
  for (int n : ns)
    l += pagerankMonolithicLoop(a, r, f, c, vfrom, efrom, vdata, v, v+=n, N, p, E, L) * float(n)/float(N);
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
template <class G, class T=float>
PagerankResult<T> pagerankLayerwise(const G& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  T    p = o.damping;
  T    E = o.tolerance;
  int  L = o.maxIterations, l;
  auto xc     = csr(xt);
  auto& vfrom = xc.sourceOffsets;
  auto& efrom = xc.destinationIndices;
  auto vdata  = vertexData(xt);
  int  N      = xt.order();
  vector<T> a(N), r(N), f(N), c(N);
  vector<T> *qc = q? new vector<T> : nullptr;
  if (q) *qc = compressContainer(xt, *q);
  float t = measureDuration([&]() { l = pagerankMonolithicCore(a, r, f, c, vfrom, efrom, vdata, N, qc, p, E, L); }, o.repeat);
  return {decompressContainer(xt, a), l, t};
}
