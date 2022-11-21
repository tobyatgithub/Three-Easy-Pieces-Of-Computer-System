#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n[1000000];
    int i;
    printf("hello, I am running with (pid:%d)\n", (int)getpid());
    while (1)
    {
        for (i = 0; i < 1000000; i++) {
            n[i] = i + 100;
            // printf("running");
        }
        /* humm how to allocate a lot of memory? other than make the n array larger??? */
    }
    
    return 0;
}

/* 
free -m
While running:
              total        used        free      shared  buff/cache   available
Mem:          15929         864       13790           0        1273       14786
Swap:          4096           0        4096

While not running:
              total        used        free      shared  buff/cache   available
Mem:          15929         861       13794           0        1273       14789
Swap:          4096           0        4096


pmap
     Address Perm   Offset Device Inode Size  Rss  Pss Referenced Anonymous LazyFree ShmemPmdMapped FilePmdMapped Shared_Hugetlb Private_Hugetlb Swap SwapPss Locked THPeligible Mapping
561060a00000 r-xp 00000000  08:20 44840    4    4    4          4         0        0              0             0              0               0    0       0      0           0 memory-user
561060c00000 r--p 00000000  08:20 44840    4    4    4          4         4        0              0             0              0               0    0       0      0           0 memory-user
561060c01000 rw-p 00001000  08:20 44840    4    4    4          4         4        0              0             0              0               0    0       0      0           0 memory-user
561062380000 rw-p 00000000  00:00     0  132    4    4          4         4        0              0             0              0               0    0       0      0           0 [heap]
7f74fb769000 r-xp 00000000  08:20 40245 1948 1244   59       1244         0        0              0             0              0               0    0       0      0           0 libc-2.27.so
7f74fb950000 ---p 001e7000  08:20 40245 2048    0    0          0         0        0              0             0              0               0    0       0      0           0 libc-2.27.so
7f74fbb50000 r--p 001e7000  08:20 40245   16   16   16         16        16        0              0             0              0               0    0       0      0           0 libc-2.27.so
7f74fbb54000 rw-p 001eb000  08:20 40245    8    8    8          8         8        0              0             0              0               0    0       0      0           0 libc-2.27.so
7f74fbb56000 rw-p 00000000  00:00     0   16   12   12         12        12        0              0             0              0               0    0       0      0           0
7f74fbb5a000 r-xp 00000000  08:20 40235  164  152    6        152         0        0              0             0              0               0    0       0      0           0 ld-2.27.so
7f74fbd79000 rw-p 00000000  00:00     0    8    8    8          8         8        0              0             0              0               0    0       0      0           0
7f74fbd83000 r--p 00029000  08:20 40235    4    4    4          4         4        0              0             0              0               0    0       0      0           0 ld-2.27.so
7f74fbd84000 rw-p 0002a000  08:20 40235    4    4    4          4         4        0              0             0              0               0    0       0      0           0 ld-2.27.so
7f74fbd85000 rw-p 00000000  00:00     0    4    4    4          4         4        0              0             0              0               0    0       0      0           0
7ffcd1d6c000 rw-p 00000000  00:00     0 3924 3920 3920       3920      3920        0              0             0              0               0    0       0      0           1 [stack]
7ffcd21d5000 r--p 00000000  00:00     0   16    0    0          0         0        0              0             0              0               0    0       0      0           0 [vvar]
7ffcd21d9000 r-xp 00000000  00:00     0    4    4    0          4         0        0              0             0              0               0    0       0      0           0 [vdso]
                                        ==== ==== ==== ========== ========= ======== ============== ============= ============== =============== ==== ======= ====== ===========
                                        8308 5392 4057       5392      3988        0              0             0              0               0    0       0      0           1 KB
 */