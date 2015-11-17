/**
**  Project: Project 5
**  Class: CMSC 313
**  Name: Dong Sun
**  Date: 10/27/2014
**  Email: dongsun1@umbc.edu
**/




#ifndef FRAC_HEAP_H
#define FRAC_HEAP_H



/* frac_heap.h*/
/* #include required by the prototypes*/
/* typedefs and #defines*/
typedef struct
{
    char sign;
   unsigned int denominator;
   unsigned int numerator;
}fraction;

/* function prototypes*/
//initialize the heap
void init_Heap();
//print the array
void dump_heap();
//delete an point from memory
void del_frac();
//add new point to the heap
fraction* new_frac();


#endif // FRAC_HEAP
