import numpy as np

'''
For answers to be the same there must be the same number of two different ranks
'''
data = np.loadtxt('combo_2_6.txt')
f = open('perm_2_6.txt','w')
N=len(data[:,0])
L=len(data[0,:])-1
for i in range(100):
    write=True
    combo=data[i,:L]
    ranks,freq=np.unique(combo, return_counts=True)
    for r in range(len(ranks)):
        for rr in range(len(ranks)):
            if(freq[r]==freq[rr] and r!=rr and r>rr and ranks[r]<ranks[rr]): #if frequency of rank is the same but not same rank
                write=False

    if (write==True):
        for j in range(L+1):
            if (j<L):
                f.write(str(int(data[i,j])))
            else:
                f.write(str(data[i,j]))
            f.write(" ")
        f.write('\n')
f.close()
