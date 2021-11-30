#!/bin/bash
#SBATCH --job-name=caut
#SBATCH --output=gol_ra2_%j.out
#SBATCH --error=gol_ra2_%j.out
#SBATCH --partition=fat
#SBATCH --time=00:40:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=28
#SBATCH --account=cis431_531

export OMP_NUM_THREADS=1
echo "1 Thread"
./caut input/ra1.caut 1 10

export OMP_NUM_THREADS=2
echo "2 Threads"
./caut input/ra1.caut 1 10

export OMP_NUM_THREADS=4
echo "4 Threads"
./caut input/ra1.caut 1 10

export OMP_NUM_THREADS=8
echo "8 Threads"
./caut input/ra1.caut 1 10

export OMP_NUM_THREADS=16
echo "16 Threads"
./caut input/ra1.caut 1 10

export OMP_NUM_THREADS=28
echo "28 Threads"
./caut input/ra1.caut 1 10
