#include "merge.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

#define MAX_THREADS 4

int new_array[10];
//static int counter;

struct param{
  int *array;
  int left;
  int right;
  int thread_id;

};

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


void *setVariables(void *input){
  
 // printf("Thread ID is : %d\n",(int) pthread_self());
  multiThreadedMergeSort(((struct param*)input)->array, ((struct param*)input)->left, ((struct param*)input)->right);
  return 0;
}

void *split(void *input){
  pthread_t threads[2];

  int left = ((struct param*)input)->left;
  int right = ((struct param*)input)->right;
  int middle = (left + right)/2;

  if ((right - left) > 1){ 

  
 // int left_middle = (left + middle)/2;
 // int right_middle = (right + middle)/2;
 

  struct param *left_array = (struct param*)malloc(sizeof(struct param));
  struct param *right_array = (struct param*)malloc(sizeof(struct param));


  left_array->array = ((struct param*)input)->array;
  left_array->left = left;
  left_array->right = middle;
  

  right_array->array = ((struct param*)input)->array;
  right_array->left = middle + 1;
  right_array->right = right;
  pthread_create(&threads[0], NULL, setVariables, (void *)left_array);
  pthread_create(&threads[1], NULL, setVariables, (void *)right_array);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  }
  merge(((struct param*)input)->array, left, middle, right);

  return 0;

}


/*

Create  struct that hold array information and left/right values.
Create two threads, one to sort left hand side of array, one to sort right
using pthead_join to wait for both threads to complete, merge them.
 
 * This function stub needs to be completed
 */
void multiThreadedMergeSort(int arr[], int left, int right) 
{
  
  if(left == right){
    return;
  }

  int middle = (left + right)/2;
 

  if ((right - left) > 1)
  {  
  struct param *left_array = (struct param*)malloc(sizeof(struct param));
  struct param *right_array = (struct param*)malloc(sizeof(struct param));


  left_array->array = arr;
  left_array->left = left;
  left_array->right = middle;
  

  right_array->array = arr;
  right_array->left = middle + 1;
  right_array->right = right;
  
  
  pthread_t threads[MAX_THREADS];
    
  
  pthread_create(&threads[0], NULL, split, (void *)left_array);
  pthread_create(&threads[1], NULL, split, (void *)right_array);


  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  }

  merge(arr, left, middle, right);
  

}


