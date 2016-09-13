/**
** Project: Project1
** Name: Dong Sun
** Class: CMSC 341
** Date: 9/30/2014

**/





#ifndef INTERSECTIONFLOWRATE_H
#define INTERSECTIONFLOWRATE_H
using namespace std;


class IntersectionFlowRate{

private:
	int eastFlowRateCars;
	int westFlowRateCars;
	int northFlowRateCars;
	int southFlowRateCars;
	int eastFlowRateTrucks;
	int westFlowRateTrucks;
	int northFlowRateTrucks;
	int southFlowRateTrucks;
public:
		int setEFRCars(int efc);
		int setWFRCars(int wfc);
		int setNFRCars(int nfc);
		int setSFRCars(int sfc);
		int setEFRTrucks(int eft);
		int setWFRTrucks(int wft);
		int setNFRTrucks(int nft);
		int setSFRTrucks(int sft);
		int getEFRCars();
		int getWFRCars();
		int getNFRCars();
		int getSFRCars();
		int getEFRTrucks();
		int getWFRTrucks();
		int getNFRTrucks();
		int getSFRTrucks();
};

#endif