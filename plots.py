import numpy as np
import matplotlib.pyplot as plt

plt.figure()
for i in range(1,11):

    data=np.loadtxt("combo_15_"+str(i)+"_it0.0.txt")
    nr=data.shape[1]
    times=data[:,nr-1]
    x=np.arange(len(times))
    times=np.sort(times)

    plt.plot(x,times[::-1],label=r"$\sigma$="+str(i),alpha=0.7)
plt.ylabel("Guessed time")
plt.xlabel("Index")
plt.legend()
plt.savefig("vary_sigma.png")
plt.show()

