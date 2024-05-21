#!/bin/bash
#SBATCH -N 2
#SBATCH -C cpu
#SBATCH -q regular
#SBATCH -t 00:30:00

#OpenMP settings:
export OMP_NUM_THREADS=1
export OMP_PLACES=threads
export OMP_PROC_BIND=spread
module load cray-mpich

mpicxx -o bf_mpi brute_force.cpp
#run the application:
#./a.out 4 1 5 2
#srun -N 128 -n 6144 bf_mpi 6144 16 5 2
srun -N 2 -n 64 bf_mpi 64 16 15 2  #No of ranks=64 Nbox_per_rank=16 mean=15 stddev=2

