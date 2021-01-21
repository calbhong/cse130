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
//memory imports
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
 * Implementation for UNIX Merge Sort
 * Shared memory usage based on notes from Lecture 4
 * Based on Pseudo code given during lecture 5
 * Used the following link to learn memcpy : https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
 */
void multiProcessMergeSort(int arr[], int left, int right) 
{

  int middle = (left+right) / 2;
  int size = sizeof(int) * (middle + 1);
  //create shared memory, size of right side of array 
  int shmid = shmget(IPC_PRIVATE, size, 0666|IPC_CREAT);
  //attach to shared mem (do i need to typecast on shmat?)
  int* shm = (int*)shmat(shmid, (void*)0, 0);
  
  //copy RIGHT side of local memory into shared mem
  memcpy(shm, &arr[middle+1],size);

  switch(fork())
  {
    case -1:
      exit(-1);
    case 0:
      //attach to shared mem
      shm = (int*)shmat(shmid, (void*)0, 0);
      //sort shared mem
      singleProcessMergeSort(shm, 0, middle);
      //detach from shared mem
      shmdt(shm);
      exit(0);
    default:
      //sort LEFT side of LOCAL MEM
      singleProcessMergeSort(arr, left, middle);
      //wait for child to finish
      wait(NULL);
      //copy shared mem to RIGHT side of LOCAL MEM
      memcpy(&arr[middle + 1], shm, size);
      //detach from shared mem
      shmdt(shm);
      //destroy shared mem
      shmctl(shmid, IPC_RMID, NULL);
      merge(arr, left, middle, right);
  }
}
