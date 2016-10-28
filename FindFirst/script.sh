#!/bin/bash
# ==== Main ====


echo
echo "Time takes to find min in array using 1 Thread & Granularity 100000"
./main.o 100000000 1 100000
echo "Time takes to find min in array using 2 Thread & Granularity 100000"
./main.o 100000000 2 100000
echo "Time takes to find min in array using 4 Thread & Granularity 100000"
./main.o 100000000 4 100000
echo "Time takes to find min in array using 8 Thread & Granularity 100000"
./main.o 100000000 8 100000
echo "Time takes to find min in array using 16 Thread & Granularity 100000"
./main.o 100000000 16 100000
echo


exec 1>$PBS_O_WORKDIR/out 2?$PBS_O_WORKDIR/err