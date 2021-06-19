Performance of standard (**monolithic**) vs topologically-ordered components
(**levelwise**) PageRank ([pull], [CSR], [compute-10]).

This experiment was for comparing performance between:
1. Find pagerank with standard algorithm (**monolithic**).
2. Find pagerank in topologically-ordered components fashion (**levelwise**).

Both approaches were attempted on different types of graphs, running each
approach 5 times per graph to get a good time measure. **Levelwise** pagerank
is the [STIC-D algorithm], without **ICD** optimizations (using single-thread).
On average, **levelwise** pagerank is faster than the **monolithic** approach.

All outputs are saved in [out](out/) and a small part of the output is listed
here. All [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. For previous experiments, see [branches].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (loopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00395.793 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00244.404 ms; 054 iters.] [4.3718e-06 err.] pagerankLevelwise
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 69532892 {} (loopDeadEnds)
# order: 4847571 size: 69532892 {} (transposeWithDegree)
# [12915.615 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithic
# [10037.996 ms; 048 iters.] [4.7744e-06 err.] pagerankLevelwise
#
# ...
```

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/ewKOeWS.jpg)](https://www.youtube.com/watch?v=eBW0s125f-Y)

[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[monolithic]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[compute-10]: https://github.com/puzzlef/pagerank-levelwise-adjust-compute-size
[branches]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise/branches
[charts]: https://photos.app.goo.gl/KgBUFkTrHGB4WBfs9
[sheets]: https://docs.google.com/spreadsheets/d/10KhCjLln713-qWsQMURTQKmQsniTO0xwGzNeQkuV3sE/edit?usp=sharing
