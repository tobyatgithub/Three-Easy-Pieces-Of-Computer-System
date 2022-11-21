import random
import numpy as np
import matplotlib.pyplot as plt


asize = 1024  # address space size (e.g., 16, 64k, 32m, 1g)
psize = 16 * 1024  # physical memory size (e.g., 16, 64k, 32m, 1g)
uList = [0] * psize

for seed in range(500):
    random.seed(seed)
    for limit in range(psize):
        vaddr = int(random.random() * psize)
        if vaddr < limit:
            uList[limit] += 1

fig = plt.figure()
x = np.linspace(1, psize, psize)
plt.plot(x, [u / 500 for u in uList], color="red")
plt.ylim(0, 1.2)
plt.xlabel("Limit")
plt.ylabel("Valid fraction")
plt.show()

