
/*********************************************************************
 *
 * Copyright (C) 2020 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ***********************************************************************/

#include "manpage.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>


#define MAX_THREADS 7


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int global;

struct param{
	int mid;
};

/* Set up global variable that starts at 0 and if mid = variable, then show paragraph, otherwise
wait until its that threads turn. Pass mid to pthread_create and then use cond_wait to wait until gloabl variable
= mid.
*/

void *getAndShow(void *input){



	int mid = getParagraphId();
//	printf("MID is %d\n", mid);

	pthread_mutex_lock(&mutex);

	
	while(mid != global)
	{
	//	printf("Checking global: %d\n", global);
	//	printf("MID: %d is waiting\n", mid);
		pthread_cond_wait(&cond, &mutex);
	//	printf("MID: %d has stopped waiting\n", mid);
	}	
//	printf("Outside while MID: %d \n", mid);
	
//	pthread_mutex_unlock(&mutex);
	
	

//	pthread_mutex_lock(&mutex);

//	printf(" MID is correct: %d, printing paragraph \n", mid);
	global++;
//	printf("Global is now: %d\n", global);
	showParagraph();
	pthread_cond_broadcast(&cond);

	pthread_mutex_unlock(&mutex);


	return 0;
}


/*
 * See manpage.h for details.
 *
 * As supplied, shows random single messages.
 */
void manpage()  
{
  
  pthread_t threads[MAX_THREADS];
  global = 0;

  for (int i = 0; i < 7; i++)
  {  	

	
	  
	pthread_create(&threads[i], NULL, getAndShow, NULL);
//	pthread_join(threads[i], NULL);
  }


  for(int i = 0; i < 7; i++)
  {
  	pthread_join(threads[i], NULL);
  }

}
