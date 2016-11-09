---
title: Immutable Red-Black Search Tree Implementation
layout: lecture
mathjax: true
---

This will be graded at milestone 2, due 11.59PM, 29th October

The job of this part, project 6, is to construct a functional red-black tree database, in a new python module, `cs207rbtree`. Develop this in the `cs207project` repo, or optionally another repo of your choice, whose name is linked from the `cs207project` `README.md`. This module should be pip installable, and properly travis-ci'ed and coveralled.

For milestone 2, this database needs only to work as a library, which carries out its work in a manner to sqlite: multiple processes may access the database at the same time. Remember that you are basing this off lab10, where simultaneous reads are allowed, but simultaneous writes are not.

My suggestion is to first implement the database as an unbalanced binary search tree: basically you need to cross the t's and dot the i's on the lab and add a Transaction manager. The code can be more elegant, and you must document it better, and test it extensively. Make sure the testing tests atomicity and rollback. 

Make sure that you have read-committed isolation. The code already does this by default, but we need to keep track of the transactions. To do this you will need to keep a transaction mamager that keeps track of both read and write transactions explicitly, along with the version of the tree made available to that transaction. This manager must be persisted on a database close, but in milestone 2 we shall skip writing out a transaction manager log (a write ahead log) from which transactions can be reconstructed if desired.

Then implement the red-black tree. There will be much more writing to disk due to re-balancing on updates creating new branches upwards to the root. You do not need to implement deletion (deletion is complex!). 


Sources:

My implementation was simplified and taken from http://aosabook.org/en/500L/dbdb-dog-bed-database.html, which you should read. For balancing, these will help: http://scottlobdell.me/2016/02/purely-functional-red-black-trees-python/ and https://dl.dropboxusercontent.com/u/75194/okasakiredblack99.pdf

You will later make your database usable in a multithreaded-multiprocess socket-frontend solution. 