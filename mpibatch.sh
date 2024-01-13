#!/bin/bash
#SBATCH -N 1
#SBATCH -C cpu
#SBATCH -q regular
#SBATCH -t 12:00:00

#OpenMP settings:
export OMP_NUM_THREADS=1
export OMP_PLACES=threads
export OMP_PROC_BIND=spread
module load cray-mpich

mpicxx -o bf_mpi brute_force.cpp
#run the application:
g++ brute_force.cpp
#./a.out 4 1 5 2
srun -N 4 bf_mpi 4 2 5 2

