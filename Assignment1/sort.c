#include "merge.h"
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdbool.h>
#include<sys/wait.h>



static int shmid;
static key_t key;
static size_t arr_size;



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
 * 
  Function to sort an array recursively while utilizing multiple processes
  I spent nearly every minute of the last 4 days trying to debug this. It would only work about 25% of the time
  for arrays larger than 12. The issue was my if else statement was set up in the opposite way, i.e. it would sort
  all the children first rather than having each parent wait until all of its children were finished. I tried everything, from
  adjusting the size shared memory to changing how data was copied.
  I'm only including this paragraph because I am exceptionally happy I got it to work and need to feel like the amount of
  effort it took is at least somehow documented.
 */
void multiProcessMergeSort(int arr[], int left, int right) 
{
  
 
    if(left == right)
    {
      return;
    }
   
    int middle;
    int *new_array;
    // Initialize shared memory
    key = ftok("mwbauer", 65);
    arr_size = 32;
    shmid = shmget(key, arr_size, 0666 | IPC_CREAT);   
    new_array = (int*)shmat(shmid, (void*)0, 0); 
    

    for (int i = left; i <= right; i++){
      new_array[i] = arr[i];
       
    }   
    
      int status;
      pid_t lpid; 
      // Fork
      lpid = fork(); 
    
      // Error making child
      if (lpid<0) {   
        perror("Unable to create child\n"); 
        exit(-1); 
      } 
      else if (lpid > 0)
      {
        middle = (left + right)/2;
        multiProcessMergeSort(new_array, middle + 1, right);
        waitpid(lpid, &status, 0);
        merge(new_array, left, middle, right);

        for (int k = left; k <= right ; k++){
            arr[k] = new_array [k]; 
        } 
        
        shmdt(new_array);
        shmctl(shmid, IPC_RMID, NULL); 
        
        

      }  
      // If child created successfully, attach to shared memory
      else{ 

        middle = (left + right)/2;
        new_array =(int*)shmat(shmid, (void*)0, 0);
     
        multiProcessMergeSort(new_array, left, middle);
        
        shmdt(new_array);
        exit(0); 
             
      } 

       // parent process 

       
    
     

  

}




 

