#include <cmath>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




template <class G, class H>
void runPagerank(const G& x, const H& xt, bool show) {
  int repeat = 5; bool skipTeleport = true;
  vector<float> *init = nullptr;

  // Find monolithic pagerank.
  auto a1 = pagerankMonolithic(xt, init, {repeat});
  auto e1 = l1Norm(a1.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithic\n", a1.time, a1.iterations, e1);

  // Find monolithic pagerank, skipping teleport.
  auto a2 = pagerankMonolithic(xt, init, {repeat, skipTeleport});
  auto e2 = l1Norm(a2.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankMonolithic [skip-tele]\n", a2.time, a2.iterations, e2);

  // Find levelwise pagerank.
  auto a3 = pagerankLevelwise(x, xt, init, {repeat});
  auto e3 = l1Norm(a3.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwise\n", a3.time, a3.iterations, e3);

  // Find levelwise pagerank, skipping teleport.
  auto a4 = pagerankLevelwise(x, xt, init, {repeat, skipTeleport});
  auto e4 = l1Norm(a4.ranks, a1.ranks);
  printf("[%09.3f ms; %03d iters.] [%.4e err.] pagerankLevelwise [skip-tele]\n", a4.time, a4.iterations, e4);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Loading graph %s ...\n", file);
  auto x  = readMtx(file); println(x);
  loopDeadEnds(x); print(x); printf(" (loopDeadEnds)\n");
  auto xt = transposeWithDegree(x); print(xt); printf(" (transposeWithDegree)\n");
  runPagerank(x, xt, show);
  printf("\n");
  return 0;
}
