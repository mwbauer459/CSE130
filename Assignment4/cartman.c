
#include "cartman.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
 
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t semtex; 
bool availability[5];
int global; 

 
struct carts{
	int val;
	enum track track;
	enum junction junc1;
	enum junction junc2;

};



void* runCart(void *input)
{
	

	int val = ((struct carts*)input)->val;
	int track = ((struct carts*)input)->track;
	int junc1 = ((struct carts*)input)->junc1;
	int junc2 = ((struct carts*)input)->junc2;


	pthread_mutex_lock(&mutex);

		
	unAvailable(junc1);
	unAvailable(junc2);


	
	reserve(val, junc1);
	reserve(val, junc2);

	
	cross(val, track, junc1);

	

	return 0;
}


void makeAvailable(enum junction junction)
{
	availability[junction] = true;
}

void unAvailable(enum junction junction)
{
	availability[junction] = false;
}

bool getAvailability(enum junction junction) 
{
	return availability[junction];
}

/*
 * You need to implement this function, see cartman.h for details 
 */
void arrive(unsigned int cart, enum track track, enum junction junction) 
{

	//printf("CART %d is ARRIVING with track: %d, jucntion: %d\n", cart, track, junction);

	pthread_t thr;
	int trk = track;
	int junc2;

	if(junction == trk)
	{
		
		if(junction == 4)
		{
			junc2 = 0;
		}
		else
		{
			junc2 = junction + 1;
		}	
	}
	else
	{
		if(junction ==0)
		{
			junc2 = 4;
		}
		else
		{
			junc2 = junction -1;
		}	
	}
	struct carts crt = {cart, track, junction, junc2};

	
	pthread_create(&thr, NULL, runCart, (void *)&crt);

	pthread_join(thr, NULL);


}

/*
 * You need to implement this function, see cartman.h for details 
 */
void depart(unsigned int cart, enum track track, enum junction junction) 
{
	
	//printf("CART %d is DEPARTING with track: %d, jucntion: %d\n", cart, track, junction);
	int junc1;
	int junc2;
	int trk = track;


	if(junction == trk)
	{
		if(junction ==4)
		{
			junc1 = 0;
			junc2 = junction;
		}
		else
		{
			junc1 = junction + 1 ;
			junc2 = junction;
		}

	}	
	else{

		if(junction == 0)
		{
			junc1 = 4;
			junc2 = 0;
		}
		else
		{
			junc1 = junction - 1;
			junc2 = junction;
		}
	}		
	release(cart, junc1);
//	//printf("release %d\n", junc1);
	release(cart, junc2);
//	//printf("release %d\n", junc2);

	pthread_mutex_unlock(&mutex);
	makeAvailable(junction);
	makeAvailable(junc2);


}

/*
 * You need to implement this function, see cartman.h for details 
 */
void cartman() 
{

	for(int i = 0; i< 5; i++)
	{
		availability[i] = true;
	}

	global = 0;
	
	sem_init(&semtex, 0, 2);

  
}

