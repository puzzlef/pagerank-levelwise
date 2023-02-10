Comparing the effect of using different values of **damping factor**,
with **Levelwise PageRank** ([pull], [CSR]).

Adjustment of the *damping factor α* is a delicate balancing act. For
smaller values of *α*, the convergence is fast, but the *link structure*
*of the graph* used to determine ranks is less true. Slightly different
values for *α* can produce *very different* rank vectors. Moreover, as
α → 1, convergence *slows down drastically*, and *sensitivity issues*
begin to surface.

For this experiment, the **damping factor** `α` (which is usually `0.85`)
is **varied** from `0.50` to `1.00` in steps of `0.05`. This is in order
to compare the performance variation with each *damping factor*. The
calculated error is the *L1 norm* with respect to default PageRank
(`α = 0.85`). Since *Levelwise PageRank* requires the *absence of dead ends*
(teleport-based dead end handling strategy does not work), before
performing any PageRank computation, **self-loops** are added to
*dead ends*. **Monolithic PageRank** computation is also performed, which
is used for performance comparison and error measurement.

All *seventeen* graphs used in this experiment are stored in the
*MatrixMarket (.mtx)* file format, and obtained from the *SuiteSparse*
*Matrix Collection*. These include: *web-Stanford, web-BerkStan,*
*web-Google, web-NotreDame, soc-Slashdot0811, soc-Slashdot0902,*
*soc-Epinions1, coAuthorsDBLP, coAuthorsCiteseer, soc-LiveJournal1,*
*coPapersCiteseer, coPapersDBLP, indochina-2004, italy_osm,*
*great-britain_osm, germany_osm, asia_osm*. The experiment is implemented
in *C++*, and compiled using *GCC 9* with *optimization level 3 (-O3)*.
The *iterations* taken with each test case is measured. `500` is the
*maximum iterations* allowed. Statistics of each test case is
printed to *standard output (stdout)*, and redirected to a *log file*,
which is then processed with a *script* to generate a *CSV file*, with
each *row* representing the details of a *single test case*. This
*CSV file* is imported into *Google Sheets*, and necessary tables are set
up with the help of the *FILTER* function to create the *charts*.

Results indicate that **increasing the damping factor α beyond** `0.85`
**significantly increases convergence time** , and lowering it below
`0.85` decreases convergence time. As the *damping factor* `α` increases
*linearly*, the iterations needed for PageRank computation *increases*
*almost exponentially*. On average, using a *damping factor* `α = 0.95`
increases *iterations* needed by `170-180%` (`2.7-2.8x`), and using a *damping*
*factor* `α = 0.75` *decreases* it by `40%` (`0.6x`), compared to
*damping factor* `α = 0.85`. Note that a higher *damping factor* implies
that a random surfer follows links with *higher probability* (and jumps
to a random page with lower probability).

