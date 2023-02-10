Design of **Levelwise** *PageRank algorithm* for link analysis.

[Levelwise PageRank] is the [STIC-D algorithm], without **ICD** optimizations
(using a single-thread here). We use a rank [pull] based approach, and perform
the computation upon the [CSR] representation of a graph. If the size of a
level is fewer than 10 vertices, we combine multiple levels together
([compute-10]).

We attempt each experiment (mentioned below) on different types of graphs,
running each approach 5 times per graph to get a good time measure. The input
data used for each experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. Experiments were done with guidance from
[Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>


### Adjusting Damping factor

Adjustment of the *damping factor α* is a delicate balancing act. For smaller
values of *α*, the convergence is fast, but the *link structure* *of the graph*
used to determine ranks is less true. Slightly different values for *α* can
produce *very different* rank vectors. Moreover, as α → 1, convergence *slows
down drastically*, and *sensitivity issues* begin to surface.

For this experiment ([adjust-damping-factor]), the **damping factor** `α` (which
is usually `0.85`) is **varied** from `0.50` to `1.00` in steps of `0.05`. This
is in order to compare the performance variation with each *damping factor*. The
calculated error is the *L1 norm* with respect to default PageRank (`α = 0.85`).
Since *Levelwise PageRank* requires the *absence of dead ends* (teleport-based
dead end handling strategy does not work), before performing any PageRank
computation, **self-loops** are added to *dead ends*. **Monolithic PageRank**
computation is also performed, which is used for performance comparison and
error measurement.

Results indicate that **increasing the damping factor α beyond** `0.85`
**significantly increases convergence time** , and lowering it below `0.85`
decreases convergence time. As the *damping factor* `α` increases *linearly*,
the iterations needed for PageRank computation *increases almost*
*exponentially*. On average, using a *damping factor* `α = 0.95` increases
*iterations* needed by `170-180%` (`2.7-2.8x`), and using a *damping* *factor*
`α = 0.75` *decreases* it by `40%` (`0.6x`), compared to *damping factor* `α =
0.85`. Note that a higher *damping factor* implies that a random surfer follows
links with *higher probability* (and jumps to a random page with lower
probability).

[adjust-damping-factor]: https://github.com/puzzlef/pagerank-componentwise/tree/adjust-damping-factor

<br>


### Adjusting Tolerance function

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

This experiment ([adjust-tolerance-function]) was for comparing the performance
between PageRank computation with *L1, L2* and *L∞ norms* as convergence check,
for *damping factor `α = 0.85`, and *tolerance* `τ = 10⁻⁶`. Since *Levelwise*
*PageRank* requires the *absence of dead ends* (teleport-based dead end handling
strategy does not work), before performing any PageRank computation,
**self-loops** are added to *dead ends*. **Monolithic PageRank** computation is
also performed, which is used for performance comparison and error measurement.

From the results it is clear that PageRank computation with **L∞ norm as**
**convergence check is the fastest** , quickly followed by *L2 norm*, and finally
*L1 norm*. Thus, when comparing two or more approaches for an iterative
algorithm, it is important to ensure that all of them use the same error
function as convergence check (and the same parameter values). This would help
ensure a level ground for a good relative performance comparison. It is also
observed that *Levelwise PageRank* comverges faster than *Monolithic PageRank*
in most cases. Also note that PageRank computation with **L∞ norm** as
convergence check **completes in a single iteration for all the road**
**networks** *(ending with _osm)*. This is likely because it is calculated as
`||E||ᵢ = max(|rₙ - sₙ|)`, and depending upon the *order (number of vertices)*
`N` of the graph (those graphs are quite large), the maximum rank change for any
single vertex does not exceed the *tolerance* `τ` value of `10⁻⁶`.

[adjust-tolerance-function]: https://github.com/puzzlef/pagerank-componentwise/tree/adjust-tolerance-function

<br>


### Adjusting Compute size

This experiment ([adjust-compute-size]) was for comparing performance between
various min. compute sizes, ranging from `1` - `1E+7`. As mentioned above, *min.
compute size* is the minimum number of vertices per level. If the size of a
level is fewer than 10 vertices, we combine multiple levels together. From the
results, it appears a *min. compute size* of `10` would be a good choice.

[adjust-compute-size]: https://github.com/puzzlef/pagerank-componentwise/tree/adjust-compute-size

<br>


### Skipping Teleport calculation

In this experiment ([skip-teleport]), we check the performance benefit of
Levelwise PageRank when *teleport* calculation is *skipped*. Results show that
except for `soc-LiveJournal1` and `coPapersCiteseer`, in all cases *skipping*
teleport calculations is *slightly faster*. The improvement is most prominent in
case of *road networks* and certain *web graphs*.

[skip-teleport]: https://github.com/puzzlef/pagerank-componentwise/tree/skip-teleport

<br>


### Comparison with Monolithic approach

In this experiment ([compare-monolithic], [main]), we compare the performance
between Monolithic and Levelwise PageRank. On average, results indicate that
*Levelwise PageRank* is *faster* than the Monolithic approach.

[compare-monolithic]: https://github.com/puzzlef/pagerank-levelwise/tree/compare-monolithic
[main]: https://github.com/puzzlef/pagerank-levelwise

<br>


### Other experiments

- [adjust-tolerance-function-analysis](https://github.com/puzzlef/pagerank-componentwise/tree/adjust-tolerance-function-analysis)
- [adjust-tolerance-analysis](https://github.com/puzzlef/pagerank-componentwise/tree/adjust-tolerance-analysis)
- [adjust-component-size](https://github.com/puzzlef/pagerank-componentwise/tree/adjust-component-size)
- [adjust-monolithic-iterations](https://github.com/puzzlef/pagerank-componentwise/tree/adjust-monolithic-iterations)
- [perform-initialization](https://github.com/puzzlef/pagerank-componentwise/tree/perform-initialization)

<br>


## References

- [STIC-D: algorithmic techniques for efficient parallel pagerank computation on real-world graphs][STIC-D algorithm]
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]
- [Merge git repo into branch of another repo](https://stackoverflow.com/a/21353836/1413259)

<br>
<br>


[![](https://img.youtube.com/vi/vbXTZlJ5fHU/maxresdefault.jpg)](https://www.youtube.com/watch?v=vbXTZlJ5fHU)


[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[Levelwise PageRank]: https://ieeexplore.ieee.org/abstract/document/9835216
[STIC-D algorithm]: https://dl.acm.org/doi/abs/10.1145/2833312.2833322
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu/
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank
[CSR]: https://github.com/puzzlef/pagerank
[compute-10]: https://github.com/puzzlef/pagerank-levelwise
