# Chapter 29 Threads and Locks usage

In this homework, you’ll gain some experience with writing concurrent code and measuring its performance. Learning to
build code that performs well is a critical skill and thus gaining a little experience here with it is quite worthwhile.

## Question 1

> We’ll start by redoing the measurements within this chapter. Use the call `gettimeofday()` to measure time within your
> program. How accurate is this timer? What is the smallest interval it can measure? Gain confidence in its workings, as
> we will need it in all subsequent questions. You can also look into other timers, such as the cycle __counter_t available on
> x86 via the `rdtsc` instruction.

**Answer**

`gettimeofday` can measure second and microsecond. 

My mac has 8 cores and pc has 9 cores. 

## Question 2

> Now, build a simple concurrent __counter_t and measure how long it takes to increment the __counter_t many times as the number of threads increases. How many CPUs are available on the system you are using? Does this number impact your measurements at all?

**Answer**
See in `simpleCounter.cpp`. And it turns out that increase amount of thread may not necessarily help the performance.

## Question 3

>Next, build a version of the sloppy __counter_t. Once again, measure its performance as the number of threads varies, as well as the threshold. Do the numbers match what you see in the chapter?

**Answer**

See in `sloppyCounter.cpp`, and here are few of the results:
```
1 threads, 2 threshold
100000 global counter
Time (seconds): 0.023110

2 threads, 2 threshold
200000 global counter
Time (seconds): 0.080130

1 threads, 4 threshold
100000 global counter
Time (seconds): 0.019870

2 threads, 4 threshold
200000 global counter
Time (seconds): 0.062700

1 threads, 8 threshold
100000 global counter
Time (seconds): 0.019440

2 threads, 8 threshold
200000 global counter
Time (seconds): 0.057390

1 threads, 32 threshold
100000 global counter
Time (seconds): 0.022750

2 threads, 32 threshold
200000 global counter
Time (seconds): 0.056620
```


## Question 4

> Build a version of a linked list that uses hand-over-hand locking[[MS04](https://www.cs.tau.ac.il/~shanir/concurrent-data-structures.pdf)], as cited in the chapter. You should read the paper first to understand how it works, and then implement it. Measure its performance. When does a hand-over-hand list work better than a standard list as shown in the chapter?

**Answer**

See `concurrentLinkedList.cpp` and Humm... based on the textbook, the hand-over-hand locking seems barely overperform a standard list with a lock?


## Question 5

> Pick your favorite interesting data structure, such as a B-tree or other slightly more interested structure. Implement it, and start with a simple locking strategy such as a single lock. Measure its performance as the number of concurrent threads increases.

**Answer**

## Question 6

>  Finally, think of a more interesting locking strategy for this favorite data structure of yours. Implement it, and measure its performance. How does it compare to the straightforward locking approach?

**Answer**