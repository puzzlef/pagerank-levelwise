Performance of standard (**monolithic**) vs topologically-ordered components
(**levelwise**) PageRank ([pull], [CSR], [skip-teleport], [compute-10]).

This experiment was for comparing performance between:
1. Find pagerank with standard algorithm (**monolithic**).
2. Find pagerank in topologically-ordered components fashion (**levelwise**).

Both approaches were attempted on different types of graphs, running each
approach 5 times per graph to get a good time measure. **Levelwise** pagerank
is the [STIC-D algorithm], without **ICD** optimizations (using single-thread).
On average, **levelwise** pagerank is **faster** than the *monolithic* approach.
Note that neither approach makes use of *SIMD instructions* which are available
on all modern hardware.

All outputs are saved in [gist] and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. For previous experiments, see [branches].
This experiment was done with guidance from [Prof. Dip Sankar Banerjee] and
[Prof. Kishore Kothapalli].

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

[![](https://i.imgur.com/TqrzS48.gif)][sheets]
[![](https://i.imgur.com/bROelWZ.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/ewKOeWS.jpg)](https://www.youtube.com/watch?v=eBW0s125f-Y)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[skip-teleport]: https://github.com/puzzlef/pagerank-levelwise
[compute-10]: https://github.com/puzzlef/pagerank-levelwise
[branches]: https://github.com/puzzlef/pagerank-levelwise/branches
[gist]: https://gist.github.com/wolfram77/ab9ab9db11f9ebe28310efe06131fbd1
[charts]: https://photos.app.goo.gl/9wFk82NncJ7gUhxC9
[sheets]: https://docs.google.com/spreadsheets/d/1qVLU0PTUl-PglezkSmPe7PwQHOvCgBGTSTclfg71B5Q/edit?usp=sharing
