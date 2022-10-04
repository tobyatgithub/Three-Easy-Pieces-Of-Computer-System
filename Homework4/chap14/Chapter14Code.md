# Homework Code Chapter14

## Question 1

> First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Com- pile this into an executable called null. What happens when you run this program?

**Answer:**

Run `null.c` and we will get two returns:

1 - null

2 - [1] 51643 segmentation fault

## Question

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

## Question

> QQQ

**Answer:**
