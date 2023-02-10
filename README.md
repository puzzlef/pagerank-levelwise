Finding suitable number of *monolithic PageRank iterations* for
**initialization of ranks** with Levelwise PageRank ([pull], [CSR]).

`TODO!`

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

Similar to the *damping factor* `α` and the *error function* used for
convergence check, **adjusting the value of tolerance** `τ` can have a
significant effect. This experiment was for comparing the performance
between PageRank computation with *L1, L2* and *L∞ norms* as convergence
check, for various *tolerance* `τ` values ranging from `10⁻⁰` to `10⁻¹⁰`
(`10⁻⁰`, `5×10⁻⁰`, `10⁻¹`, `5×10⁻¹`, ...). The PageRank algorithm used
here is the *standard power-iteration (pull)* based PageRank. The rank
of a vertex in an iteration is calculated as `c₀ + αΣrₙ/dₙ`, where `c₀`
is the *common teleport contribution*, `α` is the *damping factor*, `rₙ`
is the *previous rank of vertex* with an incoming edge, `dₙ` is the
*out-degree* of the incoming-edge vertex, and `N` is the *total number*
*of vertices* in the graph. The *common teleport contribution* `c₀`,
calculated as `(1-α)/N + αΣrₙ/N` , includes the *contribution due to a*
*teleport from any vertex* in the graph due to the damping factor `(1-α)/N`,
and *teleport from dangling vertices* (with *no outgoing edges*) in the
graph `αΣrₙ/N`. This is because a random surfer jumps to a random page
upon visiting a page with *no links*, in order to avoid the *rank-sink*
effect.

All *seventeen* graphs used in this experiment are stored in the
*MatrixMarket (.mtx)* file format, and obtained from the *SuiteSparse*
*Matrix Collection*. These include: *web-Stanford, web-BerkStan,*
*web-Google, web-NotreDame, soc-Slashdot0811, soc-Slashdot0902,*
*soc-Epinions1, coAuthorsDBLP, coAuthorsCiteseer, soc-LiveJournal1,*
*coPapersCiteseer, coPapersDBLP, indochina-2004, italy_osm,*
*great-britain_osm, germany_osm, asia_osm*. The experiment is implemented
in *C++*, and compiled using *GCC 9* with *optimization level 3 (-O3)*.
The system used is a *Dell PowerEdge R740 Rack server* with two *Intel*
*Xeon Silver 4116 CPUs @ 2.10GHz*, *128GB DIMM DDR4 Synchronous Registered*
*(Buffered) 2666 MHz (8x16GB) DRAM*, and running *CentOS Linux release*
*7.9.2009 (Core)*. The *iterations* taken with each test case is measured.
`500` is the *maximum iterations* allowed. Statistics of each test case is
printed to *standard output (stdout)*, and redirected to a *log file*,
which is then processed with a *script* to generate a *CSV file*, with
each *row* representing the details of a *single test case*. This
*CSV file* is imported into *Google Sheets*, and necessary tables are set
up with the help of the *FILTER* function to create the *charts*.

For various graphs it is observed that PageRank computation with *L1*, *L2*,
or *L∞ norm* as *convergence check* suffers from **sensitivity issues**
beyond certain (*smaller*) tolerance `τ` values, causing the computation to
halt at maximum iteration limit (`500`) without convergence. As *tolerance*
`τ` is decreased from `10⁻⁰` to `10⁻¹⁰`, *L1 norm* is the *first* to suffer
from this issue, followed by *L2 and L∞ norms (except road networks)*. This
*sensitivity issue* was recognized by the fact that a given approach *abruptly*
takes `500` *iterations* for the next lower *tolerance* `τ` value.

It is also observed that PageRank computation with *L∞ norm* as convergence
check **completes in just one iteration** (even for *tolerance* `τ ≥ 10⁻⁶`)
for large graphs *(road networks)*. This again, as mentioned above, is likely
because the maximum rank change for any single vertex for *L∞ norm*, and
the sum of squares of total rank change for all vertices, is quite low for
such large graphs. Thus, it does not exceed the given *tolerance* `τ` value,
causing a single iteration convergence.

