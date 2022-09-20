# Homework Simulation Chapter 7

## Question 1

> Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

**Answer**

Responses from `./scheduler.py -j 3 -l 200,200,200 -p SJF -c` and `./scheduler.py -j 3 -l 200,200,200 -p FIFO -c` are same because each job has the same length:

```
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

## Question 2

Now do the same but with jobs of different lengths: 100, 200, and 300.

**Answer**

Run `./scheduler.py -j 3 -l 100,200,300 -p SJF -c` :

```
Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

Run `./scheduler.py -j 3 -l 100,200,300 -p FIFO -c` :

```
Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

We can see the result is the same as the job comes in the shortest first order.

## Question 3

Now do the same, but also with the RR scheduler and a time-slice of 1.

**Answer**

Run `./scheduler.py -j 3 -l 100,200,300 -p RR -q 1 -c`:

```
Final statistics:
  Job   0 -- Response: 0.00  Turnaround 298.00  Wait 198.00
  Job   1 -- Response: 1.00  Turnaround 499.00  Wait 299.00
  Job   2 -- Response: 2.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 1.00  Turnaround 465.67  Wait 265.67
```

We can see that the response time can dramatically better (from 133 to 1 second) but the turnaround and wait time worsen a lot.

## Question 4

For what types of workloads does SJF deliver the same turnaround times as FIFO?

**Answer**
If the job order comes in the order of shorter job comes first. (e.g. `-j 100,200,300`.)

## Question 5

ForwhattypesofworkloadsandquantumlengthsdoesSJFdeliver the same response times as RR?

**Answer**

If each workload's running time is smaller than the quantum, then SJF will be the same as RR.

## Question 6

What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

**Answer**
The average response time with SJF will increase as the job lengths increase, because the later jobs will need to wait longer.

For example:

`./scheduler.py -j 3 -l 300,300,300 -p SJF -c `: Average -- Response: 300.00 Turnaround 600.00 Wait 300.00

`./scheduler.py -j 5 -l 300,300,300,300,300 -p SJF -c`: Average -- Response: 600.00 Turnaround 900.00 Wait 600.00

## Question 7

What happens to response time with RR as quantum lengths in- crease? Can you write an equation that gives the worst-case response time, given N jobs?

**Answer**

The response time will increase as the quantum lengths increase.

The worst case response time = min(quantum length, max(job lengths for N jobs))
