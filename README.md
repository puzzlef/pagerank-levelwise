Comparing various **min. compute sizes** for topologically-ordered components
([levelwise]) PageRank ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between [levelwise] pagerank
with various **min. compute size**, ranging from `1` - `1E+7`. Here,
**min. compute size** is the minimum no. nodes of each pagerank compute using
standard algorithm ([monolithic]). Each **min. compute size** was attempted on
different types of graphs, running each size 5 times per graph to get a good
time measure. **Levelwise** pagerank is the [STIC-D algorithm], without
**ICD** optimizations (using single-thread). Although there is no clear
winner, it appears a **min. compute size** of `10` would be a good choice.
Note that *levelwise* approach does not make use of *SIMD instructions* which
are available on all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 69532892 {} (selfLoopDeadEnds)
# order: 4847571 size: 69532892 {} (transposeWithDegree)
# [16988.721 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithicSeq
# [15675.792 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm
# [11350.305 ms; 047 iters.] [4.0676e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+00]
# [20016.074 ms; 062 iters.] [7.0796e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=5e+00]
# [13340.599 ms; 049 iters.] [4.1088e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+01]
# [11769.303 ms; 051 iters.] [4.3096e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=5e+01]
# [11654.890 ms; 051 iters.] [4.3460e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+02]
# [11445.128 ms; 051 iters.] [5.0098e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=5e+02]
# [11232.422 ms; 052 iters.] [4.3319e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+03]
# [11798.237 ms; 052 iters.] [4.9639e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=5e+03]
# [11004.436 ms; 052 iters.] [5.0014e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+04]
# [16143.310 ms; 065 iters.] [7.9891e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=5e+04]
# [15877.591 ms; 066 iters.] [8.0451e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+05]
# [12904.661 ms; 056 iters.] [4.2787e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=5e+05]
# [13170.025 ms; 056 iters.] [5.1053e-06 err.] pagerankLevelwiseSeqL1Norm [min-compute-size=1e+06]
# [08036.637 ms; 031 iters.] [5.8270e-04 err.] pagerankMonolithicSeqL2Norm
# [05435.565 ms; 026 iters.] [7.7020e-04 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+00]
# [07069.839 ms; 034 iters.] [2.7029e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=5e+00]
# [05579.577 ms; 027 iters.] [6.4905e-04 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+01]
# [07599.213 ms; 035 iters.] [3.1922e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=5e+01]
# [07818.099 ms; 035 iters.] [3.1938e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+02]
# [05543.575 ms; 028 iters.] [6.4413e-04 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=5e+02]
# [05479.441 ms; 027 iters.] [7.6150e-04 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+03]
# [08112.955 ms; 034 iters.] [3.2283e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=5e+03]
# [05767.833 ms; 026 iters.] [6.4266e-04 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+04]
# [05946.888 ms; 025 iters.] [7.2743e-04 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=5e+04]
# [07430.806 ms; 032 iters.] [3.3501e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+05]
# [05794.045 ms; 024 iters.] [2.0932e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=5e+05]
# [05623.636 ms; 025 iters.] [1.7650e-03 err.] pagerankLevelwiseSeqL2Norm [min-compute-size=1e+06]
# [07580.298 ms; 028 iters.] [1.0223e-03 err.] pagerankMonolithicSeqLiNorm
# [03633.120 ms; 012 iters.] [2.9828e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+00]
# [04951.259 ms; 016 iters.] [2.8539e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=5e+00]
# [05036.243 ms; 016 iters.] [2.8399e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+01]
# [03929.513 ms; 012 iters.] [2.6856e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=5e+01]
# [03805.548 ms; 012 iters.] [2.6462e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+02]
# [03709.831 ms; 013 iters.] [2.6963e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=5e+02]
# [03692.420 ms; 013 iters.] [2.5894e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+03]
# [04758.245 ms; 016 iters.] [1.9258e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=5e+03]
# [04100.179 ms; 013 iters.] [1.9633e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+04]
# [05605.095 ms; 015 iters.] [1.5618e-01 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=5e+04]
# [05550.661 ms; 017 iters.] [8.4116e-02 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+05]
# [05377.503 ms; 017 iters.] [1.9150e-02 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=5e+05]
# [05580.688 ms; 019 iters.] [4.1948e-03 err.] pagerankLevelwiseSeqLiNorm [min-compute-size=1e+06]
#
# ...
```

[![](https://i.imgur.com/d7a2KUv.png)][sheets]
[![](https://i.imgur.com/N5GTokT.png)][sheets]
[![](https://i.imgur.com/a02NaHs.png)][sheets]
[![](https://i.imgur.com/6BqYmGp.png)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/5gcO8cg.jpg)](https://www.youtube.com/watch?v=4Xw0MrllRfQ)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[monolithic]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/KgBUFkTrHGB4WBfs9
[sheets]: https://docs.google.com/spreadsheets/d/10KhCjLln713-qWsQMURTQKmQsniTO0xwGzNeQkuV3sE/edit?usp=sharing
