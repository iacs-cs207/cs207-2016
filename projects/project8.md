---
title: Storage Manager
layout: lecture
mathjax: true
---

This work is due in Milestone 2, 11.59PM, November 30th, 2016

### Persistent Storage

So far we have inherited from TimeSeries ABC's, the appropriate form of time series we have wanted to use, whether simulated or stored.

In this part, we'll focus on Timeseries, and focus on the issue of **Persistent** storage, while still obtaining individual time series.

Why do this?

1. We'd like to move to a system in which the storage of time series is orthogonal to the functionality they provide. In other words, a time series ought to be characterized by what you can do with it, rather than how it is stored
2. In a database like scenario, the srorage issues that concerns us is how a **collection** of time series are stored and queried, not how an individual one is produced.

### Feeding time series for ops

The time series interface largely consists of methods allowing for iteration on time series and operations between them. These operations would need to be re-defined in terms of whatever our storage interface provides in terms of obtaining elements from a time series.

For example, if you do something like `ts1 + ts2`, we must pull `t1` from storage, possibly caching it, do the same for `t2`, and compute `t1+t2`. We might even want to ask the question: should the result be automatically stored?

Here's we'll opt for a simple interface which explicitly stores and fetches. We'll do this for an isolated setup right now, integrating it into out overall project after milestone 2

### milestone 2 work

(1) Create a new `StorageManagerInterface` which has abstract methods: 

   - `store(id:int/string, t:SizedContainerTimeSeriesInterface)->SizedContainerTimeSeriesInterface`
   - `size(id:int/string)->int`
   - `get(id:int/string)->SizedContainerTimeSeriesInterface`

   Notice that one implication of this interface is that we are also letting the storage manager handle the in-memory needs of our time series.

(2) Inherit from your `SizedContainerTimeSeriesInterface` a new class, `SMTimeSeries`. The SM stands for StorageManager. The normal constructor for a time series (which we have not specified to be part of the standard interface) would take times and values lists as arguments. Now we have two possible choices for construction:

   - `__init__`: times and values, and an optional id (the storage manager should autogenerate one if an id is not provided), which then ought to store the time series into a storage manager. 
   - classmethod `SMTimeSeries.from_db(id)`: a method with an id to look up and fetch from the storage manager, having the manager allocate the time series in memory.

(3) Create a `FileStorageManager` that inherits the `StorageManagerInterface` ABC and implements it by putting 2-d numpy arrays with 64-bit floats for both times and values onto disk. This manager must support having some form of the time series in memory both on `get` and `store` (see the interface above).

   You can use anything implementing  `SizedContainerTimeSeriesInterface` inside the manager (with some likely changes to how its constructed). The manager should maintain a persistent structure in memory and on disk which maps ids to the appropriate files and keeps track of lengths. Make sure you minimize copying of arrays

(4) Now `SMTimeSeries` should use delegation in methods that need implementing to the `SizedContainerTimeSeriesInterface` object that the storage manager returns to us. This ensures that `SMTimeSeries` is independent of the actual implementation (list/np.array/array.array, etc) of the sized time series and allows you to use previous work; while at the same time not having to create an overly large storage manager interface. You might want to think about how to minimize code repetition during this delegation

(5) To think, but not to submit: instead of direct caching to a `SizedContainerTimeSeriesInterface`, how might you do this in the most lazy way possible? Also, how might you write a more performant storage manager implementation?



As before, document and test!
