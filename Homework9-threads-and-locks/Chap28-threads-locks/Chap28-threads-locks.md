# Homework Simulation Chapter 28 Threads and Locks

This program, `x86.py`, allows you to see how different thread interleavings either cause or avoid race conditions. See the README for details on how the program works and answer the questions below.

## Question 1

> Examine `flag.s`. This code “implements” locking with a single memory flag. Can you understand the assembly?

**Answer:**

Mostly seems fair. Not very sure about the `.var`. Seems like variable declaration.

## Question 2

> When you run with the defaults, does `flag.s` work? Use the `-M` and `-R` flags to trace variables and registers (and turn on `-c` to see their values). Can you predict what value will end up in `flag`?

**Answer:**

```
./x86.py -p flag.s -M flag,count -R ax,bx -c
ARG seed 0
ARG numthreads 2
ARG program flag.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched
ARG argv
ARG load address 1000
ARG memsize 128
ARG memtrace flag,count
ARG regtrace ax,bx
ARG cctrace False
ARG printstats False
ARG verbose False


 flag count      ax    bx          Thread 0                Thread 1

    0     0       0     0
    0     0       0     0   1000 mov  flag, %ax
    0     0       0     0   1001 test $0, %ax
    0     0       0     0   1002 jne  .acquire
    1     0       0     0   1003 mov  $1, flag
    1     0       0     0   1004 mov  count, %ax
    1     0       1     0   1005 add  $1, %ax
    1     1       1     0   1006 mov  %ax, count
    0     1       1     0   1007 mov  $0, flag
    0     1       1    -1   1008 sub  $1, %bx
    0     1       1    -1   1009 test $0, %bx
    0     1       1    -1   1010 jgt .top
    0     1       1    -1   1011 halt
    0     1       0     0   ----- Halt;Switch -----  ----- Halt;Switch -----
    0     1       0     0                            1000 mov  flag, %ax
    0     1       0     0                            1001 test $0, %ax
    0     1       0     0                            1002 jne  .acquire
    1     1       0     0                            1003 mov  $1, flag
    1     1       1     0                            1004 mov  count, %ax
    1     1       2     0                            1005 add  $1, %ax
    1     2       2     0                            1006 mov  %ax, count
    0     2       2     0                            1007 mov  $0, flag
    0     2       2    -1                            1008 sub  $1, %bx
    0     2       2    -1                            1009 test $0, %bx
    0     2       2    -1                            1010 jgt .top
    0     2       2    -1                            1011 halt
```

## Question 3

> Change the value of the register `%bx` with the `-a` flag(e.g., `-a bx=2,bx=2` if you are running just two threads). What does the code do? How does it change your answer for the question above?

**Answer:**

`./x86.py -p flag.s -a bx=2,bx=2 -M flag,count -R ax,bx -c`

Each thread will run twice, count will become 4.

```
flag count      ax    bx          Thread 0                Thread 1

    0     0       0     2
    0     0       0     2   1000 mov  flag, %ax
    0     0       0     2   1001 test $0, %ax
    0     0       0     2   1002 jne  .acquire
    1     0       0     2   1003 mov  $1, flag
    1     0       0     2   1004 mov  count, %ax
    1     0       1     2   1005 add  $1, %ax
    1     1       1     2   1006 mov  %ax, count
    0     1       1     2   1007 mov  $0, flag
    0     1       1     1   1008 sub  $1, %bx
    0     1       1     1   1009 test $0, %bx
    0     1       1     1   1010 jgt .top
    0     1       0     1   1000 mov  flag, %ax
    0     1       0     1   1001 test $0, %ax
    0     1       0     1   1002 jne  .acquire
    1     1       0     1   1003 mov  $1, flag
    1     1       1     1   1004 mov  count, %ax
    1     1       2     1   1005 add  $1, %ax
    1     2       2     1   1006 mov  %ax, count
    0     2       2     1   1007 mov  $0, flag
    0     2       2     0   1008 sub  $1, %bx
    0     2       2     0   1009 test $0, %bx
    0     2       2     0   1010 jgt .top
    0     2       2     0   1011 halt
    0     2       0     2   ----- Halt;Switch -----  ----- Halt;Switch -----
    0     2       0     2                            1000 mov  flag, %ax
    0     2       0     2                            1001 test $0, %ax
    0     2       0     2                            1002 jne  .acquire
    1     2       0     2                            1003 mov  $1, flag
    1     2       2     2                            1004 mov  count, %ax
    1     2       3     2                            1005 add  $1, %ax
    1     3       3     2                            1006 mov  %ax, count
    0     3       3     2                            1007 mov  $0, flag
    0     3       3     1                            1008 sub  $1, %bx
    0     3       3     1                            1009 test $0, %bx
    0     3       3     1                            1010 jgt .top
    0     3       0     1                            1000 mov  flag, %ax
    0     3       0     1                            1001 test $0, %ax
    0     3       0     1                            1002 jne  .acquire
    1     3       0     1                            1003 mov  $1, flag
    1     3       3     1                            1004 mov  count, %ax
    1     3       4     1                            1005 add  $1, %ax
    1     4       4     1                            1006 mov  %ax, count
    0     4       4     1                            1007 mov  $0, flag
    0     4       4     0                            1008 sub  $1, %bx
    0     4       4     0                            1009 test $0, %bx
    0     4       4     0                            1010 jgt .top
    0     4       4     0                            1011 halt
```

