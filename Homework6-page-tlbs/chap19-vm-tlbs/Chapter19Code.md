# Homework Simulation Chapter 19 Faster Paging TLBs

## Question 1

> For timing, you’ll need to use a timer (e.g., `gettimeofday()`). How precise is such a timer? How long does an operation have to take in order for you to time it precisely? (this will help determine how many times, in a loop, you’ll have to repeat a page access in order to time it successfully)

**Answer:**

`clock_gettime(CLOCK_PROCESS_CPUTIME_ID, ...)` seems to have resolution of 1000 nanoseconds on macOS. But it is rather unstable (tested with `sleep(2)` multiple times and will get elapsed time ranging from 16000 to 35000 nanoseconds...)

## Question 2

> Write the program, called `tlb.c`, that can roughly measure the cost of accessing each page. Inputs to the program should be: the number of pages to touch and the number of trials.

**Answer:**

See `tlb.c` file.

## Question 3

> Now write a script in your favorite scripting language (bash?) to run this program, while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration. Run the script on different machines and gather some data. How many trials are needed to get reliable measurements?

**Answer:**

Most of the measurement will jump between 2 second to 3 seconds for page = 4. And for 5000 epochs it seems to become stable.

`python ./main.py 4 5000`

## Question 4

> Next, graph the results, making a graph that looks similar to the one above. Use a good tool like `ploticus` or even `zplot`. Visualization usually makes the data much easier to digest; why do you think that is?

**Answer:**

`python ./main.py 4 5000` and see the `plot.png`

## Question 5

> One thing to watch out for is compiler optimization. Compilers do all sorts of clever things, including removing loops which increment values that no other part of the program subsequently uses. How can you ensure the compiler does not remove the main loop above from your TLB size estimator?

**Answer:**

By searching the internet... it seems we can "Use the command-line option -O0 (-[capital o][zero]) to disable optimization." And -O0 is the default option (by: https://developer.arm.com/documentation/den0013/d/Optimizing-Code-to-Run-on-ARM-Processors/Compiler-optimizations/GCC-optimization-options)

## Question 6

> Another thing to watch out for is the fact that most systems today ship with multiple CPUs, and each CPU, of course, has its own TLB hierarchy. To really get good measurements, you have to run your code on just one CPU, instead of letting the scheduler bounce it from one CPU to the next. How can you do that? (hint: look up “pinning a thread” on Google for some clues) What will happen if you don’t do this, and the code moves from one CPU to the other?

**Answer:**

hmmmmm didn't find a way to do it on mac os yet.

## Question 7

> Another issue that might arise relates to initialization. If you don’t initialize the array `a` above before accessing it, the first time you access it will be very expensive, due to initial access costs such as demand zeroing. Will this affect your code and its timing? What can you do to counterbalance these potential costs?

**Answer:**

if it is the cost of demand zeroing that we concern about, we can use `calloc` instead of `malloc` in initialization, as:

"The C library function void \*calloc(size_t nitems, size_t size) allocates the requested memory and returns a pointer to it. The difference in malloc and calloc is that malloc does not set the memory to zero where as calloc sets allocated memory to zero."
