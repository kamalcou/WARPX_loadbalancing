#!/bin/bash
#SBATCH -N 1
#SBATCH -C cpu
#SBATCH -q debug
#SBATCH -t 00:04:00

#OpenMP settings:
# export OMP_NUM_THREADS=1
# export OMP_PLACES=threads
# export OMP_PROC_BIND=spread

for i in {1..10}
do
    #run the application:
    g++ brute_force.cpp
    ./a.out 2 2 15 $i
done
