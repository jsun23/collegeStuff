/**************************************************************
* File:    driver.cpp
* Project: CMSC 341 - Project 1 - Traffic Light Simulation
* Author : Mr. Lupoli (with help)
* Date   : 17-June-2014
* Section: ALL
* E-mail:  slupoli@cs.umbc.edu
*
* Main Program Driver.
*
*************************************************************/


#include <iostream>
#include "TrafficSim.h"

using namespace std;

int main(int argc, char *argv[]) {

	//If there is an input file listed
	if (argc > 1) {
		TrafficSim *Sim = new TrafficSim(argv[1]);
		Sim->DoRun();
		delete Sim;
		Sim = NULL;

		//If no input file is specified.    
	}
	else {
		TrafficSim *Sim = new TrafficSim();
		Sim->DoRun();
		delete Sim;
		Sim = NULL;
	}

	return 0;
}