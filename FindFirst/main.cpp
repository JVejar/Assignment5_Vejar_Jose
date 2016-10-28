#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>
#include <omp.h>
using namespace std;

int checkArray(int *array, int arrayLength, int n, int gran, int minVal, int maxVal);

int main(int argc, char* argv[]){
  int numThreads,arrayLength, gran, minVal, maxVal, *array;
  struct timeval _start, _end;
  srand(time(0));
  arrayLength = atoi(argv[1]);
  numThreads = atoi(argv[2]);
  gran = atoi(argv[3]);
  double execTime=0.0;

 

  array = new int[arrayLength];

 // cout << "Array Values: ";
  for(int i=0; i < arrayLength; i++){
    array[i] = (rand() % 100) + 1;
   // cout << array[i] << " ";
  }

  
  gettimeofday(&_start, NULL);
  #pragma omp parallel
   {
    #pragma omp single
    {
      minVal = checkArray(array, arrayLength, 40, gran-1, 0, arrayLength-1);
    }
   }
  gettimeofday(&_end, NULL);

  execTime = (double)((_end.tv_sec - _start.tv_sec) + ((_end.tv_usec  - _start.tv_usec)/1000000.0));
   cout << endl << execTime << endl;
  return 0;
}


int checkArray(int *array, int arrayLength, int n, int gran, int minVal, int maxVal){
  int leftHalf, rightHalf, middle;
  middle = (minVal+maxVal)/2;

  if(maxVal - minVal <= gran){
     for(int i=minVal; i <= maxVal; i++){
       if(array[i] == n){
         return i;
       }
     }
    return arrayLength;
  }
  else{
   #pragma omp task shared(leftHalf)
     leftHalf = checkArray(array, arrayLength, n, gran, minVal, middle);
   #pragma omp task shared(rightHalf)
     rightHalf = checkArray(array, arrayLength, n, gran, middle+1, maxVal);
   #pragma omp taskwait
     if(leftHalf < rightHalf){
        return leftHalf;
     }
     else{
       return rightHalf;
     }
  }
}