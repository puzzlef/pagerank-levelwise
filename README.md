Comparing various strategies of **performing initialization of ranks**
for Levelwise PageRank ([pull], [CSR]).

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
# [00413.684 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeq
# [00411.674 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm
# [00276.888 ms; 053 iters.] [3.8999e-06 err.] pagerankLevelwiseSeqL1Norm [initialization=default]
# [00366.951 ms; 080 iters.] [4.7366e-06 err.] pagerankLevelwiseSeqL1Norm [initialization=component]
# [00327.648 ms; 064 iters.] [6.1831e-06 err.] pagerankLevelwiseSeqL1Norm [initialization=blockgraph]
# [03298.053 ms; 060 iters.] [5.2520e-06 err.] pagerankLevelwiseSeqL1Norm [initialization=remaining]
# [00290.005 ms; 044 iters.] [3.6049e-05 err.] pagerankMonolithicSeqL2Norm
# [00205.307 ms; 040 iters.] [5.7197e-05 err.] pagerankLevelwiseSeqL2Norm [initialization=default]
# [00292.671 ms; 067 iters.] [8.0376e-05 err.] pagerankLevelwiseSeqL2Norm [initialization=component]
# [00258.842 ms; 051 iters.] [8.2951e-05 err.] pagerankLevelwiseSeqL2Norm [initialization=blockgraph]
# [03219.876 ms; 046 iters.] [8.5727e-05 err.] pagerankLevelwiseSeqL2Norm [initialization=remaining]
# [00268.528 ms; 041 iters.] [6.1639e-05 err.] pageranMonolithicSeqLiNorm
# [00146.722 ms; 023 iters.] [2.6169e-02 err.] pageranLevelwiseSeqLiNorm [initialization=default]
# [00225.055 ms; 046 iters.] [1.3656e-01 err.] pageranLevelwiseSeqLiNorm [initialization=component]
# [00182.648 ms; 029 iters.] [1.2830e-01 err.] pageranLevelwiseSeqLiNorm [initialization=blockgraph]
# [03147.628 ms; 024 iters.] [8.3605e-02 err.] pageranLevelwiseSeqLiNorm [initialization=remaining]
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
[tolerance function]: https://github.com/puzzlef/pagerank
[nvGraph]: https://github.com/rapidsai/nvgraph
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
[gist]: https://gist.github.com/wolfram77/082de8ee8e60e3f4aa55d39a788d5399
[charts]: https://photos.app.goo.gl/stdoXDUhRcDvZqZb6
[sheets]: https://docs.google.com/spreadsheets/d/1V-tanVXCIBemrC0jRtech5nA4sYUviwvUFC4G16oFKM/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vR2A2aGvONm_i4p_pun7jlKb8H2fIcYpMuXgV7BhbNAUbEeiHlTxKFWMgkE6_2LCznleVEWsjdsEqfy/pubhtml
