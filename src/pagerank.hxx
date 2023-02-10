#pragma once
#include <vector>
#include <utility>

using std::vector;
using std::move;




// PAGERANK INIT
// -------------

enum struct PagerankInit {
  DEFAULT,
  COMPONENT,
  BLOCKGRAPH,
  REMAINING
  // DEFAULT1
};

PagerankInit pagerankInit(int x) {
  typedef PagerankInit Init;
  switch (x) {
    default: return Init::DEFAULT;
    case 1:  return Init::COMPONENT;
    case 2:  return Init::BLOCKGRAPH;
    case 3:  return Init::REMAINING;
  }
}

const char* stringify(const PagerankInit& x) {
  typedef PagerankInit Init;
  switch (x) {
    default: return "default";
    case Init::COMPONENT:  return "component";
    case Init::BLOCKGRAPH: return "blockgraph";
    case Init::REMAINING:  return "remaining";
  }
}




// PAGERANK-OPTIONS
// ----------------

template <class T>
struct PagerankOptions {
  typedef PagerankInit Init;
  int  repeat;
  int  toleranceNorm;
  Init initialization;
  T    damping;
  T    tolerance;
  int  maxIterations;

  PagerankOptions(int repeat=1, int toleranceNorm=1, Init initialization=Init::DEFAULT, T damping=0.85, T tolerance=1e-6, int maxIterations=500) :
  repeat(repeat), toleranceNorm(toleranceNorm), initialization(initialization), damping(damping), tolerance(tolerance), maxIterations(maxIterations) {}
};




// PAGERANK-RESULT
// ---------------

template <class T>
struct PagerankResult {
  vector<T> ranks;
  int   iterations;
  float time;

  PagerankResult(vector<T>&& ranks, int iterations=0, float time=0) :
  ranks(ranks), iterations(iterations), time(time) {}

  PagerankResult(vector<T>& ranks, int iterations=0, float time=0) :
  ranks(move(ranks)), iterations(iterations), time(time) {}
};
