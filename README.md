Performance of standard (monolithic) vs topologically-ordered components
(levelwise) PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find pagerank with standard algorithm (**monolithic** ).
2. Find pagerank in topologically-ordered components fashion (**levelwise**).

Both approaches were attempted on different types of graphs, running each
approach 5 times per graph to get a good time measure. **Levelwise** pagerank
is the [STIC-D algorithm], without **ICD** optimizations (using single-thread).
On average, **levelwise** pagerank faster than **monolithic** pagerank.

All outputs are saved in [out/](out/) and a small part of the output is listed
here. The input data used for this experiment is available at ["graphs"] (for
small ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Loading graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {}
# order: 5 size: 7 {} (loopDeadEnds)
# order: 5 size: 7 {} (transposeWithDegree)
# [00000.000 ms; 004 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.000 ms; 004 iters.] [0.0000e+00 err.] pagerankLevelwise
#
# Loading graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {}
# order: 8 size: 12 {} (loopDeadEnds)
# order: 8 size: 12 {} (transposeWithDegree)
# [00000.005 ms; 040 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.005 ms; 040 iters.] [8.5682e-07 err.] pagerankLevelwise
#
# Loading graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {}
# order: 21 size: 35 {} (loopDeadEnds)
# order: 21 size: 35 {} (transposeWithDegree)
# [00000.012 ms; 045 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.012 ms; 045 iters.] [8.4564e-07 err.] pagerankLevelwise
#
# Loading graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {}
# order: 6 size: 11 {} (loopDeadEnds)
# order: 6 size: 11 {} (transposeWithDegree)
# [00000.002 ms; 017 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.002 ms; 017 iters.] [4.8429e-07 err.] pagerankLevelwise
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (loopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00457.110 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00260.904 ms; 058 iters.] [4.3744e-06 err.] pagerankLevelwise
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 {}
# order: 685230 size: 7605339 {} (loopDeadEnds)
# order: 685230 size: 7605339 {} (transposeWithDegree)
# [00906.546 ms; 064 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00758.347 ms; 054 iters.] [4.3459e-06 err.] pagerankLevelwise
#
# Loading graph /home/subhajit/data/web-Google.mtx ...
# order: 916428 size: 5105039 {}
# order: 916428 size: 5282013 {} (loopDeadEnds)
# order: 916428 size: 5282013 {} (transposeWithDegree)
# [01445.656 ms; 062 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00786.115 ms; 063 iters.] [5.3568e-06 err.] pagerankLevelwise
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

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
