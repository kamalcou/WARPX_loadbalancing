import numpy as np
import matplotlib.pyplot as plt

data=np.loadtxt("combinations.txt")
print(data.shape)
nr=data.shape[1]
times=data[:,nr-1]
x=np.arange(len(times))
times=np.sort(times)

plt.figure()
plt.plot(x,times[::-1])
plt.ylabel("Guessed time")
plt.xlabel("Index")
plt.savefig("time_vs_sol.png")
plt.show()

