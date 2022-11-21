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

`./multi.py -n 1 -L a:30:200 -M 300 -c -T`: start from time 10, the cpu/cache is "warm" and thus it is executing the job 2x faster.

## Question 4

> Now add one more bit of tracing, to show the status of each CPU cache for each job, with the -C flag. For each job, each cache will either show a blank space (if the cache is cold for that job) or a ’w’ (if the cache is warm for that job). At what point does the cache become warm for job ’a’ in this simple example? What happens as you change the warmup time parameter (-w) to lower or higher values than the default?

**Answer:**

`./multi.py -n 1 -L a:30:200 -M 300 -C -w 20`

The job becomes "warm" at time 10 by default, and this value can be tuned by `-w` parameter, where `-w` is the value for which the job will change from cold to warm.

## Question 5

> At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t this a multi-processor CPU scheduling chapter? Oh yeah! So let’s start working with multiple jobs. Specifically, let’s run the following three jobs on a two-CPU system (i.e., type ./multi.py -n 2 -L a:100:100,b:100:50,c:100:50) Can you predict how long this will take, given a round-robin centralized scheduler? Use -c to see if you were right, and then dive down into details with -t

**Answer:**

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50`: due to the centralized round robin scheduler, the program wasn't able to take advantage of the cache (no cache affinity) and finished (100 + 100 + 100) / 2 = 150 time.

## Question 6

> Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. To do this, you’ll need the -A flag. This flag can be used to limit which CPUs the scheduler can place a particular job upon. In this case, let’s use it to place jobs ’b’ and ’c’ on CPU 1, while restricting ’a’ to CPU 0. This magic is accomplished by typing this ./multi.py -n 2 -L a:100:100,b:100:50, c:100:50 -A a:0,b:1,c:1 ; don’t forget to turn on various tracing options to see what is really happening! Can you predict how fast this version will run? Why does it do better? Will other combinations of ’a’, ’b’, and ’c’ onto the two processors run faster or slower?

**Answer:**

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -C -T`: as expected, the jobs run much faster now given the cache affinity. Job a finishes at time 54 on cpu0, and job2 & 3 finishes at time 109 on cpu1.

The reason for this is that now all the jobs can take advantage of the "warm" status of cache, and thus run 2x fast after it warms up.

I think other combinations will be slower than this setting, bcz of the working set sizes. If we combine a with any job, the size will be larger than the cache size (thus hurting the warm acceleration.)

## Question 7

> One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speed up of jobs when using multiple CPUs (and their caches) as compared to running jobs on a single processor. Specifically, when you run on N CPUs, sometimes you can speed up by more than a factor of N, a situation entitled super-linear speedup. To experiment with this, use the job description here (-L a:100:100,b:100:100,c:100:100) with a small cache (-M 50) to create three jobs. Run this on systems with 1, 2, and 3 CPUs (-n1,-n2,-n3). Now, do the same, but with a larger per-CPU cache of size 100. What do you notice about performance as the number of CPUs scales? Use -c to confirm your guesses, and other tracing flags to dive even deeper.

**Answer:**

`./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 50 -C -T`: finishes at time 100 = (100 + 100 + 100) / 3

`./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 100 -C -T`: finishes at time 54

cache warm up for the win!

## Question 8

> One other aspect of the simulator worth studying is the per-CPU scheduling option, the -p flag. Run with two CPUs again, and this three job configuration (-L a:100:100,b:100:50,c:100:50). How does this option do, as opposed to the hand-controlled affinity limits you put in place above? How does performance change as you alter the ’peek interval’ (-P) to lower or higher values? How does this per-CPU approach work as the number of CPUs scales?

**Answer:**

With 2 CPUs:

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -p -C -T`: finishes at time 99

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -p -P 5 -C -T`: finishes at time 89

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -p -P 2 -C -T`: finishes at time 89

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -p -P 20 -C -T`: finishes at time 99

-> the lower the p value is, the better the cpu policy can take advantage of the cache affinity.

With 3 CPUs:

`./multi.py -n 3 -L a:100:100,b:100:50,c:100:50 -p -C -T`: finishes at time 54

`./multi.py -n 3 -L a:100:100,b:100:50,c:100:50 -p -P 5 -C -T`: finishes at time 54

`./multi.py -n 3 -L a:100:100,b:100:50,c:100:50 -p -P 2 -C -T`: finishes at time 54

`./multi.py -n 3 -L a:100:100,b:100:50,c:100:50 -p -P 20 -C -T`: finishes at time 54

-> It scales proportionally with more number of CPUs (the more CPUs, the more running queues and less need for switching, thus more cache affinity and warm accelerations)

## Question 9

> Finally, feel free to just generate random workloads and see if you can predict their performance on different numbers of processors, cache sizes, and scheduling options. If you do this, you’ll soon be a multi-processor scheduling master, which is a pretty awesome thing to be. Good luck!

**Answer:**

`./multi.py -n 3 -j 5 -p -C -T`
