/*************************
** File: twoDimension.cpp
** Homework: CMSC 341 Homework 1, Fall 2014
** Author: Dong Sun
** Date: 9/12/14
** Section: 04
** E-mail: dongsun1@umbc.edu
** This file is basic create a construct for 2D points and the getting and setting
**************************/
#include <iostream>
using namespace std;

class twoDimension
{
private:
	// x and y  coordinates
	int x, y; 
public:
	// this is an initializer list
	twoDimension(int i, int j) :x(i), y(j){} 
	
	void setX(int NewX)
	{ 
		x = NewX; 
	}
	void setY(int NewY)
	{ 
		y = NewY; 
	}
	const int getX()
	{ 
		return x; 
	}
	const int getY() 
	{ 
		return y;
	}
};

