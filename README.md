# ggmModel

This is an implementation of the [Gómez-Gardeñes & Moreno network model](http://journals.aps.org/pre/abstract/10.1103/PhysRevE.73.056124), intended for general-purpose usage. 

Feel free to use and/or contribute to this repository. In the near future, we should have a Python interface and routines to export the resulting network into several different formats.


# Usage

You can simply run the following. Suppose you want 10000 nodes, with increasing 10 connections per iteration and mixing probability of 1.0 (pure Erdos-Renyi).

```
make
time ./ggmModel $RANDOM 10000 10 1.0 output.dat
```

This will construct a network and output all degrees in output.dat.

Sample output:
```
[user@PC C++]$ time ./ggmModel $RANDOM 10000 10 1.0 output.dat

real	0m0.418s
user	0m0.102s
sys	0m0.316s
```


# License

This is a free software under a somewhat permissive license (MIT). Please refer to [LICENSE](https://github.com/zericardo/ggmModel/blob/master/LICENSE) file in this repository for details.
