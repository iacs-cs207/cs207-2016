---
title: Dunders and Operator Overloading on Time Series
layout: lecture
mathjax: true
---



This will be graded along with the rest of your codebase at the course Milestone 1.

## Part 1: Add some more methods

Your `TimeSeries` class should be, by now, **a well documented, well tested, mutable, class which implements**:

- `__getitem__`: to get a value for a given index (should have done this)
- `__setitem__`: set the value for the given index (should have done this)
- `__contains__`: is a value in the values (NEW)
- `__iter__`: iterates over values. (This might have iterated over tuples of (time, value) pairs earlier (should have done this)
- `values`: returns a numpy array of values (should have done this)
- `itervalues`: returns an iterator over them (NEW)
- `times`: returns a numpy array of times (NEW)
- `itertimes`: returns an iterator over them (should have done this)
- `items`: returns a list of time-value tuple pairs (NEW)
- `iteritems`: returns an iterator over these (should have done this)
- `__len__`: returns a length. (should have done this)
- `__repr__`: abbreviating string representation (should have done this)

## Part 2: Add to these methods(again well tested):

- infix addition, subtraction, equality and multiplication. Here you must check that the lengths are equal and that the time domains are the same for the case of the operations on a TimeSeries (the latter implies the former). Return a `ValueError` in case this fails:

`ValueError(str(self)+' and '+str(rhs)+' must have the same time points')`

Let these be elementwise operations, as we might expect from a numpy array-like thing. As before, handle the case of a constant.
- unary `__abs__`, `__bool__`, `__neg__`, and `__pos__` with the same semantics as the `Vector` class we saw in lecture.


A question that might arise is what to do if we add numpy arrays or regular python lists to a `Timeseries`. These should fail with `raise NotImplemented` as we dont have time associated. An option might have been to associate the array with the time indexing of the other array, but this is making too many assumptions: the user can do this explicitly.

You will probably have to catch another exception for this to happen.

Put this code into your project repo.