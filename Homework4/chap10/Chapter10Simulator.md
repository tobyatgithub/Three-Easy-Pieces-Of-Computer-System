# Homework Simulation Chapter 10 Multiprocessor Scheduling

## Question 1

> To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a run-time of 30, and a working-set size of 200. Run this job (called job ’a’ here) on one simulated CPU as follows: ./multi.py -n 1 -L a:30:200. How long will it take to complete? Turn on the -c flag to see a final answer, and the -t flag to see a tick-by-tick trace of the job and how it is scheduled.

**Answer:**

`./multi.py -n 1 -L a:30:200 -c`: as expected, the job finishes in time 30. Here is a simple situation, we only have 1 cpu and 1 job ~~without needing to consider cache size~~.

## Question 2

> Now increase the cache size so as to make the job’s working set (size=200) fit into the cache (which, by default, is size=100); for example, run ./multi.py -n 1 -L a:30:200 -M 300. Can you predict how fast the job will run once it fits in cache? (hint: remember the key parameter of the warm rate, which is set by the -r flag) Check your answer by running with the solve flag (-c) enabled.

**Answer:**

`./multi.py -n 1 -L a:30:200 -M 300 -c -t`: hmmm it finishes in time 20. Interesting, this is due to the cache and the "warm rate" we set.

## Question 3

> One cool thing about `multi.py` is that you can see more detail about what is going on with different tracing flags. Run the same simulation as above, but this time with time left tracing enabled (-T). This flag shows both the job that was scheduled on a CPU at each time step, as well as how much run-time that job has left after each tick has run. What do you notice about how that second column decreases?

**Answer:**

## Question

> QQQ

**Answer:**

## Question

> QQQ

**Answer:**

## Question

> QQQ

**Answer:**

## Question

> QQQ

**Answer:**

## Question

> QQQ

**Answer:**

## Question

> QQQ

**Answer:**
