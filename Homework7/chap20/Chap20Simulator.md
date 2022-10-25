# Homework Simulation Chapter 20 Smaller Pages

## Question 1

> With a linear page table, you need a single register to locate the page table, assuming that hardware does the lookup upon a TLB miss. How many registers do you need to locate a two-level page table? A three-level table?

**Answer:**

Based on figure 20.3, I believe only the top level page directory base registor is required (PDBR). 

## Question 2

> Use the simulator to perform translations given random seeds 0, 1, and 2, and check your answers using the -c flag. How many memory references are needed to perform each lookup?

**Answer:**

`python paging-multilevel-translate.py -s 0 -c`

Here I used a python debugger with config file to investigate the process (which is pretty much the same calculation as the textbook.)

As described in the function:

```python
def translate(self, pid, virtualAddr):
    (valid, ptPtr, pdeAddr) = self.getPageDirEntry(pid, virtualAddr, True)
    if valid == 1:
        ptePage = ptPtr
        (valid, pfn, pteAddr) = self.getPageTableEntry(virtualAddr, ptePage, True)
        if valid == 1:
            offset = (virtualAddr & self.OFFSET_MASK)
            paddr  = (pfn << self.pageBits) | offset
    # print('     --> pfn: %02x  offset: %x' % (pfn, offset))
            return paddr
        else:
            return -2
    return -1
```

here we first call `self.getPageDirEntry`, if valid then call the `self.getPageTableEntry`, and if valid, calculate the offset and actually page address in the end. 

And the memory involved methods are:
```python
pageDir = self.pdbr[pid]
pde     = self.memory[pdeAddr]
pte     = self.memory[pteAddr]
```
so three times.

## Question 3

> Given your understanding of how cache memory works, how do you think memory references to the page table will behave in the cache? Will they lead to lots of cache hits (and thus fast accesses?) Or lots of misses (and thus slow accesses)?

**Answer:**
By the figure 20.3, the top level page directory lookup will work well with temporal locality cache because we will revisit each top-level PFN multiple times. And the page table level lookup will be a little bit harder to cache (i.e. probably more cache misses) and will suit spatial locality cache beter because each PFN is not likely to be revisited but revisit will happen to other PFNs that is close to each other in the memory.