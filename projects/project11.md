---
title: Web Interface
layout: lecture
mathjax: true
---

In the last part you wrote a REST API.

This is work needed after milestone 2.

Lets start by discussing what queries we want our system to support.

We are going to create fake "metadata" associated with our 1000 time series, so that we can test a workflow in which we query timeseries by their metadata in a relational database, get results, and look for similar other time series. There are 2 ways this can play out:

1. Find similar timeseries to a "given" timeseries in a database of all time series. We will support this, both for a given uploaded time series, and for an existing timeseries in the database (which may have been found as a result of a filtered search)
2. Find similar timeseries in a metadata-filtered subset (eg find similar light curves amongst those from cepheids). We shall NOT support this, as it would require us to support a subset of points in our index binary trees, and thus require a lot of development of fast intersections between relational queries and queries on our index trees.

You can see how a query might be made: use API 4. to make a filter. Use API 3. to draw the timeseries on the results page. Provide an additional link for each result that uses API 5. to compute the similarity, showing the results using API 3. again. We can also support a separate uploaded query using 6 and show the results. (The only remaining thread there is how to set things up to display the query timeseries which is NOT part of the database. The answer is to use the same code on the browser side that you used to display the time series earlier: this will ensure that your JS code is also modular.)

Too keep things not too onerous, we'll support only one query workflow. 

Write a single-page UI which takes either a time-series id or an uploaded time series file (the latter can be supported using AJAX file upload (google it) to our `REST` endpoint, or my creating a new flask endpoint which takes HTML POST file uploads (google it too) on the server and calls tha appropriate python code directly, bypassing the REST API).

In either case draw the target curve (using a javascript library like `flot`, see http://www.flotcharts.org), compute the 5 most similar time series, and return and display them using AJAX(`$.ajax`) with their metadata (you can use a `IN` query on the ids of the time series).
