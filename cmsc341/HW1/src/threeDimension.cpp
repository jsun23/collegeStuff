/*************************
** File: threeDimension.cpp
** Homework: CMSC 341 Homework 1, Fall 2014
** Author: Dong Sun
** Date: 9/12/14
** Section: 04
** E-mail: dongsun1@umbc.edu
** 
** The threeDimension file contain the function displayPoints and sameXYZ
** also overloading the cout "<<"
** 
**************************/
#include <iostream>
using namespace std;
#include "twoDimension.cpp"

class threeDimension : public  twoDimension
{
private:
	// create valuble z
	int z; 
public:
	//construct for 3d by extends 2d
	threeDimension(int i, int j, int k) :twoDimension(i, j), z(k){}
	
	void setZ(int NewZ)
	{ 
		z = NewZ; 
	}

	const int getZ()  
	{ 
		return z; 
	}
	friend ostream& operator<<(ostream& os, const threeDimension& dt);
	void static displayPoints(threeDimension *pt[], int array_size);
	bool static sameXYZ(threeDimension *pt[], int array_size);
};


/*
**pre-condition: the << is connect with threeDimension valuble 
**post-condition: return a string
*/
ostream& operator << (ostream& out, const threeDimension& threed)
{
	out << "This 3D point has the value of:\nx: "
		<<threed.getX  <<"\ny: "<<threed.getY 
		<< "\nz: " << threed.getZ <<"\n---";
	return out;
}

/*
**pre-condition: threeDimension points array and array length
**post-condition: none
*/
void static displayPoints(threeDimension *pt[],int array_size)
{
	for (int i = 0; i < array_size; i++)
	{
		cout << pt[i];
	}
}
/*
** pre-condition: threeDimension points array and array length
** post-condition: true or false
*/
bool static sameXYZ(threeDimension *pt[], int array_size)
{
	for (int i = 0; i < array_size; i++)
	{
		if (pt[i] == pt[i + 1])
			cout << pt[i];
		else
			return false;
	}
}