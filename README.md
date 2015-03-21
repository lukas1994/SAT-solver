# SAT-solver
Implementation of the [DPLL](http://en.wikipedia.org/wiki/DPLL_algorithm) SAT algorithm in C++. The algorithm uses unit propagation and conflict-driven clause learning.

### Usage

The program accepts an input file in the [CNF file format](http://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html).

To build and run the program type:

```
make
./run [.cnf FILE]
```

The output is either `unsatisfiable` or `satisfiable`. In the latter case the program outputs a model for the given formula.

### Benchmarks
All benchmarks were run on the following machine: MacBook Pro, Mid 2012, OS X 10.9.5, 2.5GHz Intel Core i5, 4GB 1600MHz DDR3.

##### 50 variables, 218 clauses each ([data](http://www.cs.ubc.ca/~hoos/SATLIB/Benchmarks/SAT/RND3SAT/uf50-218.tar.gz))

* 1000 instances, all satisfiable: total time: 17m29.658s 
* average time per instance: ** 1.05s **

##### more benchmarks:
[SATLIB](http://www.cs.ubc.ca/~hoos/SATLIB/benchm.html)