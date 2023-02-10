#pragma once
#include <vector>
#include <utility>

using std::vector;
using std::move;




// PAGERANK-OPTIONS
// ----------------

template <class T>
struct PagerankOptions {
  int repeat;
  T   tolerance;
  int toleranceNorm;
  T   damping;
  int maxIterations;

  PagerankOptions(int repeat=1, T tolerance=1e-6, int toleranceNorm=1, T damping=0.85, int maxIterations=500) :
  repeat(repeat), tolerance(tolerance), toleranceNorm(toleranceNorm), damping(damping), maxIterations(maxIterations) {}
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
