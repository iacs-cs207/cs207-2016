---
title: Project Expectations
layout: default
---

## Overall Project

- you must make this database persistent.
  - You can choose a persistence of your choice.
  - You can decide to keep time series themselves in files and materialize them on demand, or to put them in a heap file.
  - You must make a primary index for the primary key, and secondary indices for the other metadata
  - one idea is a primary-key clustered index for the primary-key and rows, and bitmask indexes for low-cardinality "factor" or "enum" types which only take certain values and/or binary tree for the numeric ones (you will need to implement low-hi iteration and/or repeated values for a key) .
  -  You will need to introduce the concept of a transaction. Make sure changes in the database are atomic by implementing appropriate exception handling and rollback on fail. Also make sure that they are durable, ie, after a transaction is committed, the changes are available on disk. You do not need to implement isolation.
  - To keep things simple, its strongly advised that you assume that the schema tells you the types of objects: you might want to add a `type` field to the schema.
  - implement deletion of time-series in the database
- you must represent vantage points in this persistent database (just like we did in part 3) . The code in `go_client.py` to do vantage point searches can be encapsulated into a database population script
- there should be a http based REST api to the database. The API design is your choice, and depending on if you decided to write a synchronous client or an asynchronous client, you might want to choose flask or tornado/aiohttp to provide a second way to get at the database besides `tsdb_client.py`. This API should provide the ability to:
  - insert time series
  - upsert metadata
  - delete time series
  - select
  - do augmented select
  - do time-series similarity search
- You must implement one additional feature per group in the project. This feature cannot be isolated: its code should be incorporated into the project. Possible choices are:
  - a really fast FFT using cython on fftw integrated in
  - vantage point storage using a vptree integrated in ([http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.43.7492](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.43.7492))
  - A threading/multiprocessing based server where multiple processes write to the database. Implement at least read-committed isolation.
  - implement a proper language with repl as a client for the database
  - implement the iSAX tree ([http://www.cs.ucr.edu/~eamonn/iSAX_2.0.pdf](http://www.cs.ucr.edu/~eamonn/iSAX_2.0.pdf))to perform quick similarity searches, test for example on stock data and build a great interface for it
- your project MUST be installable by us. Make sure you test it on travis for this purpose: the requirements that you need to set up to install it will tell us how to do the install as well. It goes without saying that once again, test results on travis, including coverage stats, are expected. We will actually run your projects!
