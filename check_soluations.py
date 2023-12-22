'''every solution in full answer should also be in norep''' 

import numpy as np

full=np.loadtxt("combo_50_2_it0.txt")
norep=np.loadtxt("norep_50_2_it0.txt")

fs=full[:,4]
nrs=norep[:,4]
j=0
for i in range(len(fs)):
    if (len(list(filter (lambda x : x == fs[i], nrs))) == 0):
        print("there is a soluation missing from norep solution")
