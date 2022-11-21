# Homework Simulation Chapter 17 Free Space Management

## Question 1

> First run with the flags `-n 10 -H 0 -p BEST -s 0` to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?

**Answer:**

`./malloc.py -n 10 -H 0 -p BEST -s 0 -c`

```
ptr[5] = Alloc(7) returned 1008 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]
```

The free list will become very fragmentic over time (internal fragmentation.)

## Question 2

> How are the results different when using a WORST fit policy to search the freelist(`-p WORST`)? What changes?

**Answer:**

`./malloc.py -n 10 -H 0 -p WORST -s 0 -c`

```
ptr[5] = Alloc(7) returned 1026 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1033 sz:67 ]
```

Even worse and we will end up with more fragments, bcz each time the program will cut off from the biggest chunk (thus not reusing the smaller chunks who happen to have the exact same size.)

## Question 3

> What about when using FIRST fit `(-p FIRST`)? What speeds up when you use first fit?

**Answer:**

`./malloc.py -n 10 -H 0 -p FIRST -s 0 -c`

```
ptr[5] = Alloc(7) returned 1008 (searched 3 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]
```

We will search less elements (thus quicker allocation.)

## Question 4

> For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings(`-l ADDRSORT,-l SIZESORT+,-l SIZESORT-`) to see how the policies and the list orderings interact.

**Answer:**
`./malloc.py -p FIRST -l ADDRSORT -s 0 -c`

```
ptr[5] = Alloc(7) returned 1008 (searched 3 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]
```

`./malloc.py -p FIRST -l SIZESORT+ -s 0 -c`

```
ptr[5] = Alloc(7) returned 1008 (searched 3 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]
```

`./malloc.py -p FIRST -l SIZESORT- -s 0 -c`

```
ptr[5] = Alloc(7) returned 1026 (searched 1 elements)
Free List [ Size 5 ]: [ addr:1033 sz:67 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1003 sz:5 ][ addr:1000 sz:3 ]
```

The order of the size do affect the policy quite a bit.

## Question 5

> Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?

**Answer:**

`./malloc.py -n 1000 -r 30 -c` With out coalescing, many request will be out of luck (return -1). And it gets worse with larger allocation requests over time.

```
ptr[736] = Alloc(26) returned -1 (searched 31 elements)
Free List [ Size 31 ]: [ addr:1000 sz:4 ][ addr:1004 sz:4 ][ addr:1016 sz:2 ][ addr:1018 sz:5 ][ addr:1023 sz:9 ][ addr:1032 sz:1 ][ addr:1033 sz:1 ][ addr:1034 sz:1 ][ addr:1035 sz:5 ][ addr:1040 sz:1 ][ addr:1041 sz:1 ][ addr:1042 sz:3 ][ addr:1045 sz:1 ][ addr:1046 sz:10 ][ addr:1056 sz:1 ][ addr:1057 sz:1 ][ addr:1058 sz:1 ][ addr:1059 sz:2 ][ addr:1061 sz:1 ][ addr:1062 sz:2 ][ addr:1064 sz:7 ][ addr:1071 sz:1 ][ addr:1072 sz:10 ][ addr:1082 sz:1 ][ addr:1083 sz:1 ][ addr:1084 sz:1 ][ addr:1085 sz:1 ][ addr:1086 sz:4 ][ addr:1090 sz:6 ][ addr:1096 sz:1 ][ addr:1097 sz:3 ]
```

`./malloc.py -n 1000 -r 30 -c -C` Coalescing is marvelous!

```
Free(ptr[540])
returned 0
Free List [ Size 1 ]: [ addr:1000 sz:100 ]
```

## Question 6

> What happens when you change the percent allocated fraction `-P` to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?

**Answer:**
`./malloc.py -c -n 100 -P 100`

More allocation percentage = less free percentage = more space occupied and never released.

`./malloc.py -c -n 1000 -P 1`

More free without coalescing is not much better -> a lot of fragments.

## Question 7

> What kind of specific requests can you make to generate a highly-fragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.

**Answer:**
`./malloc.py -c -A +2,+2,+2,+2,+2,...+2,-0,-1,-2,-3...`

different policies and options won't change much EXCEPT `-C`.
