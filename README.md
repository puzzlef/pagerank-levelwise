Comparing the effect of using different **functions** for
**convergence check**, with **Levelwise PageRank** ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find pagerank using **L1 norm** for convergence check.
2. Find pagerank using **L2 norm** for convergence check.
3. Find pagerank using **L∞ norm** for convergence check.

It is observed that a number of *error functions* are in use for checking
convergence of PageRank computation. Although [L1 norm] is commonly used
for convergence check, it appears [nvGraph] uses [L2 norm] instead. Another
person in stackoverflow seems to suggest the use of *per-vertex tolerance*
*comparison*, which is essentially the [L∞ norm]. The **L1 norm** `||E||₁`
between two *(rank) vectors* `r` and `s` is calculated as `Σ|rₙ - sₙ|`, or
as the *sum* of *absolute errors*. The **L2 norm** `||E||₂` is calculated
as `√Σ|rₙ - sₙ|2`, or as the *square-root* of the *sum* of *squared errors*
(*euclidean distance* between the two vectors). The **L∞ norm** `||E||ᵢ`
is calculated as `max(|rₙ - sₙ|)`, or as the *maximum* of *absolute errors*.

This experiment was for comparing the performance between PageRank computation
with *L1, L2* and *L∞ norms* as convergence check, for *damping factor
`α = 0.85`, and *tolerance* `τ = 10⁻⁶`. Since *Levelwise PageRank*
requires the *absence of dead ends* (teleport-based dead end handling
strategy does not work), before performing any PageRank computation,
**self-loops** are added to *dead ends*. **Monolithic PageRank** computation
is also performed, which is used for performance comparison and error
measurement.

All *seventeen* graphs used in this experiment are stored in the
*MatrixMarket (.mtx)* file format, and obtained from the *SuiteSparse*
*Matrix Collection*. These include: *web-Stanford, web-BerkStan,*
*web-Google, web-NotreDame, soc-Slashdot0811, soc-Slashdot0902,*
*soc-Epinions1, coAuthorsDBLP, coAuthorsCiteseer, soc-LiveJournal1,*
*coPapersCiteseer, coPapersDBLP, indochina-2004, italy_osm,*
*great-britain_osm, germany_osm, asia_osm*. The experiment is implemented
in *C++*, and compiled using *GCC 9* with *optimization level 3 (-O3)*.
The execution time of each test case is measured using
*std::chrono::high_performance_timer*. This is done *5 times* for each
test case, and timings are *averaged (AM)*. The *iterations* taken with
each test case is also measured. `500` is the *maximum iterations* allowed.
Statistics of each test case is printed to *standard output (stdout)*, and
redirected to a *log file*, which is then processed with a *script* to
generate a *CSV file*, with each *row* representing the details of a
*single test case*. This *CSV file* is imported into *Google Sheets*,
and necessary tables are set up with the help of the *FILTER* function
to create the *charts*.

From the results it is clear that PageRank computation with **L∞ norm**
**as convergence check is the fastest** , quickly followed by *L2 norm*,
and finally *L1 norm*. Thus, when comparing two or more approaches for an
iterative algorithm, it is important to ensure that all of them use the same
error function as convergence check (and the same parameter values). This
would help ensure a level ground for a good relative performance comparison.
It is also observed that *Levelwise PageRank* comverges faster than
*Monolithic PageRank* in most cases.

Also note in below charts that PageRank computation with **L∞ norm** as
convergence check **completes in a single iteration for all the road**
**networks** *(ending with _osm)*. This is likely because it is calculated
as `||E||ᵢ = max(|rₙ - sₙ|)`, and depending upon the *order (number of*
*vertices)* `N` of the graph (those graphs are quite large), the maximum
rank change for any single vertex does not exceed the *tolerance* `τ`
value of `10⁻⁶`.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /kaggle/input/graphs/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (selfLoopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00464.522 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm
# [00334.191 ms; 061 iters.] [0.0000e+00 err.] pagerankLevelwiseSeqL1Norm
# [00318.081 ms; 044 iters.] [3.6049e-05 err.] pagerankMonolithicSeqL2Norm
# [00252.807 ms; 047 iters.] [9.3213e-05 err.] pagerankLevelwiseSeqL2Norm
# [00299.334 ms; 041 iters.] [6.1639e-05 err.] pagerankMonolithicSeqLiNorm
# [00154.913 ms; 023 iters.] [8.8077e-02 err.] pagerankLevelwiseSeqLiNorm
#
# ...
#
# Loading graph /kaggle/input/graphs/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 69532892 {} (selfLoopDeadEnds)
# order: 4847571 size: 69532892 {} (transposeWithDegree)
# [16359.787 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm
# [13256.489 ms; 047 iters.] [0.0000e+00 err.] pagerankLevelwiseSeqL1Norm
# [08485.205 ms; 031 iters.] [5.8270e-04 err.] pagerankMonolithicSeqL2Norm
# [06404.363 ms; 026 iters.] [7.7020e-04 err.] pagerankLevelwiseSeqL2Norm
# [07606.579 ms; 028 iters.] [1.0223e-03 err.] pagerankMonolithicSeqLiNorm
# [04042.529 ms; 012 iters.] [2.9828e-01 err.] pagerankLevelwiseSeqLiNorm
#
# ...
```

[![](https://i.imgur.com/yArpSFJ.png)][sheetp]
[![](https://i.imgur.com/eGYTtoA.png)][sheetp]
[![](https://i.imgur.com/tIXHciJ.png)][sheetp]
[![](https://i.imgur.com/05p0Vj7.png)][sheetp]

[![](https://i.imgur.com/3zmoua6.png)][sheetp]
[![](https://i.imgur.com/24N5TaZ.png)][sheetp]
[![](https://i.imgur.com/tlKUkCv.png)][sheetp]
[![](https://i.imgur.com/A6QN9sN.png)][sheetp]

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs)
- [RAPIDS nvGraph NVIDIA graph library][nvGraph]
- [How to check for Page Rank convergence?][L∞ norm]
- [L0 Norm, L1 Norm, L2 Norm & L-Infinity Norm](https://montjoile.medium.com/l0-norm-l1-norm-l2-norm-l-infinity-norm-7a7d18a4f40c)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [Weighted Geometric Mean Selected for SPECviewperf® Composite Numbers](https://www.spec.org/gwpg/gpc.static/geometric.html)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/BnCiig7.jpg)](https://www.youtube.com/watch?v=04Uv44DRJAU)

[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[nvGraph]: https://github.com/rapidsai/nvgraph
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
[charts]: https://photos.app.goo.gl/oVojYnFDJ6TwXftq5
[sheets]: https://docs.google.com/spreadsheets/d/1JSmTIvhGadE4NAHQtLkwzDhJIhGkvlFKyRMr8uua8lo/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vTkVlY-Ur_q_wM6bgxXIxv9Vf_IGW4PJ8eIOYf0lCgDSwo71eXhkyi4LlokdUd81m10TWu8vDwd8lYj/pubhtml