All outputs are saved in [gist] and a small part of the output is listed
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
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312669 {} (selfLoopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00413.935 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithicSeq
# [03321.036 ms; 500 iters.] [1.1830e+00 err.] pagerankMonolithicSeq [damping=1.00]
# [01995.664 ms; 386 iters.] [8.6363e-01 err.] pagerankLevelwiseSeq [damping=1.00]
# [01256.598 ms; 192 iters.] [3.3431e-01 err.] pagerankMonolithicSeq [damping=0.95]
# [00761.530 ms; 160 iters.] [3.3431e-01 err.] pagerankLevelwiseSeq [damping=0.95]
# [00629.869 ms; 096 iters.] [1.3513e-01 err.] pagerankMonolithicSeq [damping=0.90]
# [00393.066 ms; 082 iters.] [1.3513e-01 err.] pagerankLevelwiseSeq [damping=0.90]
# [00409.312 ms; 063 iters.] [2.0306e-07 err.] pagerankMonolithicSeq [damping=0.85]
# [00264.667 ms; 055 iters.] [4.6983e-06 err.] pagerankLevelwiseSeq [damping=0.85]
# [00305.375 ms; 047 iters.] [1.0810e-01 err.] pagerankMonolithicSeq [damping=0.80]
# [00205.093 ms; 043 iters.] [1.0811e-01 err.] pagerankLevelwiseSeq [damping=0.80]
# [00239.792 ms; 037 iters.] [2.0043e-01 err.] pagerankMonolithicSeq [damping=0.75]
# [00162.889 ms; 033 iters.] [2.0043e-01 err.] pagerankLevelwiseSeq [damping=0.75]
# [00197.437 ms; 030 iters.] [2.8262e-01 err.] pagerankMonolithicSeq [damping=0.70]
# [00150.736 ms; 030 iters.] [2.8262e-01 err.] pagerankLevelwiseSeq [damping=0.70]
# [00162.177 ms; 025 iters.] [3.5705e-01 err.] pagerankMonolithicSeq [damping=0.65]
# [00129.267 ms; 026 iters.] [3.5705e-01 err.] pagerankLevelwiseSeq [damping=0.65]
# [00137.687 ms; 021 iters.] [4.2546e-01 err.] pagerankMonolithicSeq [damping=0.60]
# [00099.487 ms; 020 iters.] [4.2546e-01 err.] pagerankLevelwiseSeq [damping=0.60]
# [00122.985 ms; 018 iters.] [4.8941e-01 err.] pagerankMonolithicSeq [damping=0.55]
# [00088.685 ms; 017 iters.] [4.8941e-01 err.] pagerankLevelwiseSeq [damping=0.55]
# [00106.585 ms; 016 iters.] [5.5069e-01 err.] pagerankMonolithicSeq [damping=0.50]
# [00085.601 ms; 017 iters.] [5.5069e-01 err.] pagerankLevelwiseSeq [damping=0.50]
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 69532892 {} (selfLoopDeadEnds)
# order: 4847571 size: 69532892 {} (transposeWithDegree)
# [14849.229 ms; 058 iters.] [0.0000e+00 err.] pagerankMonolithicSeq
# [132531.172 ms; 500 iters.] [1.5027e+00 err.] pagerankMonolithicSeq [damping=1.00]
# [124651.750 ms; 441 iters.] [9.5421e-01 err.] pagerankLevelwiseSeq [damping=1.00]
# [37465.320 ms; 151 iters.] [3.4072e-01 err.] pagerankMonolithicSeq [damping=0.95]
# [33996.082 ms; 131 iters.] [3.4073e-01 err.] pagerankLevelwiseSeq [damping=0.95]
# [23698.520 ms; 084 iters.] [1.1537e-01 err.] pagerankMonolithicSeq [damping=0.90]
# [25438.498 ms; 086 iters.] [1.1538e-01 err.] pagerankLevelwiseSeq [damping=0.90]
# [15372.076 ms; 058 iters.] [1.4498e-07 err.] pagerankMonolithicSeq [damping=0.85]
# [13778.573 ms; 047 iters.] [4.0831e-06 err.] pagerankLevelwiseSeq [damping=0.85]
# [12635.385 ms; 044 iters.] [8.3088e-02 err.] pagerankMonolithicSeq [damping=0.80]
# [11039.472 ms; 035 iters.] [8.3088e-02 err.] pagerankLevelwiseSeq [damping=0.80]
# [11112.011 ms; 035 iters.] [1.5136e-01 err.] pagerankMonolithicSeq [damping=0.75]
# [13110.716 ms; 038 iters.] [1.5136e-01 err.] pagerankLevelwiseSeq [damping=0.75]
# [08859.578 ms; 028 iters.] [2.1045e-01 err.] pagerankMonolithicSeq [damping=0.70]
# [06935.414 ms; 023 iters.] [2.1045e-01 err.] pagerankLevelwiseSeq [damping=0.70]
# [06759.742 ms; 024 iters.] [2.6569e-01 err.] pagerankMonolithicSeq [damping=0.65]
# [05089.345 ms; 020 iters.] [2.6569e-01 err.] pagerankLevelwiseSeq [damping=0.65]
# [05259.400 ms; 020 iters.] [3.1422e-01 err.] pagerankMonolithicSeq [damping=0.60]
# [06107.679 ms; 018 iters.] [3.1422e-01 err.] pagerankLevelwiseSeq [damping=0.60]
# [05073.656 ms; 018 iters.] [3.5880e-01 err.] pagerankMonolithicSeq [damping=0.55]
# [06011.300 ms; 020 iters.] [3.5880e-01 err.] pagerankLevelwiseSeq [damping=0.55]
# [04309.695 ms; 015 iters.] [3.9532e-01 err.] pagerankMonolithicSeq [damping=0.50]
# [05140.188 ms; 014 iters.] [3.9532e-01 err.] pagerankLevelwiseSeq [damping=0.50]
#
# ...
```

[![](https://i.imgur.com/1L1y4n0.png)][sheetp]
[![](https://i.imgur.com/4aYgSx1.png)][sheetp]
[![](https://i.imgur.com/QZu9piW.png)][sheetp]
[![](https://i.imgur.com/U8A7P1z.png)][sheetp]

[![](https://i.imgur.com/S8aSAzd.png)][sheetp]
[![](https://i.imgur.com/jp8GQ8b.png)][sheetp]
[![](https://i.imgur.com/CFilBqu.png)][sheetp]
[![](https://i.imgur.com/9wUi3iA.png)][sheetp]

[![](https://i.imgur.com/7KhAr9U.gif)][sheetp]
[![](https://i.imgur.com/THykHUN.gif)][sheetp]

<br>
<br>


## References

- [STIC-D: Algorithmic Techniques For Efficient Parallel Pagerank Computation on Real-World Graphs](https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs)
- [Deeper Inside PageRank :: Amy N. Langville, Carl D. Meyer](https://www.slideshare.net/SubhajitSahu/deeper-inside-pagerank-notes)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/CxwDsTm.jpg)](https://www.youtube.com/watch?v=jcqkqJnTydU)

[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[gist]: https://gist.github.com/wolfram77/99ef2865eea9d483eb50ba5ce1a4b750
[charts]: https://photos.app.goo.gl/crWMPqmbV6JTHVGR7
[sheets]: https://docs.google.com/spreadsheets/d/1PqGsHP9Tz3yIu__Pepxh1ZWeVy-dqEz_3_LSdUobIYk/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vSBRQZbwZnLYp5rYaTGYaV3rOhEwBty8m0DhdSryT0yhe7o6T3LeHYApUJZL-R5WYcvdiPd0MuuS-Ai/pubhtml
