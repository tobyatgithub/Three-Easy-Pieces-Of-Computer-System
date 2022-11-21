# Homework Simulation Chapter 27 Thread API

## Homework (Code)

In this section, we’ll write some simple multi-threaded programs and use a specific tool, called `helgrind`, to find
problems in these programs.

Read the README in the homework download for details on how to build the programs and run `helgrind`.

## Question 1

> First build `main-race.c`. Examine the code so you can see the (hopefully obvious) data race in the code. Now
> run `helgrind` (by typing `valgrind --tool=helgrind main-race`) to see how it reports the race. Does it point to the
> right lines of code? What other information does it give to you?

**Answer:**

Yes, the `balance++` is not protected and being modified both in the main thread and in the newly created p_thread.

```
i$ valgrind --tool=helgrind ./main-race
==4916== Helgrind, a thread error detector
==4916== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==4916== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==4916== Command: ./main-race
==4916==
==4916== ---Thread-Announcement------------------------------------------
==4916==
==4916== Thread #1 is the program's root thread
==4916==
==4916== ---Thread-Announcement------------------------------------------
==4916==
==4916== Thread #2 was created
==4916==    at 0x518460E: clone (clone.S:71)
==4916==    by 0x4E4BEC4: create_thread (createthread.c:100)
==4916==    by 0x4E4BEC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==4916==    by 0x4C38A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==4916==    by 0x1087E2: main (main-race.c:14)
==4916==
==4916== ----------------------------------------------------------------
==4916==
==4916== Possible data race during read of size 4 at 0x309014 by thread #1
==4916== Locks held: none
==4916==    at 0x108806: main (main-race.c:15)
==4916==
==4916== This conflicts with a previous write of size 4 by thread #2
==4916== Locks held: none
==4916==    at 0x10879B: worker (main-race.c:8)
==4916==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==4916==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==4916==    by 0x518461E: clone (clone.S:95)
==4916==  Address 0x309014 is 0 bytes inside data symbol "balance"
==4916==
==4916== ----------------------------------------------------------------
==4916==
==4916== Possible data race during write of size 4 at 0x309014 by thread #1
==4916== Locks held: none
==4916==    at 0x10880F: main (main-race.c:15)
==4916==
==4916== This conflicts with a previous write of size 4 by thread #2
==4916== Locks held: none
==4916==    at 0x10879B: worker (main-race.c:8)
==4916==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==4916==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==4916==    by 0x518461E: clone (clone.S:95)
==4916==  Address 0x309014 is 0 bytes inside data symbol "balance"
==4916==
==4916==
==4916== For counts of detected and suppressed errors, rerun with: -v
==4916== Use --history-level=approx or =none to gain increased speed, at
==4916== the cost of reduced accuracy of conflicting-access information
==4916== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

It correctly pointed out the two data-race places: main-race.c: line 8 and line 15.

## Question 2

> What happens when you remove one of the offending lines of code? Now add a lock around one of the updates to the
> shared variable, and then around both. What does helgrind report in each of these cases?

**Answer:**

1. Remove the `balance++` in the worker method and helgrind gives no errors:

```
$ valgrind --tool=helgrind ./main-race
==5085== Helgrind, a thread error detector
==5085== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==5085== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==5085== Command: ./main-race
==5085==
==5085==
==5085== For counts of detected and suppressed errors, rerun with: -v
==5085== Use --history-level=approx or =none to gain increased speed, at
==5085== the cost of reduced accuracy of conflicting-access information
==5085== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

2. Adding one lock is not enough, will result in the same error message as shown in the last question.
3. Adding two locks will be sufficient and there will be no error nor race condition.

## Question 3

> Now let’s look at `main-deadlock.c`. Examine the code. This code has a problem known as **deadlock** (which we discuss
> in much more depth in a forthcoming chapter). Can you see what problem it might have?

**Answer:**

Yes, both threads will try to acquire lock1 and lock2. Thus possibly locking out each other.

## Question 4

> Now run `helgrind` on this code. What does `helgrind` report?

**Answer:**

```
$ valgrind --tool=helgrind ./main-deadlock
==5874== Helgrind, a thread error detector
==5874== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==5874== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==5874== Command: ./main-deadlock
==5874==
==5874== ---Thread-Announcement------------------------------------------
==5874==
==5874== Thread #3 was created
==5874==    at 0x518460E: clone (clone.S:71)
==5874==    by 0x4E4BEC4: create_thread (createthread.c:100)
==5874==    by 0x4E4BEC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==5874==    by 0x4C38A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x1089E8: main (main-deadlock.c:24)
==5874==
==5874== ----------------------------------------------------------------
==5874==
==5874== Thread #3: lock order "0x30A040 before 0x30A080" violated
==5874==
==5874== Observed (incorrect) order is: acquisition of lock at 0x30A080
==5874==    at 0x4C3603C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x1088B6: worker (main-deadlock.c:13)
==5874==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==5874==    by 0x518461E: clone (clone.S:95)
==5874==
==5874==  followed by a later acquisition of lock at 0x30A040
==5874==    at 0x4C3603C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x1088E5: worker (main-deadlock.c:14)
==5874==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==5874==    by 0x518461E: clone (clone.S:95)
==5874==
==5874== Required order was established by acquisition of lock at 0x30A040
==5874==    at 0x4C3603C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x108858: worker (main-deadlock.c:10)
==5874==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==5874==    by 0x518461E: clone (clone.S:95)
==5874==
==5874==  followed by a later acquisition of lock at 0x30A080
==5874==    at 0x4C3603C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x108887: worker (main-deadlock.c:11)
==5874==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==5874==    by 0x518461E: clone (clone.S:95)
==5874==
==5874==  Lock at 0x30A040 was first observed
==5874==    at 0x4C3603C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x108858: worker (main-deadlock.c:10)
==5874==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==5874==    by 0x518461E: clone (clone.S:95)
==5874==  Address 0x30a040 is 0 bytes inside data symbol "m1"
==5874==
==5874==  Lock at 0x30A080 was first observed
==5874==    at 0x4C3603C: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x108887: worker (main-deadlock.c:11)
==5874==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==5874==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==5874==    by 0x518461E: clone (clone.S:95)
==5874==  Address 0x30a080 is 0 bytes inside data symbol "m2"
==5874==
==5874==
==5874==
==5874== For counts of detected and suppressed errors, rerun with: -v
==5874== Use --history-level=approx or =none to gain increased speed, at
==5874== the cost of reduced accuracy of conflicting-access information
==5874== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
```

