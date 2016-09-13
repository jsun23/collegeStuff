/*
** Project: Project1
** Name: Dong Sun
** Class: CMSC 341
** Date: 9/24/2014
** IntersectionFlowRate class
** create all the flow rate of each dirction of cars and trucks


*/


#include "IntersectionFlowRate.h"


	 int IntersectionFlowRate :: setEFRCars(int efc)
	{
		eastFlowRateCars = efc;
	}
	int IntersectionFlowRate :: setWFRCars(int wfc)
	{
		westFlowRateCars = wfc;
	}
	int IntersectionFlowRate :: setNFRCars(int nfc)
	{
		northFlowRateCars = nfc;
	}
	int IntersectionFlowRate::setSFRCars(int sfc)
	{
		southFlowRateCars = sfc;
	}
	int IntersectionFlowRate::setEFRTrucks(int eft)
	{
		eastFlowRateTrucks = eft;
	}
	int IntersectionFlowRate::setWFRTrucks(int wft)
	{
		westFlowRateTrucks = wft;
	}
	int IntersectionFlowRate::setNFRTrucks(int nft)
	{
		northFlowRateTrucks = nft;
	}
	int IntersectionFlowRate::setSFRTrucks(int sft)
	{
		southFlowRateTrucks = sft;
	}
	int IntersectionFlowRate::getEFRCars()
	{
		return eastFlowRateCars;
	}
	int IntersectionFlowRate::getWFRCars()
	{
		return westFlowRateCars;
	}
	int IntersectionFlowRate::getNFRCars()
	{
		return northFlowRateCars;
	}
	int IntersectionFlowRate::getSFRCars()
	{
		return southFlowRateCars;
	}
	int IntersectionFlowRate::getEFRTrucks()
	{
		return eastFlowRateTrucks;
	}
	int IntersectionFlowRate::getWFRTrucks()
	{
		return westFlowRateTrucks;
	}
	int IntersectionFlowRate::getNFRTrucks()
	{
		return northFlowRateTrucks;
	}
	int IntersectionFlowRate::getSFRTrucks()
	{
		return southFlowRateTrucks;
	}
