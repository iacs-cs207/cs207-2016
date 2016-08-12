---
title: Final Thoughts
layout: default
---

## The major aim

The major aim of CS207 was to introduce non computer-scientists to ideas and techniques in computer

So we've reached near the end of this course. There's been a lot of concepts, a lot of work, a lot of things to learn. This might be a good time to step back and summarize.

## Goals

But, even before we get there, lets recall some of our goals in this course. I hope that you feel that some of these were achieved...

1. We wanted to become better programmers, and in particular, better Python programmers.
2. We wanted to learn to be disciplined in writing our code, testing it well and at multiple places to make sure that we do not accumulate technical debt, and be able to safely refactor our code
3. We wanted to become dangerous: we wanted to gain confidence that we could understand how complex things such as databases and Theano worked. And to be able to implement DSL's as interfaces to our work.
4. To be able to do this we wanted to gain a broad based familiarity with fundamental concepts at a level that would enable us to start making simple implementations, and understand how to make optimizations
5. And thus we wanted to learn more about languages and databases, in a deep sense, as these exercise a lot of the fundamental concepts
6. And we wanted to do all of this, with the ability to think carefully through the correctness and performance consequences of our choices, as we choose algorithms and technology  for our problem at hand

We called this:

​		 **Unicorn Level 1 Unlocked**

## Concrete things we learned

1. The execution model of languages: bindings, environments, stacks, virtual machines, intermediate representations and bytecode
2. Creating languages: syntax trees, metacircular evaluation, lexing, parsing, symbol tables, semantic analysis, interpretation, DSLs, (and even pseusdo-languages through polymorphism)
3. Models for writing programs: recursion, iteration, lazyness, functional programming, the object(data) model, object-oriented programming, polymorphism and overloading
4. Measuring a program: debugging and profiling
5. Writing fast programs: C, pointers, memory allocation, wrapping C, cython, performance, memory layout, generators, coroutines, and iteration
6. Data Structures: lists, trees, graphs, hashing and their multifarious uses in things like median maintenance, language IR, and databases. Also, creating unusual structures for unusual situations (time series similarity).
7. Concurrent and parallel programming in asynchronous (coroutines and callbacks), multiprocess and multithreaded style, and the consequences of these styles for shared objects
8. Systems programming for networking and databases, including sockets and protocols
9. Unit testing, coverage, continuous integration, invariants, Abstract Data types, representation-invariants.
10. Technology for productifying including modules, module setup, and web servers

## Things we missed out on

(In other words, you should learn about these. Preferably soon, in the summer, while the course is still fresh with you)

Clearly we have a finite amount of time. We missed out on these important things:

1. Caches and cacheing
2. Replication and partitioning: distributed databases and distributed programming in general. (Check out Developing Data Intensive Applications for this)
3. Functional programming and concurrency
4. Evaluating existing NoSQL databases (you should do this soon)
5. More on computational graphs: examples including Theano And Spark. You should check out the source code for Dask.
6. More Programming languages: you should check out javascript and React.js, Haskell and Julia at the very least
7. Generic Programming: check out Julia and C++ for this, or read more about Java Generics.
