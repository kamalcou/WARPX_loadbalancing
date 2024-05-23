import numpy as np

'''
For answers to be the same there must be the same number of two different ranks
'''
data = np.loadtxt('combo_15_2_it0.0.txt')
# print(data)

# Create an empty list to store unique rows
unique_data = []

# Create a set to track seen values in the last column
seen = set()

# Iterate through the rows in the data
for row in data:
    # Check if the last column value is already in the seen set
    if row[-1] not in seen:
        # If not, add the row to unique_data and add the last column value to seen
        unique_data.append(row)
        seen.add(row[-1])

# Write the unique rows to a file
with open('perm_15_2.txt', 'w') as file:
    for row in unique_data:
        file.write(' '.join(map(str, row)) + '\n')

print("Unique rows have been written to 'perm_15_2.txt'.")


# f = open('perm_2_6.txt','w')
# N=len(data[:,0])
# L=len(data[0,:])-1
# print(N,L)
# for i in range(100):
#     write=True
#     combo=data[i,:L]
#     ranks,freq=np.unique(combo, return_counts=True)
#     for r in range(len(ranks)):
#         for rr in range(len(ranks)):
#             if(freq[r]==freq[rr] and r!=rr and r>rr and ranks[r]<ranks[rr]): #if frequency of rank is the same but not same rank
#                 write=False

#     if (write==True):
#         for j in range(L+1):
#             if (j<L):
#                 f.write(str(int(data[i,j])))
#             else:
#                 f.write(str(data[i,j]))
#             f.write(" ")
#         f.write('\n')
# f.close()
