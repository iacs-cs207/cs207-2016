---
title: tsdb (part 1, milestone 2) - client communication
layout: lecture
mathjax: true
---


This is a skeleton for the database part 1 of milestone 2 of your project.

## copying this over

You want to copy `both.sh` and the `go-*` files to the toplevel of your project, and the subfolder `tsdb` to be at par with the rest of your project modules such as `timeseries` and `pype`.

## running the client and server

- You can run both the client and the server to (informally) test your output together as `sh both.sh` from this folder.
- `go_server.py` sets up the database schema and the database server
- `go_client.py` has a set of commands to run from the client to the server, inserting some time-series (`insert_ts`), updating if not inserting and inserting otherwise their metadata (`upsert_meta`), and carrying out a select `select`

## the `tsdb` module: here is where you do the work.

Signatures for all the implementations you need to do are provided to you in the files themselves. A transcript of the output can be seen in [output.md](output.md).

- `__init__.py` exports the module
- `dictdb.py` **implements an in-memory, dictionary based database**. You will be implementing large chunks of this. WORK TO BE DONE HERE
- `tsdb_client.py` **implements a client for the database that paks the json and sends it out**. You will be implementing all of this. You are free to do this using asyncio or synchronous socket techniques. Keep in mind that you might want to reuse these functions inside a http server which you will be writing for the end of your project: if you want to implement this server synchronously in flask for example, you might want to use synchronous technology. On the other hand if you want to use `aiohttp` or `tornado`, use something asynchronous and figure out how to combine both the http serving and the database client calls in the same event loop. WORK TO BE DONE HERE
- `tsdb_server.py`: ** unpack json and run **: currently, at least, we provide all the implementation of a callbacks based asynchronous socket server. Please read carefully how this file works as we will ask you to make modifications to it later next week.
- `tsdb_error.py`: **provides error and status handling**
- `tsdb_ops.py`: **documents the database ops supported**, including their "string names" in the `typemap`, and **conversion to and from a json-like dictionary structure**
- `tsdb_serialization.py`: in class you saw how client-server communication benefits from having some **wire format**. Here you will implement the serialization from json-like dictionary, to json, to bytes on the network. We implement de-serialization for you. WORK HERE

## How the database works

`dictdb` is a very simple (for-now) in memory database. No persistence.

- the primary key, which must be unique, is called `pk`
- `self.rows` contains all the rows. This is a dictionary with keys the primary keys
- `self.index` is a dictionary. The keys are the indexed fields. The values are the index for each field.
- The index itself is an inverse-lookup dictionary. Say a field `f` has values 1,9,33,1 in pks 1,2,3,4. Then self.index['f']={1:[1,4], 2:[9], 3:[33]}.
- Notice that we `update_indices` on all database changing operations. Here these are `insert_ts` and `upsert_meta`. You must implement the latter. You must also implement the `select` function.
