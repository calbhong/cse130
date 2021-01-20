/************************************************************************
 * 
 * CSE130 Winter 2021 Assignment 1
 *  
 * POSIX Shared Memory Multi-Process Merge Sort
 * 
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ************************************************************************/

#include "merge.h"

/* LEFT index and RIGHT index of the sub-array of ARR[] to be sorted */
void singleProcessMergeSort(int arr[], int left, int right) 
{
  if (left < right) {
    int middle = (left+right)/2;
    singleProcessMergeSort(arr, left, middle); 
    singleProcessMergeSort(arr, middle+1, right); 
    merge(arr, left, middle, right); 
  } 
}

/*
*fork
*if error
*   exit
*if child
*   sort one side
*   exit 
*if parent
*   sort other side
*   wait for child to finish
*   merge
*/

void multiProcessMergeSort(int arr[], int left, int right) 
{

  // create share mem
  // attach shared mem
  
  switch(fork()){
    case -1:
      exit(-1);
    case 0:
      //attach to shared mem
      //sort shared mem
      singleProcessMergeSort(shm, 0, right - middle - 1);
      //detach from shared mem
      exit(0);
    case 1:
      //sort LEFT side of LOCAL MEM
      singleProcessMergeSort(arr, left, middle);
      //wait for child to finish
      wait(NULL);
      //copy shared mem to RIGHT side of LOCAL MEM
      memcpy(arr[middle + 1], shm, sizeof(shm));
      //desotry shared mem
      //merge LOCAL mem
      merge(arr, left, right / 2, right);

  }
}
