#!/bin/bash
# ==== Main ====


echo
echo "Time takes to perform MergeSort on an array of size 10^9 using 1 Thread"
./main.o 1000000000 1
echo "Time takes to perform MergeSort on an array of size 10^9 using 2 Threads"
./main.o 1000000000 2
echo "Time takes to perform MergeSort on an array of size 10^9 using 4 Threads"
./main.o 1000000000 4
echo "Time takes to perform MergeSort on an array of size 10^9 using 8 Threads"
./main.o 1000000000 8
echo "Time takes to perform MergeSort on an array of size 10^9 using 16 Threads"
./main.o 1000000000 16
echo


exec 1>$PBS_O_WORKDIR/out 2?$PBS_O_WORKDIR/err