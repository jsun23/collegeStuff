#include "Vehicle.h"


Vehicle::Vehicle(char t, int time)
{
	type = t;
	timeEntered = time;
}
char Vehicle :: setType(char t)
	{
		type = t;
	}
int Vehicle::setTimeEntered(int te)
	{
		timeEntered = te;
	}
char Vehicle::getType()
	{
		return type;
	}
int Vehicle::getTimeEntered()
	{
		return timeEntered;
	}
