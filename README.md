# ggmModel


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
