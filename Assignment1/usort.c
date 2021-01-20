/************************************************************************
 * 
 * CSE130 Winter 2021 Assignment 1
 * 
 * UNIX Shared Memory Multi-Process Merge Sort
 * 
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ************************************************************************/

#include "merge.h"
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>

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
 * This function stub needs to be completed
 */
void multiProcessMergeSort(int arr[], int left, int right) 
{
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

  //create shared memory 
  int shmid = shmget();
  //cattach to shared mem 
  int* shm = shmat (shmid, 0 , 0);
  int middle = right/2;

  //copy RIGHT side of local memory into shared mem
  memcpy(shm, arr[middle+1],sizeof(int) * (right - middle - 1 ));

  switch(fork()){
    case -1:
      exit(-1);
    case 0:
      //attach to shared mem
      //sort shared mem
      //detach from shared mem
    default:
      //sort LEFT side of LOCAL MEM
      //wait for child to finish
      //copy shared mem to RIGHT side of LOCAL MEM
      //desotry shared mem
      //merge LOCAL memory
  }

}
