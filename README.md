Comparing various **min. compute sizes** for topologically-ordered components
([componentwise]) PageRank ([pull], [CSR]).

`TODO!`

This experiment was for comparing performance between [componentwise] pagerank
with various **min. compute size**, ranging from `1` - `1E+7`. Here,
**min. compute size** is the minimum no. nodes of each pagerank compute using
standard algorithm ([monolithic]). Each **min. compute size** was attempted on
different types of graphs, running each size 5 times per graph to get a good
time measure. **Componentwise** pagerank is the [STIC-D algorithm], without
**ICD** optimizations (using single-thread). Although there is no clear
winner, it appears a **min. compute size** of `10` would be a good choice.
Note that *componentwise* approach does not make use of *SIMD instructions* which
are available on all modern hardware.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -std=c++17 -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 69532892 {} (selfLoopDeadEnds)
# order: 4847571 size: 69532892 {} (transposeWithDegree)
# [12962.080 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm
# [11354.885 ms; 047 iters.] [4.7413e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=1]
# [10767.653 ms; 048 iters.] [4.7330e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=5]
# [10908.700 ms; 048 iters.] [4.7744e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=10]
# [10771.453 ms; 049 iters.] [4.2481e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=50]
# [10696.650 ms; 049 iters.] [4.9025e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=100]
# [10748.728 ms; 050 iters.] [4.2373e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=500]
# [10811.415 ms; 050 iters.] [4.1973e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=1000]
# [11087.216 ms; 050 iters.] [4.1276e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=5000]
# [11022.650 ms; 051 iters.] [4.8086e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=10000]
# [11313.031 ms; 051 iters.] [4.4000e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=50000]
# [11395.394 ms; 051 iters.] [3.7668e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=100000]
# [12522.878 ms; 056 iters.] [4.2787e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=500000]
# [12644.565 ms; 056 iters.] [5.1053e-06 err.] pagerankComponentwiseSeqL1Norm [min-compute=1000000]
# [13193.104 ms; 058 iters.] [0.0000e+00 err.] pagerankComponentwiseSeqL1Norm [min-compute=5000000]
# [13166.581 ms; 058 iters.] [0.0000e+00 err.] pagerankComponentwiseSeqL1Norm [min-compute=10000000]
# [13188.021 ms; 058 iters.] [0.0000e+00 err.] pagerankComponentwiseSeqL1Norm [min-compute=50000000]
# [07181.352 ms; 031 iters.] [5.8270e-04 err.] pagerankMonolithicSeqL2Norm
# [05394.708 ms; 026 iters.] [6.5001e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=1]
# [05098.983 ms; 026 iters.] [7.6977e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=5]
# [05002.137 ms; 026 iters.] [6.4927e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=10]
# [04987.877 ms; 026 iters.] [7.6833e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=50]
# [04999.733 ms; 027 iters.] [6.4733e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=100]
# [05036.777 ms; 026 iters.] [6.4407e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=500]
# [05051.953 ms; 026 iters.] [6.4117e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=1000]
# [05153.592 ms; 026 iters.] [6.3410e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=5000]
# [05182.462 ms; 026 iters.] [6.3526e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=10000]
# [05130.106 ms; 025 iters.] [7.0284e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=50000]
# [05170.001 ms; 024 iters.] [7.2325e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=100000]
# [05329.245 ms; 024 iters.] [2.0932e-03 err.] pagerankComponentwiseSeqL2Norm [min-compute=500000]
# [05375.341 ms; 025 iters.] [1.7650e-03 err.] pagerankComponentwiseSeqL2Norm [min-compute=1000000]
# [07060.266 ms; 031 iters.] [5.8270e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=5000000]
# [07062.370 ms; 031 iters.] [5.8270e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=10000000]
# [07045.892 ms; 031 iters.] [5.8270e-04 err.] pagerankComponentwiseSeqL2Norm [min-compute=50000000]
# [06491.511 ms; 028 iters.] [1.0223e-03 err.] pagerankMonolithicSeqLiNorm
# [03411.284 ms; 012 iters.] [4.0536e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=1]
# [03382.860 ms; 012 iters.] [4.0314e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=5]
# [03392.604 ms; 012 iters.] [4.0151e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=10]
# [03391.786 ms; 012 iters.] [3.9896e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=50]
# [03406.461 ms; 012 iters.] [3.9304e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=100]
# [03417.452 ms; 013 iters.] [3.8109e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=500]
# [03435.928 ms; 013 iters.] [3.7051e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=1000]
# [03467.708 ms; 013 iters.] [3.0511e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=5000]
# [03486.001 ms; 013 iters.] [2.6698e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=10000]
# [03946.612 ms; 015 iters.] [1.3742e-01 err.] pagerankComponentwiseSeqLiNorm [min-compute=50000]
# [03979.955 ms; 016 iters.] [2.4241e-02 err.] pagerankComponentwiseSeqLiNorm [min-compute=100000]
# [04034.822 ms; 017 iters.] [1.9150e-02 err.] pagerankComponentwiseSeqLiNorm [min-compute=500000]
# [04265.240 ms; 019 iters.] [4.1948e-03 err.] pagerankComponentwiseSeqLiNorm [min-compute=1000000]
# [06390.675 ms; 028 iters.] [1.0223e-03 err.] pagerankComponentwiseSeqLiNorm [min-compute=5000000]
# [06375.421 ms; 028 iters.] [1.0223e-03 err.] pagerankComponentwiseSeqLiNorm [min-compute=10000000]
# [06392.886 ms; 028 iters.] [1.0223e-03 err.] pagerankComponentwiseSeqLiNorm [min-compute=50000000]
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
[monolithic]: https://github.com/puzzlef/pagerank-monolithic-vs-componentwise
[componentwise]: https://github.com/puzzlef/pagerank-monolithic-vs-componentwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/KgBUFkTrHGB4WBfs9
[sheets]: https://docs.google.com/spreadsheets/d/10KhCjLln713-qWsQMURTQKmQsniTO0xwGzNeQkuV3sE/edit?usp=sharing
