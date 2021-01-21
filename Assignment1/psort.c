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
//memory imports
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "sys/mman.h"
#include "fcntl.h"

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
 * Implementation for POSIX Merge Sort
 * Shared memory usage based on notes from Lecture 4 slide 13 
 * Based on Pseudo code given during lecture 5 (Pseudo Code 1)
 * Used the following link to shared memory : http://logan.tw/posts/2018/01/07/posix-shared-memory/
 * Used the following link to learn memcpy : https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
 */

void multiProcessMergeSort(int arr[], int left, int right) 
{
  int middle = (left+right) / 2;
  int size = sizeof(int) * (right + 1);

  // create share mem
  int shmid = shm_open("shm", O_CREAT|O_RDWR, 0666);
  ftruncate(shmid,size);
  //copy RIGHT side of local memory into shared mem
  int* shm = (int*)mmap(0, size, PROT_WRITE, MAP_SHARED, shmid, 0);
  memcpy(shm, &arr[0], size);

  switch(fork())
  {
    case -1:
      exit(-1);
    case 0: //sort one side -> detach from mem
      singleProcessMergeSort(shm, left, middle);
      munmap(shm, size);
      close(shmid);
      exit(0);
    case 1: //sort other side -> merge -> copy share mem to local
      singleProcessMergeSort(shm, middle+1, right);
      wait(NULL);
      merge(shm, left, middle, right);
      memcpy(&arr[left], shm, size);
      munmap(shm,size);
      close(shmid);
      shm_unlink("shm");
  }

}