On average, PageRank computation with **L∞ norm** as the error function is the
**fastest**, quickly **followed by** **L2 norm**, and **then** **L1 norm**. This
is the case with both geometric mean (GM) and arithmetic mean (AM) comparisons
of iterations needed for convergence with each of the three error functions. In
fact, this trend is observed with each of the individual graphs separately.

Based on **GM-RATIO** comparison, the *relative iterations* between
PageRank computation with *L1*, *L2*, and *L∞ norm* as convergence check
is `1.00 : 0.30 : 0.20`. Hence *L2 norm* is on *average* `70%` *faster*
than *L1 norm*, and *L∞ norm* is `33%` *faster* than *L2 norm*. This
ratio is calculated by first finding the *GM* of *iterations* based on
each *error function* for each *tolerance* `τ` value separately. These
*tolerance* `τ` specific means are then combined with *GM* to obtain a
*single mean value* for each *error function (norm)*. The *GM-RATIO* is
then the ratio of each *norm* with respect to the *L∞ norm*. The variation
of *tolerance* `τ` specific means with *L∞ norm* as baseline for various
*tolerance* `τ` values is shown below.

On the other hand, based on **AM-RATIO** comparison, the *relative*
*iterations* between PageRank computation with *L1*, *L2*, and *L∞ norm*
as convergence check is `1.00 : 0.39 : 0.31`. Hence, *L2 norm* is on
*average* `61%` *faster* than *L1 norm*, and *L∞ norm* is `26%` *faster*
than *L2 norm*. This ratio is calculated in a manner similar to that of
*GM-RATIO*, except that it uses *AM* instead of *GM*. The variation of
*tolerance* `τ` specific means with *L∞ norm* as baseline for various
*tolerance* `τ` values is shown below as well.

