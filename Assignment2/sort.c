#include "merge.h"
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include <string.h>

int split[5];
pthread_t threads[4];

typedef struct data
{
  int* arr;
  int thread_num;
} data;

void* threadSort(void* arg)
{
  data* ptr = (data*) arg;
  int n = ptr->thread_num;
  int* array = ptr->arr;

  int x = 1;
  if (n == 0){
    x = 0;
  }

  singleThreadedMergeSort(array, split[n] + x ,split[n+1] );
  if(n%2==0){
    pthread_join(threads[x],NULL);
    merge(array, split[n] + x, split[n+1], split[n+2]);
  }
  pthread_exit(NULL);
  return(NULL);
}

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
 * Office Hours
 * 
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  struct data thread_data[4];
  //split array into 4 quarters
  split[0] = left;
  for(int i = 1; i<4; i++){
    split[i] = i*(left+right)/4;
    printf("%d", split[i]);
  }
  split[4] = right;



  for(int i = 0; i < 4; i++){
    &thread_data[i].arr = arr;
    &thread_data.thread_num = i;
  }
  
  

  pthread_create(&threads[0], NULL, &threadSort, &thread_data[0]);
  pthread_create(&threads[1], NULL, &threadSort, &thread_data[1]);
  pthread_create(&threads[2], NULL, &threadSort, &thread_data[2]);
  pthread_create(&threads[3], NULL, &threadSort, &thread_data[3]);
  pthread_join(threads[1], NULL);
  pthread_join(threads[3], NULL); 

  merge(arr, left, split[2], right);

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
