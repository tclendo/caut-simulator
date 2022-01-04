#!/bin/bash
#SBATCH --job-name=caut
#SBATCH --output=gol_ra2_2thr.out
#SBATCH --error=gol_ra2_2thr.err
#SBATCH --partition=fat
#SBATCH --time=00:40:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=28
#SBATCH --account=cis431_531

export OMP_NUM_THREADS=2

for i in {1..20} ; do ./caut inputs/ra2.caut 1 50 ; done
