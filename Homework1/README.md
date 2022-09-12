# Homework 1

## Question 1:

> Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.

**Answer**:

The CPU will run the two jobs in sequence (i.e. run job1, wait until finished, and then run job2.)

And the CPU utilization shall be 100% as here we only run CPU jobs (as both job use "5:100" flag which indicates 100% cpu job.)

Result of `./process-run.py -l 5:100,5:100 -c -p`:

```
Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
```

## Question 2:

> Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p to find out if you were right.

**Answer**:

It shall take 4 clock time to complete job1, and 2 clock time to complete job 2 (run io and run io_done) assuming i/o initiation and completion only takes 1 clock time for simplicity.
-> well... correction: it turns out that the `-L` is 5 by default if not specified (which means any I/O job will at least take 5 clock time + initiation + completion). Thus the total time used is 4 + 5 + 1 + 1 = 11

Result of `./process-run.py -l 4:100,1:0 -c -p`:

```
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1
  2        RUN:cpu         READY             1
  3        RUN:cpu         READY             1
  4        RUN:cpu         READY             1
  5           DONE        RUN:io             1
  6           DONE       WAITING                           1
  7           DONE       WAITING                           1
  8           DONE       WAITING                           1
  9           DONE       WAITING                           1
 10           DONE       WAITING                           1
 11*          DONE   RUN:io_done             1

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)
```

## Question 3:

> Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)

**Answer**:

It matters! The reason being that if we run the I/O task (1:0) first, we will be able to run the second non-I/O job (4:100) while the cpu is waiting for the first I/O job. Thus saving a lot of times and efficiency.

Result of `./process-run.py -l 1:0,4:100 -c -p`:

```
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        WAITING       RUN:cpu             1             1
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)

```

## Question 4

> We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH_ON_END), one doing I/O and the other doing CPU work?

**Answer**:
As we see from question 3, the switching helped a lot compared to question 2. If we ban the switch here, we will just get the same result from question s. As confirmed by running the `./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END -p -c`:

```
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        WAITING         READY                           1
  3        WAITING         READY                           1
  4        WAITING         READY                           1
  5        WAITING         READY                           1
  6        WAITING         READY                           1
  7*   RUN:io_done         READY             1
  8           DONE       RUN:cpu             1
  9           DONE       RUN:cpu             1
 10           DONE       RUN:cpu             1
 11           DONE       RUN:cpu             1

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)
```

## Question 5

> Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH_ON_IO). What happens now? Use -c and -p to confirm that you are right.

**Answer**:

We shall get the same result from question 3, the cpu will switch to another task when waiting on the I/O to finish.

Results of `./process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO -p -c`:

```
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1
  2        WAITING       RUN:cpu             1             1
  3        WAITING       RUN:cpu             1             1
  4        WAITING       RUN:cpu             1             1
  5        WAITING       RUN:cpu             1             1
  6        WAITING          DONE                           1
  7*   RUN:io_done          DONE             1

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)
```

## Question 6

> One other important behavior is what to do when an I/O completes. With -I IO_RUN_LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p) Are system resources being effectively utilized?

**Answer**:
As described in the `-I` flag:

- the I/O job (3:0) will run first
- while cpu waiting on the I/O job to finish, it will kick start the cpu job (5:100)
- since the `-I` is set to io run later, the I/O job will wait until the cpu job finishes to run the io_done
- however (??), it turns out that the io job will keep waiting until all cpu jobs (there are three 5:100 cpu jobs) to finish to resume.

Result from `./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p`

```
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1
  8          READY          DONE       RUN:cpu         READY             1
  9          READY          DONE       RUN:cpu         READY             1
 10          READY          DONE       RUN:cpu         READY             1
 11          READY          DONE       RUN:cpu         READY             1
 12          READY          DONE          DONE       RUN:cpu             1
 13          READY          DONE          DONE       RUN:cpu             1
 14          READY          DONE          DONE       RUN:cpu             1
 15          READY          DONE          DONE       RUN:cpu             1
 16          READY          DONE          DONE       RUN:cpu             1
 17    RUN:io_done          DONE          DONE          DONE             1
 18         RUN:io          DONE          DONE          DONE             1
 19        WAITING          DONE          DONE          DONE                           1
 20        WAITING          DONE          DONE          DONE                           1
 21        WAITING          DONE          DONE          DONE                           1
 22        WAITING          DONE          DONE          DONE                           1
 23        WAITING          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1
 25         RUN:io          DONE          DONE          DONE             1
 26        WAITING          DONE          DONE          DONE                           1
 27        WAITING          DONE          DONE          DONE                           1
 28        WAITING          DONE          DONE          DONE                           1
 29        WAITING          DONE          DONE          DONE                           1
 30        WAITING          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)
```

## Question7

> Now run the same processes, but with -I IO_RUN_IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?

**Answer**:

The behavior will be much different! The I/O init and completion will now kick in immediately. This is very beneficial as:
1 - it will greatly improve the cpu stats and io stats (much higher efficiency) because we are utilizing the cpu while waiting on the I/O for as many I/O tasks as possible. (Different from question 6 where only the first I/O task gets to take this advantage.)
2 - the I/O task might update some files in hardware and might influence the result of the cpu job. Thus finish that I/O job earlier could make the cpu task result more accurate.

Result from `./process-run.py -l 3:0,6:100,6:100,6:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p`:

```
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1
  2        WAITING       RUN:cpu         READY         READY             1             1
  3        WAITING       RUN:cpu         READY         READY             1             1
  4        WAITING       RUN:cpu         READY         READY             1             1
  5        WAITING       RUN:cpu         READY         READY             1             1
  6        WAITING       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done         READY         READY         READY             1
  8         RUN:io         READY         READY         READY             1
  9        WAITING       RUN:cpu         READY         READY             1             1
 10        WAITING          DONE       RUN:cpu         READY             1             1
 11        WAITING          DONE       RUN:cpu         READY             1             1
 12        WAITING          DONE       RUN:cpu         READY             1             1
 13        WAITING          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE         READY         READY             1
 15         RUN:io          DONE         READY         READY             1
 16        WAITING          DONE       RUN:cpu         READY             1             1
 17        WAITING          DONE       RUN:cpu         READY             1             1
 18        WAITING          DONE          DONE       RUN:cpu             1             1
 19        WAITING          DONE          DONE       RUN:cpu             1             1
 20        WAITING          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE         READY             1
 22           DONE          DONE          DONE       RUN:cpu             1
 23           DONE          DONE          DONE       RUN:cpu             1
 24           DONE          DONE          DONE       RUN:cpu             1

Stats: Total Time 24
Stats: CPU Busy 24 (100.00%)
Stats: IO Busy  15 (62.50%)
```
