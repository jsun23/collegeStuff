/*
Class: CMSC313
Project: Project 6
Filename: Circular.h
Name: Dong Sun
Email: dongsun1@umbc.edu
Date: 11/5/2014

*/



#ifndef CIRCULAR_H
#define CIRCULAR_H

#define startSize 10
#define fiveMin 300


typedef struct quote{
	unsigned int time;
	double rate;

}quote;
typedef struct cbuf{
	int h;
	int t;
	int size;
	int count;
	quote *q;


}cbuf;


cbuf * cbuf_init();
double cbuf_average(cbuf *cb_ptr);
quote *cbuf_start(cbuf *cb_ptr);
void cbuf_delete(cbuf *cb_ptr);
quote *cbuf_end(cbuf *cb_ptr);
void cbuf_dump(cbuf *cb_ptr);
void cbuf_stats(cbuf *cb_ptr);
void cbuf_update(cbuf *cb_ptr, unsigned int time, double rate);

#endif // CIRCULAR_H
