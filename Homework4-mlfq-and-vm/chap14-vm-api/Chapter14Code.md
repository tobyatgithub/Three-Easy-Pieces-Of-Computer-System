# Homework Code Chapter14

## Question 1

> First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Com- pile this into an executable called null. What happens when you run this program?

**Answer:**

Run `null.c` and we will get two returns:

1 - null

2 - [1] 51643 segmentation fault

## Question 2

> Next,compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?

**Answer:**

```
(gdb) run
Starting program: /Users/toby/Documents/ACADEMIC_Northeastern/2022_fall_now/cs5600_computerSystem_fall2022/Homework4/chap14/null
Note: this version of macOS has System Integrity Protection.
Because `startup-with-shell' is enabled, gdb has worked around this by
caching a copy of your shell.  The shell used by "run" is now:
    /Users/toby/Library/Caches/gdb/bin/sh
[New Thread 0x1a03 of process 57353]
[New Thread 0x1f03 of process 57353]
During startup program terminated with signal SIGTRAP, Trace/breakpoint trap.
```

## Question 3

> Finally, use the valgrind tool on this program. We’ll use the memcheck
tool that is a part of valgrind to analyze what happens. Run
this by typing in the following: valgrind --leak-check=yes
null. What happens when you run this? Can you interpret the
output from the tool?

**Answer:**

```
==8902== Memcheck, a memory error detector
==8902== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8902== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==8902== Command: ./null
==8902== 
==8902== Invalid read of size 4
==8902==    at 0x108701: main (null.c:8)
==8902==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==8902== 
==8902== 
==8902== Process terminating with default action of signal 11 (SIGSEGV)
==8902==  Access not within mapped region at address 0x0
==8902==    at 0x108701: main (null.c:8)
==8902==  If you believe this happened as a result of a stack
==8902==  overflow in your program's main thread (unlikely but
==8902==  possible), you can try to increase the size of the
==8902==  main thread stack using the --main-stacksize= flag.
==8902==  The main thread stack size used in this run was 8388608.
==8902== 
==8902== HEAP SUMMARY:
==8902==     in use at exit: 4 bytes in 1 blocks
==8902==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==8902== 
==8902== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==8902==    at 0x4C33B25: calloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==8902==    by 0x1086F0: main (null.c:6)
==8902== 
==8902== LEAK SUMMARY:
==8902==    definitely lost: 4 bytes in 1 blocks
==8902==    indirectly lost: 0 bytes in 0 blocks
==8902==      possibly lost: 0 bytes in 0 blocks
==8902==    still reachable: 0 bytes in 0 blocks
==8902==         suppressed: 0 bytes in 0 blocks
==8902== 
==8902== For counts of detected and suppressed errors, rerun with: -v
==8902== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
Segmentation fault
```


## Question 4

> Write a simple program that allocates memory using malloc() but
forgets to free it before exiting. What happens when this program
runs? Can you use gdb to find any problems with it? How about
valgrind (again with the --leak-check=yes flag)?

**Answer:**

Return from `gdb` and `run`: no problem
```
(gdb) run
Starting program: /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/forgetFree 
1
[Inferior 1 (process 9289) exited normally]
```

Return from `valgrind --leak-check=yes ./forgetFree`:
```
==9389== Memcheck, a memory error detector
==9389== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9389== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==9389== Command: ./forgetFree
==9389== 
1
==9389== 
==9389== HEAP SUMMARY:
==9389==     in use at exit: 4 bytes in 1 blocks
==9389==   total heap usage: 2 allocs, 1 frees, 1,028 bytes allocated
==9389== 
==9389== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==9389==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==9389==    by 0x10869B: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/forgetFree)
==9389== 
==9389== LEAK SUMMARY:
==9389==    definitely lost: 4 bytes in 1 blocks
==9389==    indirectly lost: 0 bytes in 0 blocks
==9389==      possibly lost: 0 bytes in 0 blocks
==9389==    still reachable: 0 bytes in 0 blocks
==9389==         suppressed: 0 bytes in 0 blocks
==9389== 
==9389== For counts of detected and suppressed errors, rerun with: -v
==9389== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## Question 5

