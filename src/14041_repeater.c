#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
 *	@author: Gursimran Singh
 *	@rollNo: 2014041
 *
 *	This is a driver program that calls all the other programs on the basis of command-line arguments.
 *	Program iterates numberOfThreads from 1 to 10.
 *	Program repeates a program for each value of numberOfThreads, numberOfRepeats time.
 *
 */

char *filepath = NULL;
FILE *outfile = NULL;

double execute (char **Args, long pass)
{
	double time_taken, start_t, end_t;
	int rc;

	start_t = time(0);
	
	// printf ("Start Time = %lf\n", start_t);
	// fprintf (outfile, "Start Time = %lf\n", start_t);
	
	printf ("STARTING PASS %ld\n", pass);
	fprintf (outfile, "STARTING PASS %ld\n", pass);

	fflush (outfile);
	fclose (outfile);

	rc = fork ();
	if (rc < 0)
	{
		printf ("EXITING...\n");
		exit (0);
	}
	else if (rc > 0)
	{
		wait (NULL);
		end_t = time(0);
		
		// printf ("End Time = %lf\n", end_t);
		// fprintf (outfile, "End Time = %lf\n", end_t);
	}
	else if (rc == 0)
	{
		execv (Args[0], Args);
		printf ("EXEC NOT WORKING\n");
		exit(0);
	}

	time_taken = end_t - start_t;

	outfile = fopen (filepath, "a");
	
	printf ("Time Taken for pass %ld = %lf seconds\n\n", pass, time_taken);
	fprintf (outfile, "Time Taken for pass %ld = %lf seconds\n\n", pass, time_taken);

	return time_taken;
}