## Question 4

> Set `bx` to a high value for each thread, and then use the `-i` flag to generate different interrupt frequencies; what values lead to a bad outcomes? Which lead to good outcomes?

**Answer**

`./x86.py -p flag.s -a bx=2,bx=2 -M flag,count -R ax,bx -c`

As far as we can use `-i` to interrupt the critical section, we will be able to generate bad outcomes. For example, `./x86.py -p flag.s -a bx=4,bx=4 -i 2 -M flag,count -R ax,bx -c` will yield count = 4 (instead of 8 as expected.)

On the other hand, if we can set `-i` to not interrupt the critical section, then the result will be good. The easiest way to do that is to make `-i` very large.

## Question 5

> Now let’s look at the program `test-and-set.s`. First, try to understand the code, which uses the `xchg` instruction to build a simple locking primitive. How is the lock acquire written? How about lock release?

**Answer**

Lock release is a simple value assign, and lock acquire uses `xchg` which is an atomic swap.

## Question 6

> Now run the code, changing the value of the interrupt interval (`-i`) again, and making sure to loop for a number of times. Does the code always work as expected? Does it sometimes lead to an inefficient use of the CPU? How could you quantify that?

**Answer**

`./x86.py -p test-and-set.s -a bx=2,bx=2 -M mutex,count -R ax,bx -c`
`./x86.py -p test-and-set.s -a bx=2,bx=7 -i 2 -M mutex,count -R ax,bx -c`

Yes it seems always work. And there will be a while spin around line 10-11 which might lead to an inefficient use of the CPU?

## Question 7

> Use the `-P` flag to generate specific tests of the locking code. For example, run a schedule that grabs the lock in the first thread, but then tries to acquire it in the second. Does the right thing happen? What else should you test?

**Answer**

`./x86.py -p test-and-set.s -a bx=2,bx=2 -M mutex,count -R ax,bx -c -P 0011` will give correct result.

`./x86.py -p test-and-set.s -a bx=2,bx=2 -M mutex,count -R ax,bx -c -P 00000011111111` which will try to interrupt the critical section but also give correct result.

## Question 8

> Now let’s look at the code in `peterson.s`, which implements Peterson’s algorithm (mentioned in a sidebar in the text). Study the code and see if you can make sense of it.

**Answer**

Added a few notations to the assembly script.

## Question 9

> Now run the code with different values of `-i`. What kinds of different behavior do you see? Make sure to set the thread IDs appropriately (using `-a bx=0,bx=1` for example) as the code assumes it.

**Answer**

`./x86.py -p peterson.s -a bx=0,bx=1 -M flag,turn,count -R ax,bx -c` with `-i` in default value, 1, 2, and 3 will all yield the same result count = 2.

## Question 10

> Can you control the scheduling (with the `-P` flag) to “prove” that the code works? What are the different cases you should show hold? Think about mutual exclusion and deadlock avoidance.

**Answer**

Test about deadlock:
`./x86.py -p peterson.s -a bx=0,bx=1 -M flag,turn,count -R ax,bx -c -P 000000111111`

Test about critical section protection (mutual exclusion):
`./x86.py -p peterson.s -a bx=0,bx=1 -M flag,turn,count -R ax,bx -c -P 01`

Both works.

## Question 11

> Now study the code for the ticket lock in `ticket.s`. Does it match the code in the chapter? Then run with the following flags: `-a bx=1000,bx=1000` (causing each thread to loop through the critical section 1000 times). Watch what happens; do the threads spend much time spin-waiting for the lock?

**Answer**

Yes.

`./x86.py -p ticket.s -a bx=1000,bx=1000 -M ticket,turn,count -R ax,bx,cx -c`

The threads seems to spend quite some time spin-waiting for the lock We can see this result by comparing `ax` and `cx`, or simply see what code gets run (mostly .tryagain part.)

## Question 12

> How does the code behave as you add more threads?

**Answer**

`./x86.py -p ticket.s -a bx=10,bx=10,bx=10,bx=10 -t 4 -M ticket,turn,count -R ax,bx,cx -c`
More and more spins!

## Question 13

> Now examine `yield.s`, in which a yield instruction enables one thread to yield control of the CPU (realistically, this would be an OS primitive, but for the simplicity, we assume an instruction does the task). Find a scenario where `test-and-set.s` wastes cycles spinning, but `yield.s` does not. How many instructions are saved? In what scenarios do these savings arise?

**Answer**

`./x86.py -p test-and-set.s -a bx=2,bx=2 -M mutex,count -R ax,bx -c -i 7` will run 73 commands.

`./x86.py -p yield.s -a bx=2,bx=2 -M mutex,count -R ax,bx -c -i 7` will run 69 commands.

Trial and error... not very sure why. Was guessing that the magic must happen near the yield line.

## Question 14

> Finally, examine `test-and-test-and-set.s`. What does this lock do? What kind of savings does it introduce as compared to `test-and-set.s`?

**Answer**
It first test the value of `mutex`, if we don't have the lock, we don't swap. ?? can xchg fail?? otherwise how `test-and-set.s` line 10 will ever be false?
