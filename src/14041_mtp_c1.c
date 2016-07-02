#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/14041_Pthread.h"
#include "../headers/14041_counter1_nonsafe.h"

/*
 *	@author: Gursimran Singh
 *	@rollNo: 2014041
 *
 *	This program uses Counter 1 to count till TOP using 'thread_count' number of threads.
 *	thread_count = number of threads is passed in as a command line argument.
 *	
 *	Each thread counts till N = floor (TOP / thread_count). So sometimes counter stops before 1E09 but that's fine
 *	since we are measuring performance and 1E09 - 10 <= counter_max <= 1E09 which is just fine.
 *
 */

#define TOP 1E09L						// TOP Value of Counter

counter1_t CNTR;						// Counter 1 Object

void *thread_func (void *N)
{
	long thread_top = (long) N;
	long i;
	for (i = 0; i < thread_top; i++)
	{
		cntr1_increment (&CNTR);
	}
}

int main (int argc, char **argv)
{
	
	int i, thread_count;

	if (argc == 3)
		thread_count = atoi (argv[1]);
	else
		exit (0);

	FILE *outfile = fopen (argv[2], "a");						// Output FILE

	pthread_t thread_ref[thread_count];						// Create thread references

	long N = (long) floor (TOP / thread_count);					// Calculate N

	cntr1_init (&CNTR);								// Initialize Counter
	for (i = 0; i < thread_count; i++)
	{
		Pthread_create (&thread_ref[i], NULL, thread_func, (void *) N);		// Create thread_count threads
	}

	for (i = 0; i < thread_count; i++)
	{
		Pthread_join (thread_ref[i], NULL);					// Join all thread_count threads
	}
	
	printf ("\n"
		"2014041_mtp_c1.c:\n"
		"Counter Value after count: %ld\n"
		"\n", cntr1_get (&CNTR));

	fprintf (outfile,
		"\n"
		"2014041_mtp_c1.c:\n"
		"Counter Value after count: %ld\n"
		"\n", cntr1_get (&CNTR));

	fflush (outfile);
	fclose (outfile);
	outfile = NULL;

	return 0;
}