#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <omp.h>
using namespace std;

void mergeSort(int minVal, int maxVal, int *arrayA, int*arrayB);
void merge(int minVal, int middle, int arrayLength, int *arrayA, int *arrayB);

int arrayLength;

int main(int argc, char* argv[]){
  int numThreads, n, *arrayA, *arrayB;
  struct timeval _start, _end;
  n = 1000000000;
  double execTime = 0.0;  

  arrayLength = atoi(argv[1]);
  numThreads = atoi(argv[2]);

  arrayA = new int[n];
  arrayB = new int[n];

  srand(time(NULL));
  for(int i=0; i<n; i++){
    arrayA[i] = (rand()%100)+1;
  }

  gettimeofday(&_start, NULL);
 // #pragma omp parallel
  //{
    //#pragma omp single
    //{
       mergeSort(0, n, arrayA, arrayB);
    //}
  //}
  gettimeofday(&_end, NULL);
  
  execTime = (double)((_end.tv_sec - _start.tv_sec) + ((_end.tv_usec  - _start.tv_usec)/1000000.0));
  cout << endl << execTime << endl;
  return 0;
}


void mergeSort(int minVal, int maxVal, int *arrayA, int*arrayB){
  int middle;
  if(minVal != maxVal){
   #pragma omp parallel
   {
    middle = (minVal+maxVal)/2;
    #pragma omp task
     mergeSort(minVal, middle, arrayA, arrayB);
    #pragma omp task
     mergeSort(middle+1, maxVal, arrayA, arrayB);
    #pragma omp task
     merge(minVal, middle, (maxVal - minVal)+1, arrayA, arrayB);
   }
  }else{
    return;
  }
}
void merge(int minVal, int middle, int arrayLength, int *arrayA, int *arrayB){
  int minTemp, midTemp;
  minTemp = minVal;
  midTemp = middle + 1;

  for(int i=minVal; i < arrayLength; i++){
    if(arrayA[minTemp] < arrayA[midTemp]){
     arrayB[i] = arrayA[minTemp];
     minTemp++;
    }else if(arrayA[minTemp] > arrayA[midTemp]){
     arrayB[i] = arrayA[midTemp];
     midTemp++;
    }else{
     arrayB[i] = arrayA[minTemp];
     minTemp++;
    }
  }
  for(int i=minVal; i < arrayLength; i++){
   arrayA[i] = arrayB[i];
  }

}