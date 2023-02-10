Comparing the effect of using **different values of tolerance**,
with Levelwise PageRank ([pull], [CSR]).

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
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (selfLoopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00388.488 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeq
# [00006.691 ms; 001 iters.] [6.1000e-01 err.] pagerankMonolithicSeqL1Norm [tolerance=1e+00]
# [00005.774 ms; 001 iters.] [8.6828e-01 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e+00]
# [00006.808 ms; 001 iters.] [6.1000e-01 err.] pagerankMonolithicSeqL2Norm [tolerance=1e+00]
# [00005.636 ms; 001 iters.] [7.0167e-01 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e+00]
# [00006.748 ms; 001 iters.] [6.1000e-01 err.] pageranMonolithicSeqLiNorm [tolerance=1e+00]
# [00005.463 ms; 001 iters.] [8.6546e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=1e+00]
# [00012.970 ms; 002 iters.] [3.3337e-01 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-01]
# [00013.048 ms; 002 iters.] [3.6543e-01 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-01]
# [00006.806 ms; 001 iters.] [6.1000e-01 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-01]
# [00006.016 ms; 001 iters.] [6.6025e-01 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-01]
# [00006.745 ms; 001 iters.] [6.1000e-01 err.] pageranMonolithicSeqLiNorm [tolerance=5e-01]
# [00005.475 ms; 001 iters.] [8.6546e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-01]
# [00031.315 ms; 005 iters.] [9.4875e-02 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-01]
# [00021.729 ms; 004 iters.] [4.4188e-01 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-01]
# [00006.806 ms; 001 iters.] [6.1000e-01 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-01]
# [00006.725 ms; 001 iters.] [8.2704e-01 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-01]
# [00006.754 ms; 001 iters.] [6.1000e-01 err.] pageranMonolithicSeqLiNorm [tolerance=1e-01]
# [00005.475 ms; 001 iters.] [8.6546e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-01]
# [00037.484 ms; 006 iters.] [7.0229e-02 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-02]
# [00037.217 ms; 007 iters.] [2.3080e-01 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-02]
# [00006.805 ms; 001 iters.] [6.1000e-01 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-02]
# [00007.007 ms; 001 iters.] [7.2026e-01 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-02]
# [00006.741 ms; 001 iters.] [6.1000e-01 err.] pageranMonolithicSeqLiNorm [tolerance=5e-02]
# [00005.473 ms; 001 iters.] [8.6546e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-02]
# [00074.352 ms; 012 iters.] [1.6266e-02 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-02]
# [00072.409 ms; 014 iters.] [4.2948e-02 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-02]
# [00019.222 ms; 003 iters.] [1.9998e-01 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-02]
# [00010.012 ms; 002 iters.] [7.5028e-01 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-02]
# [00019.088 ms; 003 iters.] [1.9998e-01 err.] pageranMonolithicSeqLiNorm [tolerance=1e-02]
# [00005.470 ms; 001 iters.] [8.6546e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-02]
# [00092.835 ms; 015 iters.] [8.6019e-03 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-03]
# [00085.837 ms; 018 iters.] [2.5114e-02 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-03]
# [00025.415 ms; 004 iters.] [1.3297e-01 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-03]
# [00013.028 ms; 004 iters.] [5.9235e-01 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-03]
# [00019.073 ms; 003 iters.] [1.9998e-01 err.] pageranMonolithicSeqLiNorm [tolerance=5e-03]
# [00008.676 ms; 001 iters.] [6.9049e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-03]
# [00141.994 ms; 023 iters.] [1.7542e-03 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-03]
# [00097.922 ms; 021 iters.] [3.5400e-03 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-03]
# [00044.046 ms; 007 iters.] [5.3060e-02 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-03]
# [00059.675 ms; 013 iters.] [8.9478e-02 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-03]
# [00037.558 ms; 006 iters.] [7.0229e-02 err.] pageranMonolithicSeqLiNorm [tolerance=1e-03]
# [00018.369 ms; 003 iters.] [5.6610e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-03]
# [00166.539 ms; 027 iters.] [8.2089e-04 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-04]
# [00111.132 ms; 024 iters.] [1.8732e-03 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-04]
# [00056.469 ms; 009 iters.] [3.2178e-02 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-04]
# [00051.986 ms; 013 iters.] [3.0824e-02 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-04]
# [00037.547 ms; 006 iters.] [7.0229e-02 err.] pageranMonolithicSeqLiNorm [tolerance=5e-04]
# [00037.765 ms; 006 iters.] [4.0643e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-04]
# [00221.884 ms; 036 iters.] [1.5467e-04 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-04]
# [00146.681 ms; 032 iters.] [3.5924e-04 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-04]
# [00106.124 ms; 017 iters.] [5.7098e-03 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-04]
# [00083.469 ms; 020 iters.] [7.2078e-03 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-04]
# [00080.657 ms; 013 iters.] [1.3102e-02 err.] pageranMonolithicSeqLiNorm [tolerance=1e-04]
# [00066.776 ms; 011 iters.] [4.2862e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-04]
# [00246.484 ms; 040 iters.] [7.4641e-05 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-05]
# [00191.635 ms; 040 iters.] [2.3539e-04 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-05]
# [00130.920 ms; 021 iters.] [2.5811e-03 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-05]
# [00096.412 ms; 022 iters.] [2.8759e-03 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-05]
# [00105.244 ms; 017 iters.] [5.7098e-03 err.] pageranMonolithicSeqLiNorm [tolerance=5e-05]
# [00079.937 ms; 013 iters.] [3.8228e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-05]
# [00301.772 ms; 049 iters.] [1.3693e-05 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-05]
# [00201.684 ms; 043 iters.] [3.3711e-05 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-05]
# [00186.689 ms; 030 iters.] [4.6867e-04 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-05]
# [00132.791 ms; 030 iters.] [6.7984e-04 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-05]
# [00166.707 ms; 027 iters.] [8.2089e-04 err.] pageranMonolithicSeqLiNorm [tolerance=1e-05]
# [00113.338 ms; 019 iters.] [3.6970e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-05]
# [00326.413 ms; 053 iters.] [6.0694e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-06]
# [00248.465 ms; 052 iters.] [2.2007e-05 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-06]
# [00211.465 ms; 034 iters.] [2.2333e-04 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-06]
# [00150.139 ms; 034 iters.] [3.3333e-04 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-06]
# [00191.419 ms; 031 iters.] [3.8856e-04 err.] pageranMonolithicSeqLiNorm [tolerance=5e-06]
# [00127.976 ms; 022 iters.] [3.6415e-01 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-06]
# [00386.756 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-06]
# [00284.290 ms; 061 iters.] [5.3406e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-06]
# [00273.416 ms; 044 iters.] [3.6049e-05 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-06]
# [00218.376 ms; 047 iters.] [9.3213e-05 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-06]
# [00252.847 ms; 041 iters.] [6.1639e-05 err.] pageranMonolithicSeqLiNorm [tolerance=1e-06]
# [00132.043 ms; 023 iters.] [8.8077e-02 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-06]
# [00413.442 ms; 067 iters.] [6.4162e-07 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-07]
# [00272.120 ms; 060 iters.] [2.6354e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-07]
# [00298.292 ms; 048 iters.] [1.7268e-05 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-07]
# [00204.327 ms; 046 iters.] [2.6889e-05 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-07]
# [00277.447 ms; 045 iters.] [2.9376e-05 err.] pageranMonolithicSeqLiNorm [tolerance=5e-07]
# [00178.528 ms; 032 iters.] [5.2598e-02 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-07]
# [00479.512 ms; 078 iters.] [1.2432e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-07]
# [00323.831 ms; 077 iters.] [1.4276e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-07]
# [00359.862 ms; 058 iters.] [2.4392e-06 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-07]
# [00247.956 ms; 057 iters.] [7.0967e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-07]
# [00339.033 ms; 055 iters.] [3.8894e-06 err.] pageranMonolithicSeqLiNorm [tolerance=1e-07]
# [00216.148 ms; 040 iters.] [1.0915e-02 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-07]
# [00522.964 ms; 085 iters.] [1.2167e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-08]
# [00352.656 ms; 084 iters.] [1.3502e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-08]
# [00385.089 ms; 062 iters.] [9.2549e-07 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-08]
# [00261.312 ms; 059 iters.] [3.8554e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-08]
# [00363.476 ms; 059 iters.] [1.2893e-06 err.] pageranMonolithicSeqLiNorm [tolerance=5e-08]
# [00229.950 ms; 042 iters.] [5.6478e-03 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-08]
# [03065.986 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-08]
# [01700.858 ms; 319 iters.] [1.3266e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-08]
# [00447.144 ms; 072 iters.] [1.1689e-06 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-08]
# [00319.837 ms; 080 iters.] [1.4299e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-08]
# [00425.001 ms; 069 iters.] [8.2751e-07 err.] pageranMonolithicSeqLiNorm [tolerance=1e-08]
# [00267.066 ms; 051 iters.] [1.1155e-03 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-08]
# [03145.252 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-09]
# [01748.802 ms; 318 iters.] [1.3253e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-09]
# [00526.746 ms; 083 iters.] [1.2104e-06 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-09]
# [00365.020 ms; 090 iters.] [1.6163e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-09]
# [00453.539 ms; 073 iters.] [1.0541e-06 err.] pageranMonolithicSeqLiNorm [tolerance=5e-09]
# [00254.022 ms; 049 iters.] [6.3086e-04 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-09]
# [03203.849 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-09]
# [00459.518 ms; 115 iters.] [1.4103e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-09]
# [03204.235 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-09]
# [00418.632 ms; 107 iters.] [1.4169e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-09]
# [03229.316 ms; 500 iters.] [1.2685e-06 err.] pageranMonolithicSeqLiNorm [tolerance=1e-09]
# [01656.181 ms; 283 iters.] [1.0254e-04 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-09]
# [03154.003 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=5e-10]
# [00464.267 ms; 119 iters.] [1.4085e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=5e-10]
# [03160.504 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL2Norm [tolerance=5e-10]
# [00430.654 ms; 111 iters.] [1.4086e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=5e-10]
# [03245.446 ms; 500 iters.] [1.2685e-06 err.] pageranMonolithicSeqLiNorm [tolerance=5e-10]
# [01646.191 ms; 284 iters.] [5.2529e-05 err.] pageranLevelwiseSeqLiNorm [tolerance=5e-10]
# [03108.953 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL1Norm [tolerance=1e-10]
# [00497.461 ms; 126 iters.] [1.4079e-06 err.] pagerankLevelwiseSeqL1Norm [tolerance=1e-10]
# [03135.324 ms; 500 iters.] [1.2685e-06 err.] pagerankMonolithicSeqL2Norm [tolerance=1e-10]
# [00469.710 ms; 120 iters.] [1.4084e-06 err.] pagerankLevelwiseSeqL2Norm [tolerance=1e-10]
# [03103.441 ms; 500 iters.] [1.2685e-06 err.] pageranMonolithicSeqLiNorm [tolerance=1e-10]
# [01656.675 ms; 289 iters.] [1.2712e-05 err.] pageranLevelwiseSeqLiNorm [tolerance=1e-10]
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
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[tolerance function]: https://github.com/puzzlef/pagerank-adjust-tolerance-function
[nvGraph]: https://github.com/rapidsai/nvgraph
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
[charts]: https://photos.app.goo.gl/stdoXDUhRcDvZqZb6
[sheets]: https://docs.google.com/spreadsheets/d/1V-tanVXCIBemrC0jRtech5nA4sYUviwvUFC4G16oFKM/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vR2A2aGvONm_i4p_pun7jlKb8H2fIcYpMuXgV7BhbNAUbEeiHlTxKFWMgkE6_2LCznleVEWsjdsEqfy/pubhtml
