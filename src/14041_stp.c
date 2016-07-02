#include <stdio.h>
#include <stdlib.h>
#include "../headers/14041_counter1_nonsafe.h"

/*
 *	@author: Gursimran Singh
 *	@rollNo: 2014041
 *
 *	This program uses Counter 1 to count till TOP using a single thread.
 *	Theoretically this should be fast and should produce the correct output also.
 *
 */

#define TOP 1E09L					// TOP Value of the Counter

counter1_t CNTR;					// Counter 1 Object

void *thread_func (void *arg)
{
	long i;
	for (i = 0; i < TOP; i++)
	{
		cntr1_increment (&CNTR);
	}
}

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		printf ("ERROR: stp.c .. Expected 2 arguments got %d\n", argc);
		exit (0);
	}

	FILE *outfile = fopen (argv[1], "a");		// Output File

	cntr1_init (&CNTR);				// Initialize Counter
	thread_func (NULL);				// Call the function normally. No arguments required here
	
	printf ("\n"
		"2014041_stp.c:\n"
		"Counter Value after count: %ld\n"
		"\n", cntr1_get (&CNTR));

	fprintf (outfile,
		"\n"
		"2014041_stp.c:\n"
		"Counter Value after count: %ld\n"
		"\n", cntr1_get (&CNTR));

	fflush (outfile);
	fclose (outfile);
	outfile = NULL;

	return 0;
}