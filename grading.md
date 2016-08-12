---
title: Coursework and grading
layout: default
---

Project Milestone 1 details are [here](project.html).

## Working in groups

You will work in groups of 4 or 5. You can collaborate as much as you want within a group. You are not allowed to collaborate, unless expressly asked to, outside the group. This collaboration extends to both the labs and the project.

All github repos will be open. You may look at others labs after they are submitted, but not before. You may in general not look at other group's projects, even though the repos will be open, except for the code-review part talked about in "Participation" below. This works on the honor system: we are all adults here.

## Your grade

Your grade in this class is made up of the following components:

- **Labs** (30%)
    - Submission of all labs (15%): All 3 labs for a week must be submitted by 11.59pm of the Sunday of the week of the labs. The labs ought to be mostly complete if you come to the after lecture labs, needing very little work at home.
    - Random and Non-Random Evaluations (15%): In most labs, we will ask you to submit an answer from the lab via a google form. This will be used in evaluation. Additionally, some labs will be randomly chosen to grade

 - **Paper** (10%) At about the 4th or 5th week of the class, your group will be asked to choose an open source code base to review and like a paper about. For example, consider you choose sklearn's implementation of kNN. You will review the basic algorithms, implementing one of these in python. Then you will review the optimizations made by the project, whether these be pure C/C++ implementation, cython, or other. The idea is to understand and communicate (a) the algorithm (b) the optimization and why (c) how the optimization was implemented.

- **Project** (50%). The project is to create a time-series analysis library and database with a REST API to it.

The deliverables will be:

- (a) code for library
- (b) code for database
- (c) a database with a REST API to analyze/add/etc time series in this database; with tests exercising this API
- (d) a simple demo of these API endpoints from a web page
- (e) documentation of the library and the API at a web site. These should be a combination of written and automatically generated documentation.

A portion of this project is what we call "basic" and must be implemented by each group. Simpler versions of some of the code in this basic part will be played around with in the labs after class. The basic part is worth 30% and consists of **two milestones** at which you will be graded as a group. M1 will be graded in the spring break and is due the sunday night 11.59pm before that. M2 will be graded in the week of April 18th and once again is due on sunday night at 11.59pm on the sunday night before that week.

Another portion of the project is what we call "additional" and consists of the additional features you add to the library or the database. These might be different distance algorithms (between time series), an tick-database extension to the search database, etc. Your imagination is the limit. Start thinking about this immediately after Milestone M1 and discuss with your TF. This part is worth 20%.

- **Participation** (10%)

 The final 10% of your grade comes from participation.

The first part of participations comes from your presence in online discussions, individual commits, and via a within-group peer review. This is to ensure that certain team members dont slack off.

The second is more complex.

 We will divide groups into "red" groups and "black" groups. (See Red-Black trees.). In the first milestone, a red group will contribute one feature (to be decided) to a black groups codebase. Similarly, a black group will contribute another feature to a red group's codebase. This contribution will be made via a github pull request. The contributee will conduct a **code review**, and request changes. Such discussion will take place via issues and pull requests on github. When satisfied, the contributor will merge the feature into their code base.

 The contributor group's contributions will be taken into account in their project grade (the basic part). The discussions and code review: the entire back and forth will contribute to both color's participation grade.


**Peer-review may be used at the end to adjust ENTIRE individual grades up or down.**

## Workflow

The work for this course will be done on github.

Each user must have a repo: cs207labs.

Each group will have an organization, with its members and the teaching staff in it. The organization will be called "cs207_groupname", and the project repo will be called "project". The group is free to make other repos, etc for experiments, but "project" is the one we will grade.

The lectures and labs will be available from https://github.com/iacs-cs207/cs207 .
