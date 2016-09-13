/*
** Project: Project1
** Name: Dong Sun
** Class: CMSC 341
** Date: 9/30/2014

*/

#ifndef VEHICLE_H
#define VEHICLE_H
using namespace std;
class Vehicle{
	
private:
	char type;
	int timeEntered;
public:
		char setType(char t);
		int setTimeEntered(int te);
		char getType();
		int getTimeEntered();
		Vehicle(char type, int time);

};





#endif