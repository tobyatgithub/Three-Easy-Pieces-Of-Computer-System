# Homework Simulation for Chap 8

With `mlfq.py`:


## Question 1

> Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

**Answer**

`./mlfq.py -n 2 -j 2 -M 0 -m 200 -c`

## Question 2

> How would you run the scheduler to reproduce each of the examples in the chapter?

**Answer**

Example 1, A single long running job: `./mlfq.py --jlist 0,200,0 -q 10 -c`

Example 2, Along Came a Short job: `./mlfq.py --jlist 0,180,0:100,20,0 -q 10 -c`
Example 3, What about I/O: `./mlfq.py --jlist 0,180,0:50,20,1 -q 10 -c` (not super sure how z is defined in x,y,z. but the graph looks like this one.)

## Question 3

> How would you configure the scheduler parameters to behave just like a round-robin scheduler?

**Answer**

Reduce the quantum parameter `-q` will make the scheduler behave more like a round-robin.

## Question 4

>  Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

**Answer**

`./mlfq.py --jlist 0,200,0:50,150,9 -S -q 10 -S -i 1 -c`

Seems to be more like it. The second job will request I/O every 9 timesteps where the `-q` is set to 10 to game the system.

## Question 5

> Given a system with a quantum length of 10ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long- running (and potentially-starving) job gets at least 5% of the CPU?

**Answer**

5 % * B = 10 ms -> B = 200 ms

## Question 6

> One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.

**Answer**

`./mlfq.py --jlist 0,180,0:0,20,1:20,50,0 -q 10 -c` vs.
`./mlfq.py --jlist 0,180,0:0,20,1:20,50,0 -q 10 -c -I`

We can see that `-I` will put the job who just finiesd I/O to the top priority.