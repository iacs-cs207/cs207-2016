---
title: Project
layout: default
---

## Final Project: Due date and expectations

The due date is 9am Wednesday 14 December 2016. We'll have presentations that day: at least one member from each group should be there!

What are the expectations for the final project?

- There are 3 database like systems in this project: The Storage manager and associated `SMTimeSeries`, the postgres database with metadata, and the socket server fronted red-black tree based Vantage Point database. All 3 of these talk to the REST HTTP server, which in turn is fronted by the web UI. The latter is not complete, but with just enough implementation to give you the experience of making a Web UI. Setting up the whole stack is a skill which will be very useful in your career.
- The Timeseries and Storage Manager parts should be usable independent of the rest of the system and should be `python setup.py install` installable. You dont have to make a direct-from-PyPI installable project, but the user ought to be able to download the module, do `python setup.py test`, see docs by doing `python setup.py docs`, and install by doing `python setup.py install`. (You could also use pip (not frpm PyPI), in which case make it directly installable from your github repo. (For this you'll have to separate the module out into its own github repo))
- Ditto for the code for the red-black tree. (I dont mean here the server, or the command line program, I mean just the red-black tree with floating point keys and ids as values). The command line program and server ought to use this as a module
- Thats all for modules for us. 
- The rest of the project should be automatically installable on AWS using a bash script to be run on the AWS machine; including all the python, postgres, nginx, etc provisioning after you have chosen an ubuntu image. 
- We will follow your instructions to run and test your code. Where possible use appropriate technologies in this install script, such as `pip -r requeirements.txt` and so on and so forth. The web page should show up at the DNS address that Amazon gives you.
- Documentation for every subsystem in the project should be provided. If needed, generate using PyScaffold. Link to the docs from the `README.md` in each folder. The top level `README.md` should contain an overview, links to other docs, and an installation guide which will help us install and test your system.
- For those parts of the project which are modules, `python setup.py test` should suffice. For all other parts, include instructions on how to test your code. Where possible, provide links to Travis-CI test runs and Coveralls coverage.