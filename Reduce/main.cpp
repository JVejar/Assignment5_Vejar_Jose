#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <cmath>
#include <omp.h>

using namespace std;
int reduce(int* array, int arrayLength);
int gran = 1;
int main(int argc, char* argv[]){
  int arrayLength, numThreads, min,  *array;
  struct timeval _start, _end;
  double execTime = 0.0;
  
  arrayLength = atoi(argv[1]);
  numThreads = atoi(argv[2]);
  gran = atoi(argv[3]);

  array = new int[arrayLength];

  //cout << "Array Values: ";
  srand(time(NULL));
  #pragma omp parallel for
  for(int i=0; i<arrayLength; i++){
    array[i] = (rand()%100)+1;
    //cout << array[i] << " , ";
  }
  
  gettimeofday(&_start, NULL);
  #pragma omp parallel
  {
    #pragma omp single
    {
     min = reduce(array, arrayLength);
    }
  }
  gettimeofday(&_end, NULL);

  execTime = ((_end.tv_sec - _start.tv_sec) + ((_end.tv_usec  - _start.tv_usec)/1000000.0));

  cout << "Time taken to find the minimum value in the array is: " << execTime << " milliseconds." << "\n";

  cout << "\n\n";
  return 0;
}

int reduce(int* array, int arrayLength){
   int temp, min;
   int *arrFirstHalf, *arrSecondHalf;
   int f_halfMin, f_halfSize, s_halfMin, s_halfSize;

   f_halfMin=0; s_halfMin=0;
   f_halfSize = arrayLength/2;  s_halfSize = arrayLength - f_halfSize;  //f_halfSize is the first half of array, s_halfSize is the second half of the array

   if(arrayLength<=gran){
      min = array[0]; //sets the minimum of the array to the first position in the array
      for(int i=1; i<arrayLength; i++){
         if(array[i] < min){
            min = array[i];  //sets the minimum value of the array to the array at position i if array[i] is less than the original min
         }
      }
      return min;
   }

  arrFirstHalf = new int[f_halfSize]; //holds the first half of the array
  arrSecondHalf = new int[s_halfSize]; //holds the second half of the array

  if(f_halfSize < s_halfSize){
    temp = s_halfSize;
  }else{
    temp = f_halfSize;
  }

  #pragma omp parallel for  
  for(int i=0; i<temp; i++){
      if(i < f_halfSize){
         arrFirstHalf[i] = array[i];
      }
      else{
         arrSecondHalf[i] = array[f_halfSize + i];
      }
    }

  #pragma omp parallel
  {
    #pragma omp task shared(f_halfMin)
    {
      f_halfMin = reduce(arrFirstHalf, f_halfSize);  //start task to find the minimum of the first half of the array
    }

    #pragma omp task shared(s_halfMin)
    {
      s_halfMin = reduce(arrSecondHalf, s_halfSize); //start task to find the minimum of the second half of the array
    }
 

 }
 
  //used to check if the minimum value of the first half of the array is smaller than the minimum value of the second half of the array
   if(f_halfMin < s_halfMin){
     return f_halfMin; //first half minimum of the array is smaller than the second half's minimum, therefore return the smaller half
   }else{
     return s_halfMin; //second half minimum of the array is smaller than the first half's minimum, therefore return the smaller half
  }
}