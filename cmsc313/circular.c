/*
Class: CMSC313
Project: Project 6
Filename: Circular.c
Name: Dong Sun
Email: dongsun1@umbc.edu
Date: 11/5/2014

*/


#include <stdio.h>
#include <stdlib.h>
#include "circular.h"
#define T 1
#define F 0

//Initialize a circular buffer and return a pointer that can be used to specify that circular buffer in future function calls.
cbuf * cbuf_init() {
	cbuf *cbf = malloc(10 * sizeof(cbuf));
	cbf->h = 0;
	cbf->t = 0;
	cbf->size = startSize;
	cbf->count = 0;
	cbf->q = malloc(10 * sizeof(quote));
	return cbf;
}

//Deallocate all dynamically allocated memory associated with the circular buffer referenced by cb_ptr.
//The programmer using your ADT promises to never use the value in cb_ptr again.
void cbuf_delete(cbuf *cb_ptr) {
	free(cb_ptr);
}

//Return the average exchange rate of the quotes currently stored in the buffer.
double cbuf_average(cbuf *cb_ptr) {
	int i;
	double sumCurrEx = 0.0;

	for (i = 0; i < cb_ptr->count; i++) {
		struct quote *temp;
		temp = cb_ptr->q + (cb_ptr->h + i) % (cb_ptr->size);
		sumCurrEx += temp->rate;
	}
	return (sumCurrEx / i);
}

//Print the contents of the circular buffer to standard output.
void cbuf_dump(cbuf *cb_ptr) {
	printf("*** Circular Buffer Dump ***\n");
	printf("size = %d, max = %d\n", cb_ptr->count, cb_ptr->size);

	printf("start = %d, end = %d\n\n", cb_ptr->h, ((cb_ptr->t - 1) % (cb_ptr->size)));
	int i;
	struct quote *temp;
	for (i = 0; i < cb_ptr->count; i++) {
		temp = cb_ptr->q + (cb_ptr->h + i) % (cb_ptr->size);
		printf("%d: time = %u, rate = %f\n", ((cb_ptr->h + i) % (cb_ptr->size)), temp->time, temp->rate); \

	}
	printf("*******************************\n\n\n");
}

//Same as cbuf_dump() but does not print out the quotes.
void cbuf_stats(cbuf *cb_ptr) {
	printf("*** Circular Buffer Stat ***\n");
	printf("size = %d, max = %d\n", cb_ptr->count, cb_ptr->size);
	printf("start = %d, end = %d\n\n", cb_ptr->h, cb_ptr->t - 1);
}

//Return a pointer to the earliest quote currently stored in the buffer.
quote *cbuf_start(cbuf *cb_ptr) {
	return &(cb_ptr->q[cb_ptr->h]);
}

//Return a pointer to the latest quote currently stored in the buffer.
quote *cbuf_end(cbuf *cb_ptr) {
	return &(cb_ptr->q[cb_ptr->t - 1]);
}
/*
Add a new currency exchange quote to the specified circular buffer. The time is in seconds since midnight.
This function should remove any quotes in the circular buffer that are more than 5 minutes older than this quote.
You should assume that the timestamps given to cbuf_update() are in non-decreasing order.
During a cbuf_update(), the memory for the circular buffer may have to grow or shrink according to the rules described above.
*/
void cbuf_update(cbuf *cb_ptr, unsigned int time, double rate) {


	struct quote *temp;
	temp = cb_ptr->q + cb_ptr->t;
	temp->rate = rate;
	temp->time = time;
	cb_ptr->t = (((cb_ptr->t) + 1) % (cb_ptr->size));
	cb_ptr->count++;

	int timeDiff,finish;
	finish = F;
	while (finish != T) {
		struct quote *tempQ;
		tempQ = cb_ptr->q + ((cb_ptr->h) % (cb_ptr->size));
		timeDiff = (time - tempQ->time);
		if (timeDiff >= fiveMin) {
			cb_ptr->h = ((cb_ptr->h + 1) % cb_ptr->size);
			cb_ptr->count = cb_ptr->count - 1;
		}
		else {
			finish = T;
		}
	}

	if (cb_ptr->count == cb_ptr->size){
		struct quote *newArray;
		newArray = malloc(2 * (cb_ptr->size) * sizeof(quote));
		int i;
		cb_ptr->t = 0; //start the tail at position 0
		for (i = 0; i < cb_ptr->count; i++) {
			newArray[i] = cb_ptr->q[(cb_ptr->h + i) % cb_ptr->size];
		}
		//print out message, old size and new size
		printf("Expanding circular buffer: old max = %d, new max = %d\n\n", cb_ptr->size, (2 * cb_ptr->size));
		cb_ptr->size = 2 * cb_ptr->size;
		cb_ptr->h = 0;
		cb_ptr->t = cb_ptr->count;
		cb_ptr->q = newArray;
		free(cb_ptr->q);
	}

	double c, s;
	c = cb_ptr->count;
	s = cb_ptr->size;

	if (((c / s) < .25) && (cb_ptr->size > startSize))
	{
		struct quote *newQuotesArray;
		newQuotesArray = malloc(.5 * (cb_ptr->size) * sizeof(quote));
		int newSize, i;
		if ((cb_ptr->size / 2) > startSize) {
			newSize = (cb_ptr->size / 2);
		}
		else {
			newSize = startSize;
		}
		for (i = 0; i < cb_ptr->count; i++) {
			newQuotesArray[((cb_ptr->h + i) % (newSize))] = cb_ptr->q[(cb_ptr->h + i) % cb_ptr->size];
		}
		cb_ptr->size = newSize;
		cb_ptr->h = ((cb_ptr->h) % (newSize));
		cb_ptr->t = ((cb_ptr->h + (cb_ptr->count - 1)) % (newSize));
		printf("Shrinking circular buffer: old max = %d, new max = %d\n\n", (2 * cb_ptr->size), cb_ptr->size);
		cb_ptr->q = newQuotesArray;
		free(cb_ptr->q);
	}


}
