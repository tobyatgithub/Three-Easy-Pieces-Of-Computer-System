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
