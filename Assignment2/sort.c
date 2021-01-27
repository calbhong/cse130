#include "merge.h"
#include "stdio.h"
#include "pthread.h"

/* LEFT index and RIGHT index of the sub-array of ARR[] to be sorted */
void singleThreadedMergeSort(int arr[], int left, int right) 
{
  if (left < right) {
    int middle = (left+right)/2;
    singleThreadedMergeSort(arr, left, middle); 
    singleThreadedMergeSort(arr, middle+1, right); 
    merge(arr, left, middle, right); 
  } 
}

/* 
 * Multi Threaded Merge Sort
 * Helper Function Necessary for pthread_create()
 * Resrouces Used:
 * Lecture Secret Sauce
 * 
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  
  int i = 0;
  

  /* P splits array into 4 
  * P creates four threads to sort a 1/4 of the array each
  * T1 waits for T2 to finish
  *   Then merges left-left and left-right (T1 * T2)
  * T3 waits for T4 to finish 
  *   then merges right-left and right right (T3*T4)
  *  P waits for T1 and T3 to finish
  * then merge final
  */ 

  //Can make it a pyramid where T1 & T2 are used to merge
  //T3 - T6 are used to actually sort and merge again

  /*
  * P splits array into four
  * P create THREE threads to sort a 1/4 of each
  * P sorts the remaining 1/4
  * P waits for T1 to finish
  *   then merges left-left & left-right
  * T2 waits for T3 to finish
  *   then merges right-left and right right
  * P waits for T2 to finish
  * P merges left and right
  */
 

}
