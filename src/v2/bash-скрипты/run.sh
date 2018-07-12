#!/bin/sh
# Run algorithm for experiments

DATA=$2
M=$1
N=$3

for i in 0
do
	echo "number of a  series of experiments = $i"
	echo "count of threads = 1"
	srun main.phi $M $DATA $N 1
	echo "count of threads = 34"
	srun main.phi $M $DATA $N 34
	echo "count of threads = 68"
	srun main.phi $M $DATA $N 68
	echo "count of threads = 136"
	srun main.phi $M $DATA $N 136
	echo "count of threads = 204"
	srun main.phi $M $DATA $N 204
	echo "count of threads = 272"
	srun main.phi $M $DATA $N 272
done