# Homework Simulation Chapter 18 Paging

The steps seems to be 1. convert the 0x... to binary (bin(0x...)), and use the first two digit as the page table number, and then, use the mask to find the offset value: offset = hex(0x00003229 & 0x00000fff) = hex(553) = 0x229; then combine with the page value (page 3 maps to 6 thus -> 0x6229)

## Question 1

> Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags:

```
-P 1k -a 1m -p 512m -v -n 0
-P 1k -a 2m -p 512m -v -n 0
-P 1k -a 4m -p 512m -v -n 0
```

Then, to understand how linear page table size changes as page size grows:

```
-P 1k -a 1m -p 512m -v -n 0
-P 2k -a 1m -p 512m -v -n 0
-P 4k -a 1m -p 512m -v -n 0
```

Before running any of these, try to think about the expected trends. How should page-table size change as the address space grows? As the page size grows? Why not use big pages in general?

**Answer:**

`-P` changes the size of the page, the larger the page, the fewer page we will have (given the physical memory space size limitation.)

`-a` changes the size of the address space. The more space we have, the more pages we will get.

## Question 2

> Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example:

```
-P 1k -a 16k -p 32k -v -u 0
-P 1k -a 16k -p 32k -v -u 25
-P 1k -a 16k -p 32k -v -u 50
-P 1k -a 16k -p 32k -v -u 75
-P 1k -a 16k -p 32k -v -u 100
```

What happens as you increase the percentage of pages that are allocated in each address space?

**Answer:**

As the percentage increases, the more virtual address trace will have chance to be valid.

## Question 3

> Now let’s try some different random seeds, and some different (and sometimes quite crazy) address-space parameters, for variety:

```
-P 8 -a 32 -p 1024 -v -s 1
-P 8k -a 32k -p 1m -v -s 2
-P 1m -a 256m -p 512m -v -s 3
```

Which of these parameter combinations are unrealistic? Why?

**Answer:**
`-P 1m -a 256m -p 512m -v -s 3` might not be that realistic as it is too big. The first and the second seems quite proportional.

## Question 4

> Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?

**Answer:**
`./paging-linear-translate.py -a 32k -p 32k` -> the physical memory size must be greater than address-space size.

`./paging-linear-translate.py -P 64 -a 32 -p 1024 -v -c` or `./paging-linear-translate.py -P 10 -a 32 -p 1024 -v -c` -> Error in argument: address space must be a multiple of the pagesize

`./paging-linear-translate.py -a 0 -v -c` -> Error: must specify a non-zero address-space size.
