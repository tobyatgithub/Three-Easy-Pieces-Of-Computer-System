import argparse
import platform
import shutil
import subprocess

import matplotlib.pyplot as plt
import numpy as np

parser = argparse.ArgumentParser()
parser.add_argument("pages", type=int, help="number of pages.")
parser.add_argument("epochs", type=int, help="number of epochs to run the experiment.")
args = parser.parse_args()

data = []
x = np.arange(args.pages)
pages = 2 ** x
for i in pages:
    r = subprocess.run(
        ["./tlb", str(i), str(args.epochs)], capture_output=True, check=True, text=True,
    )
    # print(r.stdout)
    process = r.stdout.split("elapsed = ")[1].split(" ")[0]
    data.append(float(process))

plt.plot(x, data, marker="x", color="green")
plt.margins(0.2)
# plt.xticks(x, pages, fontsize="x-small")
plt.xlabel("Numer of pages")
plt.ylabel("Time per access (ns)")
plt.show()
