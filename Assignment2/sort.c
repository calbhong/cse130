#include "merge.h"
#include "stdio.h"
#include "pthread.h"

int* array;
int split[5];
int thread_num[4];
pthread_t threads[2];

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


void* threadHelper(void* arg)
{
  int n = *((int*)arg);
  if (n == 0){
    singleThreadedMergeSort(array, split[n],split[n+1] );
    pthread_join(threads[0],NULL);
    merge(array, split[n], split[n+1], split[n+2]);
  }
  singleThreadedMergeSort(array, split[n] + 1, split[n+1]);
  if(n == 2){
    pthread_join(threads[1],NULL);
    merge(array, split[n] + 1, split[n+1], split[n+2]);
  }
  pthread_exit(NULL);
  return(NULL);
}

/* 
 * Multi Threaded Merge Sort
 * Helper Function Necessary for pthread_create()
 * Implementing Pseudocode 2 of Lecture 7 
 * Resrouces Used:
 * Lecture Secret Sauce
 * Office Hours
 * Gave up on using the struct but read this: https://www.educative.io/edpresso/how-to-sum-an-array-using-threading-in-c
 * 
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  array = arr;
  //split array into 4 quarters & adds index to array 
  split[0] = left;
  for(int i = 1; i<4; i++){
    split[i] = i*(left+right)/4;
    //printf("%d", split[i]);
  }
  split[4] = right;

  //assign thread numbers 
  for(int i = 0; i < 4; i++){
    thread_num[i] = i; 
  }

  pthread_t thread1, thread3;
  pthread_create(&thread1, NULL, &threadHelper, (void*)&thread_num[0]); //t1
  pthread_create(&threads[0], NULL, &threadHelper, (void*)&thread_num[1]); //t2
  pthread_create(&thread3, NULL, &threadHelper, (void*)&thread_num[2]); //t3
  pthread_create(&threads[1], NULL, &threadHelper, (void*)&thread_num[3]); //t4
  pthread_join(thread1, NULL);
  pthread_join(thread3, NULL); 

  merge(arr, left, split[2], right);

}
