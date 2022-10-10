# Homework Simulation Chapter 16 VM Segmentation

## Question 1

> First let’s use a tiny address space to translate some addresses.Here’s a simple set of parameters with a few different random seeds; can you translate the addresses?

**Answer:**

`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -c`
`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -c`
`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -c`

## Question 2

> Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). What is the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? What are the lowest and highest _illegal_ addresses in this entire address space? Finally, how would you run `segmentation.py` with the `-A` flag to test if you are right?

**Answer:**

😂 here the VA decimal address is something totally different from last chapter, here it is only one line and we are deciding whether that line is legal or not.

Here the highest legal virtual address in segment is at segment0 = 0~19

The lowest legal virtual address is at segment1 = 108~127

We can test with:
`./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -A 0,19,20,107,108,127,128 -c`

ARG seed 1
ARG address space size 128
ARG phys mem size 512

Segment register information:

Segment 0 base (grows positive) : 0x00000000 (decimal 0)
Segment 0 limit : 20

Segment 1 base (grows negative) : 0x00000200 (decimal 512)
Segment 1 limit : 20

Virtual Address Trace
VA 0: 0x00000000 (decimal: 0) --> VALID in SEG0: 0x00000000 (decimal: 0)
VA 1: 0x00000013 (decimal: 19) --> VALID in SEG0: 0x00000013 (decimal: 19)
VA 2: 0x00000014 (decimal: 20) --> SEGMENTATION VIOLATION (SEG0)
VA 3: 0x0000006b (decimal: 107) --> SEGMENTATION VIOLATION (SEG1)
VA 4: 0x0000006c (decimal: 108) --> VALID in SEG1: 0x000001ec (decimal: 492)
VA 5: 0x0000007f (decimal: 127) --> VALID in SEG1: 0x000001ff (decimal: 511)
Error: virtual address 128 cannot be generated in an address space of size 128

## Question 3

> Let’s say we have a tiny 16-byte address space in a 128-byte physical memory. What base and bounds would you set up so as to get the simulator to generate the following translation results for the specified address stream: valid, valid, violation, ..., violation, valid, valid? Assume the following parameters:

**Answer:**

`./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 16 --l1 2 -c`

ARG seed 0
ARG address space size 16
ARG phys mem size 128

Segment register information:

Segment 0 base (grows positive) : 0x00000000 (decimal 0)
Segment 0 limit : 2

Segment 1 base (grows negative) : 0x00000010 (decimal 16)
Segment 1 limit : 2

Virtual Address Trace
VA 0: 0x00000000 (decimal: 0) --> VALID in SEG0: 0x00000000 (decimal: 0)
VA 1: 0x00000001 (decimal: 1) --> VALID in SEG0: 0x00000001 (decimal: 1)
VA 2: 0x00000002 (decimal: 2) --> SEGMENTATION VIOLATION (SEG0)
VA 3: 0x00000003 (decimal: 3) --> SEGMENTATION VIOLATION (SEG0)
VA 4: 0x00000004 (decimal: 4) --> SEGMENTATION VIOLATION (SEG0)
VA 5: 0x00000005 (decimal: 5) --> SEGMENTATION VIOLATION (SEG0)
VA 6: 0x00000006 (decimal: 6) --> SEGMENTATION VIOLATION (SEG0)
VA 7: 0x00000007 (decimal: 7) --> SEGMENTATION VIOLATION (SEG0)
VA 8: 0x00000008 (decimal: 8) --> SEGMENTATION VIOLATION (SEG1)
VA 9: 0x00000009 (decimal: 9) --> SEGMENTATION VIOLATION (SEG1)
VA 10: 0x0000000a (decimal: 10) --> SEGMENTATION VIOLATION (SEG1)
VA 11: 0x0000000b (decimal: 11) --> SEGMENTATION VIOLATION (SEG1)
VA 12: 0x0000000c (decimal: 12) --> SEGMENTATION VIOLATION (SEG1)
VA 13: 0x0000000d (decimal: 13) --> SEGMENTATION VIOLATION (SEG1)
VA 14: 0x0000000e (decimal: 14) --> VALID in SEG1: 0x0000000e (decimal: 14)
VA 15: 0x0000000f (decimal: 15) --> VALID in SEG1: 0x0000000f (decimal: 15)

## Question 4

> Assume we want to generate a problem where roughly 90% of the randomly-generated virtual addresses are valid (not segmentation violations). How should you configure the simulator to do so? Which parameters are important to getting this outcome?

**Answer:**

I will argue say the most important ones are the base register and the limit register, if we cover 90% of the territory, then we will achieve 90% of the validness. Combined together, the available `-l = 90% * -a`

## Question 5

> Can you run the simulator such that no virtual addresses are valid? How?

**Answer:**
Make limit == 0, then nothing will be valid.