>  Write a program that creates an array of integers called data of size
100 using malloc; then, set data[100] to zero. What happens
when you run this program? What happens when you run this
program using valgrind? Is the program correct?


**Answer:**

1 - hmmm no error or complain when running this program.

2 - running with valgrind `valgrind --leak-check=yes ./data `:

```
==9839== Memcheck, a memory error detector
==9839== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9839== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==9839== Command: ./data
==9839== 
==9839== Invalid write of size 4
==9839==    at 0x10866A: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/data)
==9839==  Address 0x522f1d0 is 0 bytes after a block of size 400 alloc'd
==9839==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==9839==    by 0x10865B: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/data)
==9839== 
==9839== 
==9839== HEAP SUMMARY:
==9839==     in use at exit: 400 bytes in 1 blocks
==9839==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
==9839== 
==9839== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==9839==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==9839==    by 0x10865B: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/data)
==9839== 
==9839== LEAK SUMMARY:
==9839==    definitely lost: 400 bytes in 1 blocks
==9839==    indirectly lost: 0 bytes in 0 blocks
==9839==      possibly lost: 0 bytes in 0 blocks
==9839==    still reachable: 0 bytes in 0 blocks
==9839==         suppressed: 0 bytes in 0 blocks
==9839== 
==9839== For counts of detected and suppressed errors, rerun with: -v
==9839== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

2 errors from 2 contexts.

## Question 6

> Create a program that allocates an array of integers (as above), frees
them, and then tries to print the value of one of the elements of
the array. Does the program run? What happens when you use
valgrind on it?


**Answer:**

See in `data2.c`

1. The program runs and print out 0 as expected.
2. Running `valgrind --leak-check=yes ./data2`:
```
==10160== Memcheck, a memory error detector
==10160== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10160== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==10160== Command: ./data2
==10160== 
==10160== Invalid read of size 4
==10160==    at 0x108700: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/data2)
==10160==  Address 0x522f040 is 0 bytes inside a block of size 400 free'd
==10160==    at 0x4C32D3B: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==10160==    by 0x1086FB: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/data2)
==10160==  Block was alloc'd at
==10160==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==10160==    by 0x1086EB: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/data2)
==10160== 
0
==10160== 
==10160== HEAP SUMMARY:
==10160==     in use at exit: 0 bytes in 0 blocks
==10160==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==10160== 
==10160== All heap blocks were freed -- no leaks are possible
==10160== 
==10160== For counts of detected and suppressed errors, rerun with: -v
==10160== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## Question 7

> Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?


**Answer:**

See in `q7.c`, the program will Abort and report "invalid pointer" error.

Running `valgrind --leak-check=yes ./q7`:
```
==10524== Memcheck, a memory error detector
==10524== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==10524== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==10524== Command: ./q7
==10524== 
==10524== Invalid free() / delete / delete[] / realloc()
==10524==    at 0x4C32D3B: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==10524==    by 0x1086AF: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/q7)
==10524==  Address 0x522f068 is 40 bytes inside a block of size 400 alloc'd
==10524==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==10524==    by 0x10869B: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/q7)
==10524== 
==10524== 
==10524== HEAP SUMMARY:
==10524==     in use at exit: 400 bytes in 1 blocks
==10524==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==10524== 
==10524== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==10524==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==10524==    by 0x10869B: main (in /home/tobyu/Documents/cs5600_computerSystem_fall2022/Homework4/chap14/q7)
==10524== 
==10524== LEAK SUMMARY:
==10524==    definitely lost: 400 bytes in 1 blocks
==10524==    indirectly lost: 0 bytes in 0 blocks
==10524==      possibly lost: 0 bytes in 0 blocks
==10524==    still reachable: 0 bytes in 0 blocks
==10524==         suppressed: 0 bytes in 0 blocks
==10524== 
==10524== For counts of detected and suppressed errors, rerun with: -v
==10524== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

## Question 8

> Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.


**Answer:**
