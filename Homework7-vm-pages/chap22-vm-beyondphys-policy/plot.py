import numpy as np
import matplotlib.pyplot as plt

cacheSizes = np.arange(1, 5)
policies = ["FIFO", "LRU", "OPT", "UNOPT", "RAND", "CLOCK"]
hitRate = [
    [60.67, 86.24, 94.39, 98.72],
    [60.79, 90.73, 95.76, 99.11],
    [60.79, 90.77, 97.49, 99.41],
    [60.79, 61.04, 61.10, 61.34],
    [60.79, 86.75, 95.34, 98.08],
    [60.79, 87.72, 95.89, 98.84]
]

for i in range(len(policies)):
    plt.plot(cacheSizes, hitRate[i])

plt.legend(policies)
plt.xlabel("Cache sizes")
plt.ylabel("Hitrate")
plt.savefig("hitrate-compare.png")