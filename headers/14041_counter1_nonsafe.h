#ifndef COUNTER1_H
#define COUNTER1_H

/*
 *	@author: Gursimran Singh
 *	@rollNo: 2014041
 *
 *	Implementing Counter 1
 *		Non Thread Safe Counter
 *
 */

typedef struct _counter1_nonThreadSafe {
	long count;					// The Counter Variable
} counter1_t;

void cntr1_init (counter1_t *counter)
{
	counter -> count = 0;				// Initialize Counter
}

void cntr1_increment (counter1_t *counter)
{
	(counter -> count) ++;				// Increment Counter
}

void cntr1_decrement (counter1_t *counter)
{
	(counter -> count) --;				// Decrement Counter
}

long cntr1_get (counter1_t *counter)
{
	return (counter -> count);			// Return Counter Value
}

#endif