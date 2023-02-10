Analysing the effect of using **different values of tolerance**
on small graphs, with **Levelwise PageRank** ([pull], [CSR]).

This experiment compared the performance between:
1. Find pagerank using **L1 norm** for convergence check.
2. Find pagerank using **L2 norm** for convergence check.
3. Find pagerank using **L∞ norm** for convergence check.

This experiment is performed on four sample graphs, *min-DeadEnd*,
*min-2SCC*, *min-4SCC*, and *min-NvgraphEx*. Since *Levelwise PageRank*
requires the *absence of dead ends* (teleport-based dead end handling
strategy does not work), before performing any PageRank computation,
**self-loops** are added to *dead ends*. **Monolithic PageRank** computation
is also performed, which is used for performance comparison and error
measurement. Once PageRank computation *converges*, the start vertex `i`,
the number of vertices `n`, the total number of vertices in the graph,
the tolerance `E`, and the number of iterations required `l` is logged.
Monolithic PageRank performs one PageRank computation on the entire
graph, and hence has only one such log line. However, Levelwise PageRank
performs PageRank compuations on *each SCC* of the graph separately in
*topological order*, and hence has multiple such log lines. The total
number of iterations taken for Levelwise PageRank is calculated as the
sum of *fractional iterations* proportional to the size of each component
`l*n/N`, while the total number of iterations taken for Monolithic
PageRank is simply the number of iterations taken for the single PageRank
computation on the entire graph `l`.

While it was expected that once early components (SCCs) converge, later
components would converge sooner, a *contradictory result* was observed for
all of the error measurement functions (atleast for the sample graphs
considered). The two possible reasons for this could either be the **poor**
**choice of initial ranks** for Levelwise PageRank, or the **transition matrix**
**being ill-conditioned** causing slow convergence. This might be mitigated
with a better choice of initial ranks, or with algorithms allowing for
faster convergence.

All *four* graphs used in this experiment are stored in the *MatrixMarket*
*(.mtx)* file format. The experiment is implemented in *C++*, and compiled
using *GCC 9* with *optimization level 3 (-O3)*. The *iterations* taken
with each test case is measured. `500` is the *maximum iterations* allowed.
Statistics of each test case is printed to *standard output (stdout)*, and
redirected to a *log file*, which is then processed with a *script* to
generate a *CSV file*, with each *row* representing the details of a *single*
*test case*.

All outputs are saved in [out](out/) and a small part of the output is listed
here. The input data used for this experiment is available at ["graphs"]. This
experiment was done with guidance from [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Loading graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {
#   1 -> 2 4 5
#   2 -> 3
#   3 ->
#   4 -> 5
#   5 -> 3
# }
# order: 5 size: 7 {
#   1 -> 2 4 5
#   2 -> 3
#   3 -> 3
#   4 -> 5
#   5 -> 3
# } (selfLoopDeadEnds)
# order: 5 size: 7 {
#   1 ->
#   2 -> 1
#   3 -> 2 3 5
#   4 -> 1
#   5 -> 1 4
# } (transposeWithDegree)
#
# ...
#
# pagerankMonolithicSeq: ks={ 1 2 3 4 5 }
# pagerankMonolithicSeqLoop: i=000 n=005 N=005 E=1.0000e-06 l=004
# [00000.004 ms; 004 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-06]
# pagerankLevelwiseSeq: ks={ 1 4 5 2 3 }
# pagerankMonolithicSeqLoop: i=000 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=001 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=002 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=003 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=004 n=001 N=005 E=2.0000e-07 l=082
# [00000.034 ms; 018 iters.] [1.0139e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-06]
# pagerankMonolithicSeq: ks={ 1 2 3 4 5 }
# pagerankMonolithicSeqLoop: i=000 n=005 N=005 E=1.0000e-06 l=004
# [00000.005 ms; 004 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-06]
# pagerankLevelwiseSeq: ks={ 1 4 5 2 3 }
# pagerankMonolithicSeqLoop: i=000 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=001 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=002 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=003 n=001 N=005 E=2.0000e-07 l=002
# pagerankMonolithicSeqLoop: i=004 n=001 N=005 E=2.0000e-07 l=082
# [00000.035 ms; 018 iters.] [1.0139e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-06]
# pagerankMonolithicSeq: ks={ 1 2 3 4 5 }
# pagerankMonolithicSeqLoop: i=000 n=005 N=005 E=1.0000e-06 l=004
# [00000.005 ms; 004 iters.] [0.0000e+00 err.] pageranMonolithicSeqLiNorm [tolerance=1e-06]
# pagerankLevelwiseSeq: ks={ 1 4 5 2 3 }
# pagerankMonolithicSeqLoop: i=000 n=001 N=005 E=1.0000e-06 l=002
# pagerankMonolithicSeqLoop: i=001 n=001 N=005 E=1.0000e-06 l=002
# pagerankMonolithicSeqLoop: i=002 n=001 N=005 E=1.0000e-06 l=002
# pagerankMonolithicSeqLoop: i=003 n=001 N=005 E=1.0000e-06 l=002
# pagerankMonolithicSeqLoop: i=004 n=001 N=005 E=1.0000e-06 l=072
# [00000.032 ms; 016 iters.] [5.1499e-06 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-06]
#
# ...
```

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs)
- [How to check for Page Rank convergence?][L∞ norm]
- [L0 Norm, L1 Norm, L2 Norm & L-Infinity Norm](https://montjoile.medium.com/l0-norm-l1-norm-l2-norm-l-infinity-norm-7a7d18a4f40c)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)

<br>
<br>

[![](https://i.imgur.com/BnCiig7.jpg)](https://www.youtube.com/watch?v=04Uv44DRJAU)

[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[tolerance function]: https://github.com/puzzlef/pagerank-adjust-tolerance-function
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
