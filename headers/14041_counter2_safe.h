#ifndef COUNTER2_H
#define COUNTER2_H

#include "14041_Pthread.h"

/*
 *	@author: Gursimran Singh
 *	@rollNo: 2014041
 *
 *	Implementing Counter 2
 *		Thread Safe Counter __ Using mutex lock
 *
 */


typedef struct _counter2_threadSafe {
	long count;						// The counter variable
	pthread_mutex_t cntLock;				// Mutex Lock
} counter2_t;

void cntr2_init (counter2_t *counter)
{
	Pthread_mutex_init (&(counter -> cntLock), NULL);	// Initialize Lock
	Pthread_mutex_lock (&(counter -> cntLock));		// Acquire Lock
	counter -> count = 0;					// Initialize Counter
	Pthread_mutex_unlock (&(counter -> cntLock));		// Release Lock
}

void cntr2_increment (counter2_t *counter)
{
	Pthread_mutex_lock (&(counter -> cntLock));		// Acquire Lock
	(counter -> count) ++;					// Increment Counter
	Pthread_mutex_unlock (&(counter -> cntLock));		// Release Lock
}

void cntr2_decrement (counter2_t *counter)
{
	Pthread_mutex_lock (&(counter -> cntLock));		// Acquire Lock
	(counter -> count) --;					// Decrement Counter
	Pthread_mutex_unlock (&(counter -> cntLock));		// Release Lock
}

long cntr2_get (counter2_t *counter)
{
	long TEMP;

	Pthread_mutex_lock (&(counter -> cntLock));		// Acquire Lock
	TEMP = (counter -> count);				// Read Counter Value
	Pthread_mutex_unlock (&(counter -> cntLock));		// Release Lock
	return TEMP;						// Return Counter Value
}

#endif