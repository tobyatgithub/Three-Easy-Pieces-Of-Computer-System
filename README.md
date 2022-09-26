# cs5600_computerSystem_fall2022

Class repo for cs5600, where we dig deep into computer systems.

## Reading Notes

### Chapter 2 intro

Key/Crux of this chapter:

Crux of Virtualization:

> How does the operating system virtualize resources? where **virtualization** == the OS takes a physical resource (processor, memory, or a disk) and transforms it into a more general, powerful, and easy-to-use virtual form of itself.

- provides some interfaces/APIs/system calls that are available to applications (standard library).
- thus OS is known as a resource manager.
- Memory virtualization: each process accesses its own private virtual address space (sometimes just called its address space), which the OS somehow maps onto the physical memory of the machine.

Crux of "How to build correct concurrent programs":

> When there are many concurrently executing threads within the same memory space, how can we build a correctly working program? What primitives are needed from the OS? What mechanisms should be provided by the hardware? How can we use them to solve the problems of concurrency?

Crux of the "how to store data persistently":

> The file system is the part of the OS in charge of managing persistent data. What techniques are needed to do so correctly? What mechanisms and policies are required to do so with high performance? How is reliability achieved, in the face of failures in hardware and software?

### Chapter 4 CPU-Intro, The Abstraction: The Process

The process == a running program. (where a program is a lifeless bunch of instructions and maybe some static data on the disk, waiting to spring into action.)

The Crux of "How to provide the illusion of many CPUs"?

> Although there are only a few physical CPUs available, how can the OS provide the illusion of a nearly-endless supply of said CPUs?

- The OS creates this illusion by virtualizing the CPU. By running one process, then stopping it and running another, and so forth, the OS can promote the illusion that many virtual CPUs exist when in fact there is only one physical CPU (or a few)

- time sharing: is a basic technique used by an OS to share a resource. By allowing the resource to be used for a little while by one entity, and then a little while by another, and so forth, the resource in question (e.g., the CPU, or a network link) can be shared by many. This basic technique, known as time sharing of the CPU, allows users to run as many concurrent processes as they would like; the potential cost is performance, as each will run more slowly if the CPU(s) must be shared.

- mechanism: We call the low-level machinery mechanisms; mechanisms are low-level methods or protocols that implement a needed piece of functionality.

- policy: Policies are algorithms for making some kind of decision within the OS. For example, given a number of possible programs to run on a CPU, which program should the OS run?

- 5 must-have process APIs: create, destroy, wait, miscellaneous control, status.

- 3 process states: running, ready, and blocked

### Chapter 5 Interlude: Process API

- The CPU scheduler (via calling fork()), we can see, is not deterministic. (i.e. the parent process and child process from fork() might get called and executed in any order.)

- This non-determinism, as it turns out, leads to some interesting problems, particularly in multi-threaded programs; hence, we’ll see a lot more non- determinism when we study concurrency in the second part of the book.

- The strangeness of `fork()` and `exec()` (and `wait()`). For now, suffice it to say that the `fork()`/`exec()` combination is a powerful way to create and manipulate processes.

- The `wait()` system call allows a parent to wait for its child to complete execution.

- The `exec()` family of system calls allows a child to break free from its similarity to its parent and execute an entirely new program.

- A UNIX shell commonly uses fork(), wait(), and exec() to launch user commands; the separation of fork and exec enables features like input/output redirection, pipes, and other cool features, all without changing anything about the programs being run.

- Process control other than fork and exec (e.g. kill) can be used to send signals to a process. However, not everyone/application is allowed to do this. Otherwise the usability and security of the system will be compromised. Thus only a validated **user** is allowed to control their own processes.

### Chapter 7 Scheduling

Crux of "How to develope scheduling policy":

> How should we develop a basic framework for thinking about scheduling policies? What are the key assumptions? What metrics are important? What basic approaches have been used in the earliest of computer systems?

- workload: Determining the workload is a critical part of building policies, and the more you know about workload, the more fine-tuned your policy can be.

- (metric) turnaround time: the time at which the job completes minus the time at which the job arrived in the system

- (metric) response time: the time from when the job arrives in a system to the first time it is scheduled

- (policy) Shortest Job First (SJF): it runs the shortest job first, then the next shortest, and so on.

- (policy) Shortest Time-to-Completion First (STCF): Any time a new job enters the system, the STCF scheduler determines which of the re- maining jobs (including the new job) has the least time left, and schedules that one.

- (policy) round robin /time-slicing: instead of running jobs to completion, RR runs a job for a time slice (sometimes called a scheduling quantum) and then switches to the next job in the run queue. (make scheduling quantum big to reduce the context-switching cost.)


### Chapter 8 The Multi-level feedback queue

Crux of "How to schedule without perfect knowledge?"

> Given that we in general do not know anything about a process, how can we build a scheduler to achivev these goals? How can the scheduler learn, as the system runs, the characteristics of the jobs it is running, and thus make better scheduling decisions? (*esp. without a priori knowledge of job length?)

- There are two overall goals for MLFQ: 1. optimize turnaround time (~shorter jobs first); 2. minimize response time (~ Round Robin).

- MLFQ's answer: learn from history.
    - the MLFQ has a number of distinct queues, each assigned a different priority level
    - MLFQ uses priorities to decide which job should run at a given time
    - Rule 1: If Priority(A) > Priority(B), A runs (B doesn’t).
    - Rule 2: If Priority(A) = Priority(B), A & B run in RR.
    - Rather than giving a fixed priority to each job, MLFQ varies the priority of a job based on its observed behavior. 
    - Rule 3: When a job enters the system, it is placed at the highest priority (the topmost queue).
    - Rule 4a: If a job uses up an entire time slice while running, its priority is reduced (i.e., it moves down one queue).
    - Rule 4b: If a job gives up the CPU before the time slice is up, it stays at the same priority level.
    - because it doesn’t know whether a job will be a short job or a long-running job, it first assumes it might be a short job, thus giving the job high priority. If it actually is a short job, it will run quickly and complete; if it is not a short job, it will slowly move down the queues, and thus soon prove itself to be a long-running more batch-like process. In this manner, MLFQ approximates SJF.
    - FLAWS: 
        1. First, there is the problem of starvation: if there are “too many” in- teractive jobs in the system, they will combine to consume all CPU time, and thus long-running jobs will never receive any CPU time (they starve).
        2. Second, a smart user could rewrite their program to game the scheduler (e.g. before the time slice is over, issue an I/O operation (to some file you don’t care about) and thus relinquish the CPU)
        3. a program may change its behavior over time; what was CPU- bound may transition to a phase of interactivity (but will remain in lowest priority in our current design.)
    
- MLFQ improve: The Priority Boost
    - "Reshuffle"Rule 5: After some time period S, move all the jobs in the system to the topmost queue.
    - Our new rule solves two problems at once. First, processes are guar- anteed not to starve: by sitting in the top queue, a job will share the CPU with other high-priority jobs in a round-robin fashion, and thus eventu- ally receive service. Second, if a CPU-bound job has become interactive, the scheduler treats it properly once it has received the priority boost.
    - However, it is very hard and tricky to set the time period S correct. If it is set too high, long-running jobs could starve; too low, and interactive jobs may not get a proper share of the CPU. "voo-doo constant", "magic number".

    