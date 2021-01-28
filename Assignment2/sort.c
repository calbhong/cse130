#include "merge.h"
#include "stdio.h"
#include "pthread.h"

int* array;
int split[5];
int thread_num[5];
pthread_t thread1, thread2, thread3, thread4;

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
  if (n == 1){
    singleThreadedMergeSort(array, split[n-1], split[n]);
    pthread_join(thread2, NULL); //wait for t2 to sort
    merge(array, split[n-1], split[n], split[n+1]); //Left side
  }
  singleThreadedMergeSort(array, split[n-1] + 1, split[n]);
  if(n == 3){
    pthread_join(thread4, NULL); //wait for t4 to sort 
    merge(array, split[n-1] + 1, split[n], split[n+1]);//Right side 
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
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  array = arr; //for helper func to change
  //split array into 4 quarters & adds index to array 
  // [left, q1, middle, q3, right]
  split[0] = left;
  split[4] = right;
  for(int i = 1; i < 4; i++){
    split[i] = i*(left + right)/4;
    //printf("%d", split[i]);
  }

  //assign thread numbers (1, 2, 3, 4)
  for(int i = 1; i < 5; i++){ 
    thread_num[i] = i; 
  }

  
  pthread_create(&thread1, NULL, &threadHelper, (void*)&thread_num[1]); //t1
  pthread_create(&thread2, NULL, &threadHelper, (void*)&thread_num[2]); //t2
  pthread_create(&thread3, NULL, &threadHelper, (void*)&thread_num[3]); //t3
  pthread_create(&thread4, NULL, &threadHelper, (void*)&thread_num[4]); //t4

  //retrieve results of T1(left) & T3(right), then process merge
  pthread_join(thread1, NULL);
  pthread_join(thread3, NULL); 

  merge(arr, left, split[2], right);

}
