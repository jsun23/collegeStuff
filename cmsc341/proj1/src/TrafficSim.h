/**
** Project: Project1
** Name: Dong Sun
** Class: CMSC 341
** Date: 9/30/2014

**/

#ifndef TRAFFICSIM_H
#define TRAFFICSIM_H
using namespace std;

#include"Linked_List.h"
#include"IntersectionFlowRate.h"
#include"Vehicle.h"
#include"ResultVehicle.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
class TrafficSim 
{
private:
	queue<char> eastBound;
	queue<char> westBound;
	queue<char> northBound;
	queue<char> southBound;
	ResultVehicle results;
	IntersectionFlowRate flowRate;
	
	void printBoard();
	bool addVehicle(char direction, Vehicle &x);
public:
	TrafficSim(const string loc);
	TrafficSim();
	ifstream myfile;
	char c;
	bool readFromFile(string filename);
	void DoRun();
};





#endif