/************************************************************************
 * 
 * CSE130 Winter 2021 Assignment 1
 *
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ************************************************************************/

/* 
 * Merges two sub-arrays of ARR[]
 * First sub-array is ARR[LEFT....MIDDLE] 
 * Second sub-array is ARR[MIDDLE+1..RIGHT] 
 *
 * This function is provided, you do not need to write it.
 */
void merge(int arr[], int left, int middle, int right);

/* 
 * Merge Sort in the current process a sub-array of ARR[] defined by the 
 * LEFT index and RIGHT indexes.
 * 
 * This function is provided, you do not need to write it.
 */
void singleProcessMergeSort(int arr[], int left, int right); 

/* 
 * Merge Sort in the current process and at least one child process a 
 * sub-array of ARR[] defined by the LEFT index and RIGHT indexes.
 * 
 * A function stub is provided, but you need to develop an implementation.
 */
void multiProcessMergeSort(int arr[], int left, int right); 