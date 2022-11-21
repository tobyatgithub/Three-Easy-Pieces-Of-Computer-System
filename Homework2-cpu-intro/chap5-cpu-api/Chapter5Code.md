# Homework Code

## Question 1

> Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

**Answers:**

See `q1.c`, print result of `q1.c`:

```
hello world (pid:27215)
hello, i am parent of 27216 (pid:27215)
parent: value of x = (100)
parent: change x to 1010, x = (1010)
hello, i am child (pid27216)
child: value of x = (100)
child: change x to 101, x = (101)
```

As we can see, the value x is copied independently and not being affected by each other.

## Question 2

> Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?

**Answers:**

Yes. Both parent and child can access the file descriptor.
And writing concurrently seems ok as well via the results of `q2.c`:

```
3
For the parent process, fp == 3
2020
For the child process, fd == 3
20201010
```

That is, the parent will write first (2020), and the child will write after it (1010).

## Question 3

> Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

**Answers:**

See in `q3.c`. It is easy to achieve with `wait()`... However I'm not sure how to do it without `wait()`.

```
hello world (pid:29235)
hello, i am child (pid29236)
child: hello
hello, i am parent of 29236 (pid:29235)
parent: goodbye.
```

## Question 4

> Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?

**Answers:**

Based on this [article](https://linuxhint.com/exec_linux_system_call_c/) which show-cased for each variants of `exec()`, we can learn that these variants are designed for different scenarios. And the main condition seems to be related to the **environment variables** and **args**.

Example can be found in `q4.c`

## Question 5

> Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

**Answers:**

Calling `wait()` in child process seems have no effect to the process and the return of the `wait()` in child process = -1. And the `wait()` in the parent process will return the pid of the child process.

Result of `q5.c`:

```
hello world (pid:30391)
hello, I am child (pid:30392)
child: return of wait = -1
hello, I am parent of 30392 (pid:30391)
parent: return of wait = 30392
```

## Question 6

> Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

**Answers:**

Please see the code in `p6.c`. And I'm assuming that `waitpid()` will be useful it we have multiple forks.

```
hello world (pid:30934)
hello, I am parent of 30935 (pid:30936)
parent: return of wait = -1
hello, I am child2 (pid:30936)
hello, I am child1 (pid:30935)
hello, I am parent of 30937 (pid:30935)
hello, I am child1 (pid:30937)
hello, I am child2 (pid:30937)
hello, I am parent of 30935 (pid:30934)
parent: return of wait = 30935
hello, I am parent of 30936 (pid:30934)
```

## Question 7

> Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?

**Answers:**

The `printf()` of the child will not print, but the parent's `printf` will still work.

Results of `q7.c`:

```
hello world (pid:31111)
hello, I am parent of 31112 (pid:31111)
```

## Question 8

> Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.

**Answers:**
Using the example from [https://stackoverflow.com/questions/6877697/communicating-between-two-child-processes-with-pipes](https://stackoverflow.com/questions/6877697/communicating-between-two-child-processes-with-pipes), we see how we can use `pipe()` to make child processes communicate with each other. In the `q8.c`, we first init
the two placeholders for the pipe (i.e. `pfd1` and `pfd2`.) After we fork them with some error checking, we call both `write` and `read` on the two processes and we can see they both sent and received messages from each other.

Results from `q8.c`:

```
Piped opened with success. Forking ...

Child 1 executing...
Parent closing pipes.
Parent waiting for children completion...

Child 2 executing...
Message received child TWO: Hello from child ONE.
Exiting child 2...
Message received child ONE: Hello from child TWO.
Exiting child 1...
Parent finishing.
```
