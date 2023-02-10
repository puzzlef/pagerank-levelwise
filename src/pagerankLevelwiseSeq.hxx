#pragma once
#include <vector>
#include <algorithm>
#include "vertices.hxx"
#include "edges.hxx"
#include "csr.hxx"
#include "components.hxx"
#include "pagerank.hxx"
#include "pagerankMonolithicSeq.hxx"

using std::vector;
using std::swap;




auto pagerankLevelwiseWaves(const vector2d<int>& cs) {
  vector<int> a;
  for (const auto& c : cs)
    a.push_back(c.size());
  return a;
}


template <class T>
inline T pagerankLevelwiseError(T E, int n, int N, int EF) {
  return EF<=2? E*n/N : E;
}




// PAGERANK-INITIALIZE
// -------------------

template <class T>
void pagerankInitializeDefault(vector<T>& a) {
  int N = a.size();
  fill(a, T(1)/N);
}

template <class T>
void pagerankInitializeComponent(vector<T>& a, const vector2d<int>& cs) {
  int i = 0;
  for (const auto& c : cs) {
    int n = c.size();
    fill(a, i, n, T(1)/n);
    i += n;
  }
}

template <class G, class T>
void pagerankInitializeBlockgraph(vector<T>& a, const G& x, const vector2d<int>& cs, const PagerankOptions<T>& o) {
  vector<T> *init = nullptr;
  auto b  = blockgraph(x, cs);
  auto bt = transposeWithDegree(b);
  auto ba = pagerankMonolithicSeq(bt, init, o);
  for (int i=0, c=0; c<cs.size(); c++) {
    int n = cs[c].size();
    fill(a, i, n, ba.ranks[c]/n);
    i += n;
  }
}

template <class T>
void pagerankInitializeRemaining(vector<T>& a, int i, int n) {
  int N = a.size();
  T   R = 1 - sum(a, 0, i);
  fill(a, i, n, R/N);
}

template <class G, class T>
void pagerankInitialize(vector<T>& a, const G& x, const vector2d<int> cs, const PagerankOptions<T>& o) {
  typedef PagerankInit Init;
  switch (o.initialization) {
    default: pagerankInitializeDefault(a); break;
    case Init::COMPONENT: pagerankInitializeComponent(a, cs); break;
    case Init::BLOCKGRAPH: pagerankInitializeBlockgraph(a, x, cs, o); break;
  }
}




// PAGERANK-LOOP
// --------------

template <class T, class J>
int pagerankLevelwiseSeqLoop(vector<T>& a, vector<T>& r, vector<T>& c, const vector<T>& f, const vector<int>& vfrom, const vector<int>& efrom, int i, J&& ns, int N, T p, T E, int L, int EF, PagerankInit IF) {
  typedef PagerankInit Init;
  float l = 0;
  for (int n : ns) {
    if (n<=0) { i += -n; continue; }
    T np = T(n)/N, En = EF<=2? E*np : E;
    if (IF==Init::REMAINING) pagerankInitializeRemaining(r, i, n);
    l += pagerankMonolithicSeqLoop(a, r, c, f, vfrom, efrom, i, n, N, p, En, L, EF)*np;
    swap(a, r);
    i += n;
  }
  swap(a, r);
  return int(l);
}


// Find pagerank of components in topological order (pull, CSR).
// @param x  current graph
// @param xt current transpose graph, with vertex-data=out-degree
// @param q initial ranks (optional)
// @param o options {damping=0.85, tolerance=1e-6, maxIterations=500}
// @returns {ranks, iterations, time}
template <class G, class H, class T=float>
PagerankResult<T> pagerankLevelwiseSeq(const G& x, const H& xt, const vector<T> *q=nullptr, PagerankOptions<T> o={}) {
  typedef PagerankInit Init;
  T    p  = o.damping;
  T    E  = o.tolerance;
  int  L  = o.maxIterations, l = 0;
  int  EF = o.toleranceNorm;
  Init IF = o.initialization;
  int  N  = xt.order();
  auto cs = sortedComponents(x, xt);
  auto ns = pagerankLevelwiseWaves(cs);
  auto ks = join(cs);
  auto vfrom = sourceOffsets(xt, ks);
  auto efrom = destinationIndices(xt, ks);
  auto vdata = vertexData(xt, ks);
  vector<T> a(N), r(N), c(N), f(N), qc;
  if (q) qc = compressContainer(xt, *q, ks);
  else { qc = vector<T>(N); pagerankInitialize(qc, x, cs, o); }
  float t = measureDurationMarked([&](auto mark) {
    copy(r, qc);  // initialize once!
    copy(a, r);
    mark([&] { pagerankFactor(f, vdata, 0, N, p); });
    mark([&] { l = pagerankLevelwiseSeqLoop(a, r, c, f, vfrom, efrom, 0, ns, N, p, E, L, EF, IF); });
  }, o.repeat);
  return {decompressContainer(xt, a, ks), l, t};
}
