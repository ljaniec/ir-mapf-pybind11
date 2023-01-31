# IR-mapf

A simulator of Multi-Agent Path Finding (MAPF), used in a paper ["Iterative Refinement for Real-Time Multi-Robot Path Planning"](https://arxiv.org/abs/2102.12331).
It is written in C++(17) with [CMake](https://cmake.org/) (≥v3.16) build.
The repository uses [Google Test](https://github.com/google/googletest) and [the original library for 2D pathfinding](https://github.com/Kei18/grid-pathfinding) as git submodules.

The implementations include: HCA\* and WHCA\* [1], PIBT [2], CBS [3], ICBS [4], ECBS [5], Revisit Prioritized Planning [6], Push and Swap [7], winPIBT [8], PIBT+, and IR (Iterative Refinement).

===

We study the iterative refinement of path planning for multiple robots, known as multi-agent pathfinding (MAPF).
Given a graph, agents, their initial locations, and destinations, a solution of MAPF is a set of paths without collisions.
Iterative refinement for MAPF is desirable for three reasons:

1) optimization is intractable,
2) sub-optimal solutions can be obtained instantly, and
3) it is anytime planning, desired in online scenarios where time for deliberation is limited.

Despite the high demand, this is under-explored in MAPF because finding good neighborhoods has been unclear
so far. Our proposal uses a sub-optimal MAPF solver to obtain an initial solution quickly, then iterates the two
procedures:

1) select a subset of agents,
2) use an optimal MAPF solver to refine paths of selected agents while keeping other paths unchanged.

Since the optimal solvers are used on small instances of the problem, this scheme yields efficient-enough solutions
rapidly while providing high scalability. We also present reasonable candidates on how to select a subset of agents.
Evaluations in various scenarios show that the proposal is promising; the convergence is fast, scalable, and with
reasonable quality.

## Usage

- PIBT

```sh
./app -i ../instances/sample.txt -s PIBT -o result.txt -v
```

- With Python bindings

```python
TBD
```

- IR (the result will be saved in result.txt)

```sh
./app -i ../instances/random-32-32-20_70agents_1.txt -s IR_HYBRID -n 300 -t 100 -v
```

- With Python bindings

```python
TBD
```

Please see `instances/sample.txt` for parameters of instances, e.g., filed, number of agents, time limit, etc.

### Output File

This is an example output of `../instances/sample.txt`.
Note that `(x, y)` denotes location.
`(0, 0)` is the left-top point.
`(x, 0)` is the location at `x`-th column and 1st row.

```terminal
instance= ../instances/sample.txt
agents=100
map_file=arena.map
solver=PIBT
solved=1
soc=3403
makespan=68
comp_time=58
starts=(32,21),(40,4),(20,22),(26,18), [...]
goals=(10,16),(30,21),(11,42),(44,6), [...]
solution=
0:(32,21),(40,4),(20,22),(26,18), [...]
1:(31,21),(40,5),(20,23),(27,18), [...]
[...]
```

## Notes

- Maps in `maps/` are from [MAPF benchmarks](https://movingai.com/benchmarks/mapf.html).
  When you add a new map, please place it in the `maps/` directory.

## References

1. Silver, D. (2005).
    Cooperative pathfinding.
    Proc. AAAI Conf. on Artificial Intelligence and Interactive Digital Entertainment (AIIDE-05)
1. Okumura, K., Machida, M., Défago, X., & Tamura, Y. (2019).
   Priority Inheritance with Backtracking for Iterative Multi-agent Path Finding.
   Proc. Intel. Joint Conf. on Artificial Intelligence (IJCAI)
1. Sharon, G., Stern, R., Felner, A., & Sturtevant, N. R. (2015).
   Conflict-based search for optimal multi-agent pathfinding.
   Artificial Intelligence
1. Boyarski, E., Felner, A., Stern, R., Sharon, G., Tolpin, D., Betzalel, O., & Shimony, E. (2015).
   ICBS: improved conflict-based search algorithm for multi-agent pathfinding.
   Proc. Intel. Joint Conf. on Artificial Intelligence (IJCAI)
1. Barer, M., Sharon, G., Stern, R., & Felner, A. (2014).
   Suboptimal Variants of the Conflict-Based Search Algorithm for the Multi-Agent Pathfinding Problem.
   Annual Symposium on Combinatorial Search (SoCS)
1. Čáp, M., Novák, P., Kleiner, A., & Selecký, M. (2015).
   Prioritized planning algorithms for trajectory coordination of multiple mobile robots.
   IEEE Trans. on automation science and engineering
1. Luna, R., & Bekris, K. E. (2011).
   Push and swap: Fast cooperative path-finding with completeness guarantees.
   Proc. Intel. Joint Conf. on Artificial Intelligence (IJCAI)
1. Okumura, K., Tamura, Y. & Défago, X. (2020).
   winPIBT: Extended Prioritized Algorithm for Iterative Multi-agent Path Finding.
   IJCAI Workshop on Multi-Agent Path Finidng (WoMAPF)
