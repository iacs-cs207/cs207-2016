---
title: Last Lecture
layout: default
---

## Query Language and Optimization

- first query expander converts to ir
	- semantic optimization
	- logical rewriting of predicates]
	- subquery flattening

- query optimization: ![](https://dl.dropboxusercontent.com/u/75194/queryopt.png)
- selectivity estimation
- search plan search
- parallel scheduling
- iterators

From the Architecture paper

> All operators in a query plan — the nodes in the dataflow graph — are implemented as subclasses of the iterator class. The set of subclasses in a typical system might include filescan, indexscan, sort, nested-loops join, merge-join, hash- join, duplicate-elimination, and grouped-aggregation. An important feature of the iterator model is that any subclass of iterator can be used as input to any other.

- Query implementation considerations: the halloween problem: ![](https://dl.dropboxusercontent.com/u/75194/queryimpl.png)