"Thread #3: lock order "0x30A040 before 0x30A080" violated"

## Question 5

> Now run `helgrind` on `main-deadlock-global.c`. Examine the code; does it have the same problem that `main-deadlock.c`
> has? Should `helgrind` be reporting the same error? What does this tell you about tools like `helgrind`?

**Answer:**

`helgrind` is reporting the same error. And I believe it should not report the same error as the `g` lock shall solve
the race condition issue. Thus we can see that the `helgrind` tool is not perfect (and detecting race condition could be
challenging indeed.)

## Question 6

> Let’s next look at `main-signal.c`. This code uses a variable (`done`) to signal that the child is done and that the
> parent can now continue. Why is this code inefficient? (what does the parent end up spending its time doing,
> particularly if the child thread takes a long time to complete?)


**Answer:**

This is the issue mentioned in the page 8 of the textbook chap 27. And the author warned us: "First, it performs poorly
in many cases (spinning for a long time just wastes CPU cycles). Second, it is error prone. As recent research
shows [X+10], it is surprisingly easy to make mistakes when using flags (as above) to synchronize between threads; in
that study, roughly half the uses of these ad hoc synchronizations were buggy! Don’t be lazy; use condition variables
even when you think you can get away without doing so."

## Question 7

> Now run `helgrind` on this program. What does it report? Is the code correct?

**Answer:**

```
$ valgrind --tool=helgrind ./main-signal
==6190== Helgrind, a thread error detector
==6190== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==6190== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==6190== Command: ./main-signal
==6190==
this should print first
==6190== ---Thread-Announcement------------------------------------------
==6190==
==6190== Thread #1 is the program's root thread
==6190==
==6190== ---Thread-Announcement------------------------------------------
==6190==
==6190== Thread #2 was created
==6190==    at 0x518460E: clone (clone.S:71)
==6190==    by 0x4E4BEC4: create_thread (createthread.c:100)
==6190==    by 0x4E4BEC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
==6190==    by 0x4C38A27: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==6190==    by 0x1087DD: main (main-signal.c:15)
==6190==
==6190== ----------------------------------------------------------------
==6190==
==6190== Possible data race during read of size 4 at 0x309014 by thread #1
==6190== Locks held: none
==6190==    at 0x108802: main (main-signal.c:16)
==6190==
==6190== This conflicts with a previous write of size 4 by thread #2
==6190== Locks held: none
==6190==    at 0x108792: worker (main-signal.c:9)
==6190==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==6190==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==6190==    by 0x518461E: clone (clone.S:95)
==6190==  Address 0x309014 is 0 bytes inside data symbol "done"
==6190==
==6190== ----------------------------------------------------------------
==6190==
==6190== Possible data race during write of size 1 at 0x5C551A5 by thread #1
==6190== Locks held: none
==6190==    at 0x4C3E546: mempcpy (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==6190==    by 0x50EE933: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1258)
==6190==    by 0x50E3A3E: puts (ioputs.c:40)
==6190==    by 0x108817: main (main-signal.c:18)
==6190==  Address 0x5c551a5 is 21 bytes inside a block of size 1,024 alloc'd
==6190==    at 0x4C32F2F: malloc (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==6190==    by 0x50E113B: _IO_file_doallocate (filedoalloc.c:101)
==6190==    by 0x50F1328: _IO_doallocbuf (genops.c:365)
==6190==    by 0x50F0447: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:759)
==6190==    by 0x50EE98C: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1266)
==6190==    by 0x50E3A3E: puts (ioputs.c:40)
==6190==    by 0x108791: worker (main-signal.c:8)
==6190==    by 0x4C38C26: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==6190==    by 0x4E4B6DA: start_thread (pthread_create.c:463)
==6190==    by 0x518461E: clone (clone.S:95)
==6190==  Block was alloc'd by thread #2
==6190==
this should print last
==6190==
==6190== For counts of detected and suppressed errors, rerun with: -v
==6190== Use --history-level=approx or =none to gain increased speed, at
==6190== the cost of reduced accuracy of conflicting-access information
==6190== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 40)
```

Potential data race between line 9 `done = 1;` and line 16 `while (done == 0)`

## Question 8

> Now look at a slightly modified version of the code, which is found in `main-signal-cv.c`. This version uses a
> condition variable to do the signaling (and associated lock). Why is this code preferred to the previous version? Is
> it
> correctness, or performance, or both?

**Answer:**

Both.

## Question 9

> Once again run `helgrind` on `main-signal-cv`. Does it report any errors?

**Answer:**
No errors!

```
$ valgrind --tool=helgrind ./main-signal-cv
==6342== Helgrind, a thread error detector
==6342== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==6342== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==6342== Command: ./main-signal-cv
==6342==
this should print first
this should print last
==6342==
==6342== For counts of detected and suppressed errors, rerun with: -v
==6342== Use --history-level=approx or =none to gain increased speed, at
==6342== the cost of reduced accuracy of conflicting-access information
==6342== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)
```