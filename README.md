Comparing various min. component sizes for topologically-ordered components
(levelwise) PageRank ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find **levelwise** pagerank using **min. component size** from `1` - `1E+7`.

Each **min. component size** was attempted on different types of graphs,
running each size 5 times per graph to get a good time measure. **Levelwise**
pagerank is the [STIC-D algorithm], without **ICD** optimizations (using
single-thread). Although there is no clear winner, it appears a
**min. component size** of `50` would be a good choice.

All outputs are saved in [out/](out/) and a small part of the output is listed
here. All [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection].

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
# [00000.002 ms; 018 iters.] [1.1921e-06 err.] pagerankLevelwise [1e+00 min-component-size]
#
# Loading graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {}
# order: 8 size: 12 {} (loopDeadEnds)
# order: 8 size: 12 {} (transposeWithDegree)
# [00000.003 ms; 040 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.005 ms; 047 iters.] [2.6524e-06 err.] pagerankLevelwise [1e+00 min-component-size]
# [00000.003 ms; 040 iters.] [8.5682e-07 err.] pagerankLevelwise [5e+00 min-component-size]
#
# Loading graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {}
# order: 21 size: 35 {} (loopDeadEnds)
# order: 21 size: 35 {} (transposeWithDegree)
# [00000.009 ms; 045 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.013 ms; 053 iters.] [2.7735e-06 err.] pagerankLevelwise [1e+00 min-component-size]
# [00000.012 ms; 058 iters.] [4.0643e-06 err.] pagerankLevelwise [5e+00 min-component-size]
# [00000.010 ms; 051 iters.] [2.7083e-06 err.] pagerankLevelwise [1e+01 min-component-size]
#
# Loading graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {}
# order: 6 size: 11 {} (loopDeadEnds)
# order: 6 size: 11 {} (transposeWithDegree)
# [00000.000 ms; 017 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00000.002 ms; 049 iters.] [3.0585e-06 err.] pagerankLevelwise [1e+00 min-component-size]
# [00000.001 ms; 027 iters.] [1.4976e-06 err.] pagerankLevelwise [5e+00 min-component-size]
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (loopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00738.952 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00528.433 ms; 061 iters.] [5.8785e-06 err.] pagerankLevelwise [1e+00 min-component-size]
# [00458.537 ms; 056 iters.] [4.6830e-06 err.] pagerankLevelwise [5e+00 min-component-size]
# [00470.989 ms; 056 iters.] [4.7403e-06 err.] pagerankLevelwise [1e+01 min-component-size]
# [00487.671 ms; 058 iters.] [4.3744e-06 err.] pagerankLevelwise [5e+01 min-component-size]
# [00540.446 ms; 065 iters.] [6.0055e-06 err.] pagerankLevelwise [1e+02 min-component-size]
# [00470.985 ms; 061 iters.] [4.8291e-06 err.] pagerankLevelwise [5e+02 min-component-size]
# [00534.583 ms; 067 iters.] [5.3440e-06 err.] pagerankLevelwise [1e+03 min-component-size]
# [00506.471 ms; 069 iters.] [5.2159e-06 err.] pagerankLevelwise [5e+03 min-component-size]
# [00359.162 ms; 069 iters.] [4.8319e-06 err.] pagerankLevelwise [1e+04 min-component-size]
# [00323.512 ms; 068 iters.] [4.4184e-06 err.] pagerankLevelwise [5e+04 min-component-size]
# [00297.972 ms; 064 iters.] [2.4454e-06 err.] pagerankLevelwise [1e+05 min-component-size]
# ...
```

<br>

[![](https://i.imgur.com/awWEd8m.png)][sheets]
[![](https://i.imgur.com/I0tdoJv.png)][sheets]
[![](https://i.imgur.com/GcUmIGy.png)][sheets]
[![](https://i.imgur.com/wHMdTfB.png)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/1VFZdqh.jpg)](https://www.youtube.com/watch?v=vbXTZlJ5fHU)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[charts]: https://photos.app.goo.gl/KveUUSpamrPKPmvY6
[sheets]: https://docs.google.com/spreadsheets/d/1cdH3LURJo4KfflTF0grHtICUsaEmDHxKGy4Vti4eZc8/edit?usp=sharing
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
