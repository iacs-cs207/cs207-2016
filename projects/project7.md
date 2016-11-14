---
title: Vantage Point calculations and database
layout: lecture
mathjax: true
---

Part 1 of this will be graded at milestone 2, due 11.59PM, 30th November, and must be implemented for your **paired** team. The idea behind this is that you get a grade on how good we think you implemented code for your paired team.

Part 2 of this builds on part 1, but we dont want to included it in the **paired** grading as we dont want any work on milestone 2 to be held up because of circumstances not within your control. For this part 2, you dont have to use your **paired** team's implementation if you dont want to...you can use your own; but if you do so you must argue why you made this choice... 

Part 2 will be out tomorrow (but is not due at milestone 2)

## Part 1

The job of Part 1, project 7 is to write code to calculate distances from vantage points which you can then use to do similarity search, and put these distances in a (non-balanced) Binary Search Tree database (on the lines of what we did in lab).

1. Assume that your time series has periodic boundary conditions with equal spacing on [0,1]. We have provided two example time series: 

[169975.dat_folded](https://dl.dropboxusercontent.com/u/75194/169975.dat_folded), [51886.dat_folded](https://dl.dropboxusercontent.com/u/75194/51886.dat_folded)

Interpolate these from 0.01 to 0.99 with 1024 points to set up a regular sampling.

For this part you can use anything that follows the sized-time-series interface.

2. Standardize the time series (subtract the mean and divide by the standard deviation)

3. Calculate the cross-correlation

4. Compute the kernelized cross-correlation as talked so that we can get a real distance. The equation for the kernelized cross correlation is given at
 http://www.cs.tufts.edu/~roni/PUB/ecml09-tskernels.pdf . Normalize the kernel there by $\sqrt(K(x,x)K(y,y))$ so that the correlation of a time series with itself is 1.
 
Here is some skeleton code you might find useful, especially to demo to yourself and as a basis for tests:

```python
import numpy.fft as nfft
import numpy as np
#below is your module. Use your ListTimeSeries or ArrayTimeSeries..
import timeseries as ts
from scipy.stats import norm

def tsmaker(m, s, j):
    t = np.arange(0.0, 1.0, 0.01)
    v = norm.pdf(t, m, s) + j*np.random.randn(100)
    return ts.TimeSeries(t, v)

def random_ts(a):
    t = np.arange(0.0, 1.0, 0.01)
    v = a*np.random.random(100)
    return ts.TimeSeries(t, v)

def stand(x, m, s):
    "standardize timeseries x my mean m and std deviation s"
    #your code here

def ccor(ts1, ts2):
    "given two standardized time series, compute their cross-correlation using FFT"
    #your code here


# this is just for checking the max correlation with the
#kernelized cross-correlation
def max_corr_at_phase(ts1, ts2):
    ccorts = ccor(ts1, ts2)
    idx = np.argmax(ccorts)
    maxcorr = ccorts[idx]
    return idx, maxcorr

#The equation for the kernelized cross correlation is given at
#http://www.cs.tufts.edu/~roni/PUB/ecml09-tskernels.pdf
#normalize the kernel there by np.sqrt(K(x,x)K(y,y)) so that the correlation
#of a time series with itself is 1. We'll set the default multiplier to 1.
def kernel_corr(ts1, ts2, mult=1):
    "compute a kernelized correlation so that we can get a real distance"
    #your code here.


#this is for a quick and dirty test of these functions
if __name__ == "__main__":
    print("HI")
    t1 = tsmaker(0.5, 0.1, 0.01)
    t2 = tsmaker(0.5, 0.1, 0.01)
    print(t1.mean(), t1.std(), t2.mean(), t2.std())
    import matplotlib.pyplot as plt
    plt.plot(t1)
    plt.plot(t2)
    plt.show()
    standts1 = stand(t1, t1.mean(), t1.std())
    standts2 = stand(t2, t2.mean(), t2.std())

    idx, mcorr = max_corr_at_phase(standts1, standts2)
    print(idx, mcorr)
    sumcorr = kernel_corr(standts1, standts2, mult=10)
    print(sumcorr)
    t3 = random_ts(2)
    t4 = random_ts(3)
    plt.plot(t3)
    plt.plot(t4)
    plt.show()
    standts3 = stand(t3, t3.mean(), t3.std())
    standts4 = stand(t4, t4.mean(), t4.std())
    idx, mcorr = max_corr_at_phase(standts3, standts4)
    print(idx, mcorr)
    sumcorr = kernel_corr(standts3, standts4, mult=10)
    print(sumcorr)
```

5. Use the code you just wrote and the code above to generate (using `tsmaker`) a set of 1000 time
series, each stored in a file. You should have one script for these.

6. We'll use the unbalanced binary search tree from lab10 (wrapped into a database as suggested in project 6), with one key-value tree-index one for each vantage point, to make really fast similarity searches. Randomly chose 20 vantage points, and create 20 database indexes. You should have another script for this

7. Write a command-line program which takes the name of a new data file as input, and returns the name of an existing data file whose time series is the most similar. Remember that the new timeseries's similarity against the vantage points needs to be calculated.

Thus the op you are supporting is: take an input light curve and compare it against your database. Find the top-n (say 10) similar light curves and return their ids.

Remember, for milestone 2, this database needs only to work as a library, which carries out its work in a manner to sqlite: multiple processes may access the database at the same time. Remember that you are basing this off lab10, where simultaneous reads are allowed, but simultaneous writes are not. We wont worry about atomicity or isolation here, and there is no transaction manager; but multiple instances of the command line program may be accessing this database at the same time.

## Part 2

coming tomorrow...




