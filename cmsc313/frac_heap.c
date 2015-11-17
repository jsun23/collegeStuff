/**
**  Project: Project 5
**  Class: CMSC 313
**  Name: Dong Sun
**  Date: 10/27/2014
**  Email: dongsun1@umbc.edu
**/



#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

#define ARRAYSIZE 10

fraction heap[ARRAYSIZE] = {NULL};
int start;
fraction* new_frac(){

	fraction *pt1, *pt2;
	int j;
	if (start != ARRAYSIZE)
	{

		pt1 = &heap[0];
		j = start;

		pt2 = pt1+j;

		start = heap[start].denominator;


		return pt2;
	}
	else
	{
		printf("Nothing is in heap\n\n");

		return NULL;
	}
}
void init_Heap(){
    int i;
	for(i = 0; i < ARRAYSIZE; i++)
    {
		heap[i].denominator = i + 1;
	}
	start = 0;

}

void dump_heap(){

    printf("***** Begin Heap Dump *****\n");
    int i;
    for(i = 0; i < ARRAYSIZE; i++)
    {

        printf("%d: ", i);
        printf("%d\t", heap[i].sign);
        printf("%d\t", heap[i].numerator);
        printf("%d\n", heap[i].denominator);
    }
    printf("***** End Heap Dump *****\n\n\n");

}
void del_frac(fraction *ftp){
     fraction *pt1, *pt2;
	int j;
	if (ftp < &heap[ARRAYSIZE] && ftp >= &heap[0])
	{
		pt1 = &heap[0];
		pt2 = ftp;
		j = pt2 - pt1;
		heap[j].sign = 0;
		heap[j].numerator = 0;
		heap[j].denominator = start;
		start = j;
	}

}

