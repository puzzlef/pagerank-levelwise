Checking the performance benefit of [levelwise] PageRank when **teleport**
**calculation** is **skipped** ([pull], [CSR]).

This experiment was for comparing performance between:
1. Find [monolithic] pagerank.
2. Find [monolithic] pagerank, **skipping teleport**.
3. Find [levelwise] pagerank.
4. Find [levelwise] pagerank, **skipping teleport**.

Each approache was attempted on different types of graphs, running each
approach 5 times per graph to get a good time measure. **Levelwise** pagerank
is the [STIC-D algorithm], without **ICD** optimizations (using single-thread).
Except for `soc-LiveJournal1` and `coPapersCiteseer`, in all cases **skipping**
**teleport calculations** is **slightly faster** (could be a random issue for
the two). The improvement is most prominent in case of *road networks* and
certain *web graphs*.

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
# order: 281903 size: 2312669 {} (loopDeadEnds)
# order: 281903 size: 2312669 {} (transposeWithDegree)
# [00431.040 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithic
# [00420.998 ms; 063 iters.] [0.0000e+00 err.] pagerankMonolithic [skip-tele]
# [00269.015 ms; 055 iters.] [3.9399e-06 err.] pagerankLevelwise
# [00250.271 ms; 055 iters.] [3.9399e-06 err.] pagerankLevelwise [skip-tele]
#
# ...
#
# Loading graph /home/subhajit/data/indochina-2004.mtx ...
# order: 7414866 size: 194109311 {}
# order: 7414866 size: 195418438 {} (loopDeadEnds)
# order: 7414866 size: 195418438 {} (transposeWithDegree)
# [19029.875 ms; 059 iters.] [0.0000e+00 err.] pagerankMonolithic
# [18562.752 ms; 059 iters.] [0.0000e+00 err.] pagerankMonolithic [skip-tele]
# [14780.369 ms; 056 iters.] [3.4176e-06 err.] pagerankLevelwise
# [14373.581 ms; 056 iters.] [3.4176e-06 err.] pagerankLevelwise [skip-tele]
#
# ...
```

[![](https://i.imgur.com/9WLLXVu.gif)][sheets]
[![](https://i.imgur.com/X6iObce.gif)][sheets]

<br>
<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.postimg.cc/PJbvkh18/aaa.jpg)](https://www.youtube.com/watch?v=SoiKp2oSUl0)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[STIC-D algorithm]: https://www.slideshare.net/SubhajitSahu/sticd-algorithmic-techniques-for-efficient-parallel-pagerank-computation-on-realworld-graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[monolithic]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[levelwise]: https://github.com/puzzlef/pagerank-monolithic-vs-levelwise
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/9QnAES4iRXg5pDd17
[sheets]: https://docs.google.com/spreadsheets/d/1EoVQpZ-lTAHOHNKhpD-1wi3G8-m0ojdA0Qt1qoNCLu4/edit?usp=sharing