int main (int args, char **argv)
{
	long choice, numberOfRepeats; 
	long numberOfThreads = 1;
	double average_time;
	char *program, *filename;
	filepath = strdup ("./Statistics/");

	if (args != 4)
	{
		printf ("ERROR: CANT RUN FURTHER\n");
		exit (0);
	}

	// printf ("Which File to run ??\n");
	// printf ("1. Single Threaded Program __ Counter 1\n");
	// printf ("2. Multi-Threaded Program __ Counter 1\n");
	// printf ("3. Multi-Threaded Program __ Counter 2\n");
	// printf ("4. Multi-Threaded Program __ Counter 1 __ Semaphores\n");
	// printf ("5. Exit\n");
	//scanf ("%ld", &choice);

	//printf ("How many time to repeat the program ??: ");
	//scanf ("%ld", &numberOfRepeats);

	//printf ("Output filename ??: ");
	//scanf ("%s", filename);

	choice = atoi (argv[1]);
	numberOfRepeats = atoi (argv[2]);
	filename = strdup (argv[3]);
	strcat (filepath, filename);

	outfile = fopen (filepath, "w");

	switch (choice)
	{
		case 1:
		{	
			long i = 0;
			char *Args[3];
			average_time = 0;
			numberOfThreads = 1;

			program = strdup ("Single Thread __ Counter 1");
			Args[0] = strdup ("./exec/14041_stp.out");
			Args[1] = strdup (filepath);
			Args[2] = NULL;

			printf ("\n"
				"STARTING EXECUTION:\n"
				"PROGRAM: %s\n"
				"NUMBER OF REPEATS: %ld\n"
				"NUMBER OF THREADS: %ld\n"
				"\n", program, numberOfRepeats, numberOfThreads);

			fprintf (outfile,
				"\n"
				"STARTING EXECUTION:\n"
				"PROGRAM: %s\n"
				"NUMBER OF REPEATS: %ld\n"
				"NUMBER OF THREADS: %ld\n"
				"\n", program, numberOfRepeats, numberOfThreads);

			for (i = 0; i < numberOfRepeats; i++)
			{
				average_time += execute (Args, i +1);
			}

			average_time /= numberOfRepeats;

			printf ("\n"
				"Statistics:\n"
				"PROGRAM: %s\n"
				"NUMBER OF REPEATS: %ld\n"
				"NUMBER OF THREADS: %ld\n"
				"AVERAGE TIME TAKEN: %lf seconds\n"
				"\n", program, numberOfRepeats, numberOfThreads, average_time);

			fprintf (outfile,
				"\n"
				"Statistics:\n"
				"PROGRAM: %s\n"
				"NUMBER OF REPEATS: %ld\n"
				"NUMBER OF THREADS: %ld\n"
				"AVERAGE TIME TAKEN: %lf seconds\n"
				"\n", program, numberOfRepeats, numberOfThreads, average_time);
			
			break;
		}
		case 2:
		{
			long i = 0;
			char *Args[4];
			char TEMP[20];

			//printf ("How many threads to create ??: ");
			//scanf ("%ld", &numberOfThreads);

			program = strdup ("Multiple Threads __ Counter 1");

			for (numberOfThreads = 1; numberOfThreads <= 10; numberOfThreads ++)
			{
				printf ("\n"
					"STARTING EXECUTION:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"\n", program, numberOfRepeats, numberOfThreads);

				fprintf (outfile,
					"\n"
					"STARTING EXECUTION:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"\n", program, numberOfRepeats, numberOfThreads);

				average_time = 0;
				sprintf (TEMP, "%ld", numberOfThreads);

				Args[0] = strdup ("./exec/14041_mtp_c1.out");
				Args[1] = strdup (TEMP);
				Args[2] = strdup (filepath);
				Args[3] = NULL;

				for (i = 0; i < numberOfRepeats; i++)
				{
					average_time += execute (Args, i +1);
				}

				average_time /= numberOfRepeats;

				printf ("\n"
					"Statistics:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"AVERAGE TIME TAKEN: %lf seconds\n"
					"\n", program, numberOfRepeats, numberOfThreads, average_time);

				fprintf (outfile,
					"\n"
					"Statistics:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"AVERAGE TIME TAKEN: %lf seconds\n"
					"\n", program, numberOfRepeats, numberOfThreads, average_time);
			}
			break;
		}
		case 3:
		{	
			long i = 0;
			char *Args[4];
			char TEMP[20];

			// printf ("How many threads to create ??: ");
			// scanf ("%ld", &numberOfThreads);
	
			program = strdup ("Multiple Threads __ Counter 2");

			for (numberOfThreads = 1; numberOfThreads <= 10; numberOfThreads ++)
			{
				printf ("\n"
					"STARTING EXECUTION:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"\n", program, numberOfRepeats, numberOfThreads);

				fprintf (outfile,
					"\n"
					"STARTING EXECUTION:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"\n", program, numberOfRepeats, numberOfThreads);

				average_time = 0;
				sprintf (TEMP, "%ld", numberOfThreads);

				Args[0] = strdup ("./exec/14041_mtp_c2.out");
				Args[1] = strdup (TEMP);
				Args[2] = strdup (filepath);
				Args[3] = NULL;

				for (i = 0; i < numberOfRepeats; i++)
				{
					average_time += execute (Args, i +1);
				}

				average_time /= numberOfRepeats;

				printf ("\n"
					"Statistics:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"AVERAGE TIME TAKEN: %lf seconds\n"
					"\n", program, numberOfRepeats, numberOfThreads, average_time);

				fprintf (outfile,
					"\n"
					"Statistics:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"AVERAGE TIME TAKEN: %lf seconds\n"
					"\n", program, numberOfRepeats, numberOfThreads, average_time);
			}
			break;
		}
		case 4:
		{
			long i = 0;
			char *Args[4];
			char TEMP[20];

			//printf ("How many threads to create ??: ");
			//scanf ("%ld", &numberOfThreads);

			program = strdup ("Multiple Threads __ Counter 1 __ Semaphores");

			for (numberOfThreads = 1; numberOfThreads <= 10; numberOfThreads ++)
			{
				average_time = 0;
				sprintf (TEMP, "%ld", numberOfThreads);

				
				Args[0] = strdup ("./exec/14041_mtp_c1_sem.out");
				Args[1] = strdup (TEMP);
				Args[2] = strdup (filepath);
				Args[3] = NULL;

				printf ("\n"
					"STARTING EXECUTION:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"\n", program, numberOfRepeats, numberOfThreads);

				fprintf (outfile,
					"\n"
					"STARTING EXECUTION:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"\n", program, numberOfRepeats, numberOfThreads);

				for (i = 0; i < numberOfRepeats; i++)
				{
					average_time += execute (Args, i +1);
				}

				average_time /= numberOfRepeats;

				printf ("\n"
					"Statistics:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"AVERAGE TIME TAKEN: %lf seconds\n"
					"\n", program, numberOfRepeats, numberOfThreads, average_time);

				fprintf (outfile,
					"\n"
					"Statistics:\n"
					"PROGRAM: %s\n"
					"NUMBER OF REPEATS: %ld\n"
					"NUMBER OF THREADS: %ld\n"
					"AVERAGE TIME TAKEN: %lf seconds\n"
					"\n", program, numberOfRepeats, numberOfThreads, average_time);
			}
			break;
		}
		default:
			printf ("\n"
				"EXITING....."
				"\n");
			exit (0);
	}

	fflush (outfile);
	fclose (outfile);
	outfile = NULL;

	return 0;
}