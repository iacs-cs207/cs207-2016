---
title: REST API
layout: lecture
mathjax: true
---

This is work needed after milestone 2.

Lets start by discussing what queries we want our system to support.

We are going to create fake "metadata" associated with our 1000 time series, so that we can test a workflow in which we query timeseries by their metadata in a relational database, get results, and look for similar other time series. There are 2 ways this can play out:

1. Find similar timeseries to a "given" timeseries in a database of all time series. We will support this, both for a given uploaded time series, and for an existing timeseries in the database (which may have been found as a result of a filtered search)
2. Find similar timeseries in a metadata-filtered subset (eg find similar light curves amongst those from cepheids). We shall NOT support this, as it would require us to support a subset of points in our index binary trees, and thus require a lot of development of fast intersections between relational queries and queries on our index trees.

We'll take the following steps to set up a REST API to support our queries, both on the relational databse, as well as on the socket-server database you are writing.

(1) keeping the ids of the 1000 timeseries from previous project missives, add random metadata for a floating point field `blarg` which takes continuous values on [0,1] drawn from a Uniform distribution.

(2) randomly drawn from letters A-F to create a field `level` associated with each id. This is kinda like throwing a dice: there are discrete enumerated values A/B/C/D/E/F that can result

(3) throw this information along with the mean (`mean`) and standard deviation(`std`) of the time series into a relational database. Thus the main table in this database has 5 columns: the `id` being the primary keys, and 4 others: `mean`, `std`, `blarg`, and `level`. You can get things working locally and test with sqlite, but for production you want to use postgres on your EC2 instance.

(4) support an additional query supported by your custom database server which returns a time-series for an id. Expose this to your command line program: you will need to support an additional operation in your protocol.  You should use your custom storage-manager that you wrote in part 8 of the project to fetch time series for this purpose from disk. At this stage make sure that when you store time series into the database, you use the storage manager interface as well. (upto now there has been no notion of storing the time series in the "database", you have probably just come up with your own scheme to store them on disk in some folder).

Now we will write a REST API that queries this relational database, the custom similarity database that you wrote, and the Storage Manager.

Endpoints you must support:

1. `/timeseries` `GET` should send back a json with metadata from all the time series
2. `/timeseries` `POST` adds a new timeseries into the database given a json which has a key for an id and a key for the timeseries, and returns the timeseries
3. `/timeseries/id` should send back metadata and the timeseries itself in a JSON payload
4. `/timeseries?mean_in=1.5-1.53` type queries should now be supported and send back only metadata. For continuous variables you only need to support range queries with string `mean_in=1.5-1.53` whereas for discrete variables(`level` here) you need to support equals and in `level_in=A,B,C` or `level=A`. For simpilicity we wont support equals or less-than/greater-than type queries on continuous variables. Finally we'll support only one query at a time (so no combined SELECTs on the database). This will enable you to develop either in DBAPI2 or SQLAlchemy (your choice, although I think that using Flask-SQLAlchemy is a bit easier).
5. `/simquery` `GET` should take a `id=the_id` querystring and use that as an id into the database to find the timeseries that are similar, sending back the ids of (say) the top 5.
6. `/simquery` `POST` should take a timeseries as an input in a JSON, carry out the query, and return the appropriate ids as well. This is an unusual use of `POST`.

This concludes part 10. Now you can see how a query might be made: use 4. to make a filter. Use 3 to draw the timeseries on the results page. Provide an additional link for each result that uses 5 to compute the similarity, showing the results using 3 again. We can also support a separate uploaded query using 6 and show the results. (The only remaining thread there is how to set things up to display the query timeseries which is NOT part of the database. The answer is to use the same code on the browser side that you used to display the time series earlier: this will ensure that your JS code is also modular.)
