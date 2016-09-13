/*************************
** File: Driver.cpp
** Homework: CMSC 341 Homework 1, Fall 2014
** Author: Dong Sun
** Date: 9/12/14
** Section: 04	
** E-mail: dongsun1@umbc.edu
** This the driver file contain a main function to run the project
** This file will assign a point and display the point, create the points array
** and find the same point, display the points 
**************************/

#include <iostream>
#include <ctime>
#include "threeDimension.cpp"
#include "twoDimension.cpp"
using namespace std;
//const create the array length to be 10
const int array_size = 10;
int main()
{
	//declare the firstPT and set x, y , z to be 3, 4, 5
	threeDimension firstPT = threeDimension(3, 4, 5);
	
	//print out firstPT point using the over load cout
	cout << firstPT;

	//declare points to be an array for threeDimension
	threeDimension **points = new threeDimension*[];
	
	//using a for loop to assign the points to each array
	for(int i=0;i<array_size;i++)	
	{
		//set the seed to be system time
		srand((unsigned)time(0));
		//random assign the point from 0-100
		points[i] = new threeDimension(rand() % 100, rand() % 100, rand() % 100);

	}
	//display the points
	displayPoints(points,array_size);
	//find the same points
	sameXYZ(points, array_size);
	system("pause");
	return 0;
}

