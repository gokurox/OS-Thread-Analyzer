#ifndef __MYTHREADS_h__
#define __MYTHREADS_h__

#include <pthread.h>
#include <assert.h>

/*
 *	@author: Gursimran Singh
 *	@rollNo: 2014041
 *
 *	"Pthread.h" contains the encapsulated functions of <pthread.h>. It also asserts that
 *	the return value is zero (0) for all functions while executing these functions.
 *
 */

void Pthread_mutex_init (pthread_mutex_t *m, const pthread_mutexattr_t *attr)
{
	int rc = pthread_mutex_init (m, attr);
	assert (rc == 0);
}

void Pthread_mutex_lock (pthread_mutex_t *m)
{
	int rc = pthread_mutex_lock (m);
	assert (rc == 0);
}

void Pthread_mutex_unlock (pthread_mutex_t *m)
{
	int rc = pthread_mutex_unlock (m);
	assert (rc == 0);
}

void Pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
{
	int rc = pthread_create (thread, attr, start_routine, arg);
	assert (rc == 0);
}

void Pthread_join (pthread_t thread, void **value_ptr)
{
	int rc = pthread_join (thread, value_ptr);
	assert (rc == 0);
}

#endif