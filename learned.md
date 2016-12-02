---
title: Wrapup
layout: lecture
mathjax: true
---

## What have we learnt?

Over the course of this semester, we've pursued multiple themes:

- a principled way of software development
- the structure of a language: what makes it fast, what makes it slow, and how it is extensible
- setting up a proper, tested, software product, with a web interface and databse backend
- the use of data structures and algorithms in real world settings such as dynamic arrays in python and trees in databases 
- notions of concurrency and parallelism, and how they apply both to writing code and obtaining data from databases
- the disabusing of the notion that systems like databases are conceptually hard: indeed hopefully this course gives you some confidence to approach an open source codebase or start your own, with the notion that you will figure it out.



Let us summarize major concepts in some of these major themes



### Software Design

- define interfaces using ABCs, if for no other reason, then documentation. Also they are key for separating abstract data types from their implementations
- choose good variable/function/class names. Remember you are writing for future you.
- else make sure to follow duck typing protocols (like `__len__` and ``__getitem__` make a sequence, though even this has been nor formalized via ABCs)
- use `isinstance` checks sparingly except when doing binary operation overloading, which is generally useful for numerical situations but should othwewise be sparingly used
- documentation should specify the contract and expectations between the user and the library writer. 
- pay particular attention to loop invariants, representation invariants, and abstraction functions
- doctests are a good way to start but should then be limited to those ones that make for good user examples
- use a testing framework like `py.test` to test early, test often, test edge cases, test incrementally, aiming for maximum test coverage as long as your tests are substantial. But test dumb things too, as you may never know when a change in implementation will break things
- use forking and cloning or branching to create pull requests: the integrator should integrate on a separate branch and make sure all tests run before merging
- stick to the languages and your group's conventions. Consensus on naming etc makes things easier to understand
- separate interfaces and implementations carefully
- consider embedding a DSL (domain specific language) in your project for users of your code
- if you have a very solid software spec, consider TDD.
- package code into small libraries, even if just for personal use
- interfaces apply to (command line) UI conventions as well



### Object Oriented Programming

- we treat everything as a noun: this lends itself to paradigms like REST
- python has a neat OO structure, with property decorators, class methods, class variables, instance methods and instance variables
- python derives much of its power from duck typing polymorphism and its object model comprised of dunder methods
- which allow us to redefine things like length and iteration (allowing us to program lazily)
- and also allows for (a somewhat unnatural, compared to say julia) operator overloading definition
- inherit interfaces or `isa`, combine in implementations using delegation

### Functional programming

- functional programming is all about referential-transparency (making functions mathy) 
- immutability (no alteration after assignment), which helps with concurrency and bookkeeping, and leads to paradigms like map-reduce
- and laziness where we dont want to evaluate anything until we really needed, which allows us (the compiler) to rewrite processes
- we treat everything as a verb

### How languages run

- there is a environment in which code runs: usually its a chained set of lookup "frames". closures capture things from parent frames and can be used to represent state from "defining" or "load" time
- recursive programs are fun and easy to write, but they can lead to an unbounded set of frames (unless your language has tail-recursion, which python does not)
- python is slow so choose data structures sensibly if you want high performance. The contiguity and heap allocation make a difference. Remember that dynamic typing in Pytho means that lists contain pointers to heap allocated objects. Not true in `numpy` unless you iteratively access by boxing.
- Julia for example will have the same list structure if you dont type the items, or if the compiler cannnot type infer. But if you know concrete types ahead of time Julia will create a list of values rather than pointers to `Any`.
- Also make sure you respect the GIL in concurrent code. IO bound use threads or coroutines. Compute bound use multiprocessing
- implementing dunders is key to making iteration and other functionality just work: there is some kind of *Principle of Least Surprise*
- consider making DSLs for your systems

### Data Structures and databases

- good data structures can make a lot of difference to an algorithm. think which one to use in interface (ADT) and implementation
- hashing is your friend in many many places.
- think of how you might use trees and append based log files
- understand SQL and ORMs in front of it for fast relational database programming. SQL is not negotiable these days
- the concepts of atomicity and isolation in transactions mirrot the concepts around shared access in databases
- thus functional concepts (no shared state) work well, and indeed provide robust performance in database systems
- LSM trees are replacing b-trees for write intensive workloads
- always consider workload: ETL? OLTP? Warehousing? streaming data? Architectures depend on this.
- we havent covered it but distributes databases are a fun topic in themselves

### Systems

- package your code into pip installable packages with tests instead of keeping them monolithic
- learn the unix command line and how to write CLIs (see `stupidlang`). You will be very thankful
- when you test, test in a fresh conda environment or virtualenv so that your testing is clean-room. Even better, test on a freshly installed virtual machine on AWS, using, for example, travis CI and coveralls
- by the same token, make sure your software can be easily installed by a user on AWS or Heroku, for example
- `concurrent.futures` exports an interface that makes it very easy to use threads and process pools. The new `asyncio` in python 3.4 onwards makes async programming to replace threads a cinch as well
- both of these can be used to write very scaleable servers. Do not be sacred to export computations through servers
- become full stack. Its not enough to know the back-end development, but also UI using javascript and HTML and javascript frameworks, with the key concepts of JSON and callback based asynchronous programming (`$.ajax`)


###Software Patterns

The definitions are taken from the GOF book.

- Template Method: Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Eg: hooks in binary search trees
- Visitor: Represent an operation to be performed on the elements of an object structure…lets you define a new operation without changing the classes of the element on which it operates. Eg: traversal or iterator with accompanying function in a tree
- Observer: Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated immediately. This is used in Backbone.js to automatically update models when views change, and vice-versa.
- Iterator: provides a way to access the elements of an aggregate object  sequentially without exposing its underlying implementation. We've seen these all over Python, including in trees, French-Decks, etc. By some implemnentation in ABCs, we could even do things like linear search on the french deck.
- Proxy: Provide a surrogate or placeholder for another object to control access to it. Eg the `SMTimeseries` is a proxy for time series in the `StorageManager`.
- Bridge: Decouple an abstraction from its implementation so the two can vary independently. (We did not do this but would have been a better way of handling the TimeSeries inheritance tree)
- Factory Method: Define an interface for creating an object, but let subclasses decide which class to instantiate. Defer instantiation to subclasses. (This is what we did with the `SizedTimeSeriesInterface`)

And in general, toward the end (and in lecture) we focusses on using composition (with delegation) over inheritance. The FrenchDeck did not inherit from a list. And while our initial time series implementations did, out end product has a compositional flavor: the `SMTimeSeries` can change its underlying Storage manager without any changes. (One could extend that to the single time series case, not just the one in which we want to get a bunch of time series from a database!)



## Where to go from here?

- I promise you that the skills you have learned will come useful in your careers. Data Engineers are in even more demand than data scientists today and having both skill-sets makes you a very valuable part of any operation. And if you learned nothing else, this will help you interview. Many students last year told me this was the most useful course for interviews :-).
- read The Practice of Programming and The Pragmatic Programmer. Both books are about 10 years old but are classics
- if you like databases read Designing Data Intensive Applications
- The books here are a great resource: http://aosabook.org/en/ . Read 500 lines or less especially, I have used it extensively.
- Learn some other programming languages. I recommend Julia, Scala, Go, and Haskell. They key is to see other paradigms!
- If you feel weak on basic unix/git etc skills work through the Software Carpentry courses.