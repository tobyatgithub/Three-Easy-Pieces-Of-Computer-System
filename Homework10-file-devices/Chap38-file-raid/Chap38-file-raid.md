# Homework Simulation Chapter 38 Redundant Arrays of Inexpensive Disks (RAIDs)

This section introduces `raid.py`, a simple RAID simulator you can use to shore up your knowledge of how RAID systems work. See the README for details.

## Question 1

> Use the simulator to perform some basic RAID mapping tests. Run with different levels (0, 1, 4, 5) and see if you can figure out the mappings of a set of requests. For RAID-5, see if you can figure out the difference between left-symmetric and left-asymmetric layouts. Use some different random seeds to generate different problems than above.

**Answer:**

Using the formula:

```
disk   = address % number_of_disks
offset = address / number_of_disks
```

We can easily calculate the ones for RAID0

```
./raid.py -n 5 -L 0 -R 20 -c
./raid.py -n 5 -L 1 -R 20 -c
./raid.py -n 5 -L 4 -R 20 -c
```

```
./raid.py -n 9 LS -L 5 -R 20 -c -W seq
./raid.py -n 9 LA -L 5 -R 20 -c -W seq

left-symmetric    left-asymmetric
0 1 2 P           0 1 2 P
4 5 P 3           3 4 P 5
8 P 6 7           6 P 7 8
```

## Question 2

> Do the same as the first problem, but this time vary the chunk size with `-C`. How does chunk size change the mappings?

**Answer:**
The ordering will change accordingly, for example:

```
./raid.py -L 5 -5 LS -c -W seq -n 12

0  2  4  P
1  3  5  P
8 10  P  6
9 11  P  7
```

## Question 3

> Do the same as above, but use the `-r` flag to reverse the nature of each problem.

**Answer:**

`./raid.py -L 5 -5 LS -c -W seq -n 12 -r`

## Question 4

> Now use the reverse flag but increase the size of each request with the `-S` flag. Try specifying sizes of 8k, 12k, and 16k, while varying the RAID level. What happens to the underlying I/O pattern when the size of the request increases? Make sure to try this with the sequential workload too (`-W sequential`); for what request sizes are RAID-4 and RAID-5 much more I/O efficient?

**Answer:**

```
./raid.py -L 4 -S 4k -c -W seq -r
./raid.py -L 4 -S 8k -c -W seq
./raid.py -L 4 -S 12k -c -W seq
./raid.py -L 4 -S 16k -c -W seq
./raid.py -L 5 -S 4k -c -W seq
./raid.py -L 5 -S 8k -c -W seq
./raid.py -L 5 -S 12k -c -W seq
./raid.py -L 5 -S 16k -c -W seq
```

When request size increases, the file system will need to read more blocks to answer the request.

To make I/O efficient, I'm leaning towards say larger size because that will allow more parallelism.

## Question 5

> Use the timing mode of the simulator (`-t`) to estimate the performance of 100 random reads to the RAID, while varying the RAID levels, using 4 disks.

**Answer:**

```
./raid.py -L 0 -t -n 100 -c // 275.7
./raid.py -L 1 -t -n 100 -c // 278.7
./raid.py -L 4 -t -n 100 -c // 386.1
./raid.py -L 5 -t -n 100 -c // 276.7
```

## Question 6

> Do the same as above, but increase the number of disks. How does the performance of each RAID level scale as the number of disks increases?

**Answer:**

```
./raid.py -L 0 -t -n 100 -D 8 -c // 275.7 / 156.5 = 1.76
./raid.py -L 1 -t -n 100 -D 8 -c // 278.7 / 167.8 = 1.66
./raid.py -L 4 -t -n 100 -D 8 -c // 386.1 / 165.0 = 2.34
./raid.py -L 5 -t -n 100 -D 8 -c // 276.5 / 158.6 = 1.74
```

## Question 7

> Do the same as above, but use all writes (`-w 100`) instead of reads. How does the performance of each RAID level scale now? Can you do a rough estimate of the time it will take to complete the workload of 100 random writes?

**Answer:**

```
./raid.py -L 0 -t -c -w 100 // 40.8
./raid.py -L 1 -t -c -w 100 // 60.6
./raid.py -L 4 -t -c -w 100 // 101.0
./raid.py -L 5 -t -c -w 100 // 60.6

./raid.py -L 0 -t -c -w 100 -D 8// 40.8 / 30.3 = 1.35
./raid.py -L 1 -t -c -w 100 -D 8// 60.6 / 40.8 = 1.49
./raid.py -L 4 -t -c -w 100 -D 8// 101.0 / 101.0 = 1
./raid.py -L 5 -t -c -w 100 -D 8// 60.6 / 50.5 = 1.2
```

## Question 8

> Run the timing mode one last time, but this time with a sequential workload(`-W sequential`). How does the performance vary with RAID level, and when doing reads versus writes? How about when varying the size of each request? What size should you write to a RAID when using RAID-4 or RAID-5?

**Answer:**

```
./raid.py -L 0 -t -n 100 -c -W seq // 12.5
./raid.py -L 0 -t -w 100 -c -W seq // 10.3

./raid.py -L 1 -t -n 100 -c -W seq // 14.9
./raid.py -L 1 -t -w 100 -c -W seq // 10.5

./raid.py -L 4 -t -n 100 -c -W seq // 13.9
./raid.py -L 4 -t -w 100 -c -W seq // 10.4

./raid.py -L 5 -t -n 100 -c -W seq // 13.3
./raid.py -L 5 -t -w 100 -c -W seq // 10.4
```

```
./raid.py -L 4 -t -n 100 -c -W seq -S 8k // 16.7
./raid.py -L 4 -t -w 100 -c -W seq -S 8k // 10.7

./raid.py -L 4 -t -n 100 -c -W seq -S 12k // 20.0
./raid.py -L 4 -t -w 100 -c -W seq -S 12k // 11.0

./raid.py -L 5 -t -n 100 -c -W seq -S 8k // 16.7
./raid.py -L 5 -t -w 100 -c -W seq -S 8k // 10.7

./raid.py -L 5 -t -n 100 -c -W seq -S 12k // 20.0
./raid.py -L 5 -t -w 100 -c -W seq -S 12k // 11.0
```

When writing, the size increase has a very minimal effect on performance when writing to RAID-4 or RAID-5. Thus bigger size probably will be good (for example, 16k one time will take abt 11.4 seconds and 8k two times will take more then 20 seconds).