All outputs are saved in [gist] and a small part of the output is listed
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
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (selfLoopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00540.215 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeq
# [00538.620 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm
# [00289.609 ms; 052 iters.] [4.4304e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=0]
# [00284.295 ms; 052 iters.] [4.4497e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=1]
# [00268.095 ms; 049 iters.] [2.8786e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=2]
# [00264.854 ms; 048 iters.] [2.9050e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=3]
# [00263.948 ms; 048 iters.] [2.8805e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=4]
# [00268.391 ms; 049 iters.] [2.3808e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=5]
# [00264.188 ms; 048 iters.] [2.3984e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=6]
# [00268.317 ms; 049 iters.] [2.3902e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=7]
# [00268.685 ms; 049 iters.] [2.3746e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=8]
# [00269.036 ms; 049 iters.] [2.3668e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=9]
# [00272.779 ms; 049 iters.] [2.3604e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=10]
# [00277.215 ms; 049 iters.] [2.3416e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=11]
# [00276.213 ms; 049 iters.] [2.3367e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=12]
# [00272.570 ms; 049 iters.] [2.3216e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=13]
# [00276.524 ms; 049 iters.] [2.3022e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=14]
# [00272.267 ms; 049 iters.] [2.2968e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=15]
# [00277.507 ms; 049 iters.] [2.2735e-06 err.] pagerankLevelwiseSeqL1Norm [monolithic-iterations=16]
# [00373.508 ms; 044 iters.] [3.6202e-05 err.] pagerankMonolithicSeqL2Norm
# [00207.673 ms; 039 iters.] [4.9055e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=0]
# [00212.430 ms; 040 iters.] [5.7242e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=1]
# [00201.147 ms; 038 iters.] [3.3047e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=2]
# [00197.781 ms; 037 iters.] [3.4998e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=3]
# [00199.643 ms; 037 iters.] [2.9693e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=4]
# [00209.387 ms; 037 iters.] [2.9652e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=5]
# [00205.112 ms; 037 iters.] [2.9951e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=6]
# [00209.222 ms; 037 iters.] [2.9905e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=7]
# [00211.058 ms; 037 iters.] [2.9929e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=8]
# [00214.637 ms; 037 iters.] [3.0042e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=9]
# [00207.264 ms; 037 iters.] [3.0097e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=10]
# [00212.277 ms; 037 iters.] [3.0044e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=11]
# [00212.778 ms; 038 iters.] [3.0021e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=12]
# [00209.390 ms; 037 iters.] [2.9979e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=13]
# [00214.317 ms; 038 iters.] [2.9701e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=14]
# [00210.989 ms; 037 iters.] [2.9742e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=15]
# [00215.843 ms; 038 iters.] [2.9595e-05 err.] pagerankLevelwiseSeqL2Norm [monolithic-iterations=16]
# [00360.638 ms; 041 iters.] [6.1780e-05 err.] pageranMonolithicSeqLiNorm
# [00155.890 ms; 023 iters.] [2.6175e-02 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=0]
# [00161.998 ms; 024 iters.] [2.5837e-02 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=1]
# [00160.867 ms; 023 iters.] [2.6772e-02 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=2]
# [00158.194 ms; 023 iters.] [1.9849e-02 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=3]
# [00158.498 ms; 023 iters.] [1.4081e-02 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=4]
# [00160.059 ms; 023 iters.] [1.1122e-02 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=5]
# [00164.045 ms; 024 iters.] [8.4821e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=6]
# [00162.556 ms; 024 iters.] [7.0738e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=7]
# [00167.148 ms; 025 iters.] [5.7856e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=8]
# [00169.508 ms; 025 iters.] [4.9805e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=9]
# [00166.323 ms; 025 iters.] [4.0502e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=10]
# [00172.372 ms; 026 iters.] [3.5612e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=11]
# [00169.605 ms; 026 iters.] [2.9289e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=12]
# [00175.553 ms; 027 iters.] [2.5827e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=13]
# [00172.983 ms; 027 iters.] [2.1346e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=14]
# [00178.880 ms; 028 iters.] [1.8660e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=15]
# [00176.688 ms; 028 iters.] [1.5713e-03 err.] pageranLevelwiseSeqLiNorm [monolithic-iterations=16]
#
# ...
```

[![](https://i.imgur.com/4NbjAzk.png)][sheetp]
[![](https://i.imgur.com/taoe5p9.png)][sheetp]
[![](https://i.imgur.com/nZxC4H2.png)][sheetp]
[![](https://i.imgur.com/wr5ziJQ.png)][sheetp]

[![](https://i.imgur.com/oZtDiXX.png)][sheetp]
[![](https://i.imgur.com/8ugVRL6.png)][sheetp]
[![](https://i.imgur.com/xmQPqNU.png)][sheetp]
[![](https://i.imgur.com/XR7hHis.png)][sheetp]

[![](https://i.imgur.com/iiVc0mT.gif)][sheetp]
[![](https://i.imgur.com/TfdJbHX.gif)][sheetp]

<br>
<br>


## References

- [RAPIDS nvGraph NVIDIA graph library][nvGraph]
- [How to check for Page Rank convergence?][L∞ norm]
- [L0 Norm, L1 Norm, L2 Norm & L-Infinity Norm](https://montjoile.medium.com/l0-norm-l1-norm-l2-norm-l-infinity-norm-7a7d18a4f40c)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/p8R1WIk.jpg)](https://www.youtube.com/watch?v=04Uv44DRJAU)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[tolerance function]: https://github.com/puzzlef/pagerank-adjust-tolerance-function
[nvGraph]: https://github.com/rapidsai/nvgraph
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
[gist]: https://gist.github.com/wolfram77/ca43a0f0f1a6814d2cacdaa703e4c1da
[charts]: https://photos.app.goo.gl/stdoXDUhRcDvZqZb6
[sheets]: https://docs.google.com/spreadsheets/d/1V-tanVXCIBemrC0jRtech5nA4sYUviwvUFC4G16oFKM/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vR2A2aGvONm_i4p_pun7jlKb8H2fIcYpMuXgV7BhbNAUbEeiHlTxKFWMgkE6_2LCznleVEWsjdsEqfy/pubhtml
