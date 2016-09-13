#include "TrafficSim.h"

TrafficSim::TrafficSim(const string loc)
{
	
	myfile.open(loc);
}

TrafficSim::TrafficSim()
{
	
}
bool TrafficSim::readFromFile(string filename)
{
	myfile.open(filename);
	if (!myfile.is_open())
	{
		cout << "Can not open the file!!";
		return false;
	}
	else 
		return true;
		myfile.close();
		
}

void TrafficSim::printBoard()
{

	cout << "The final result are: \n";
	cout << "The number of vehicles that passed through the intersection is: ";
	cout << "The number of cars that passed through the intersection is: ";
	cout << "The number of trucks that passed through the intersection is: ";
	cout << "The average wait time for this intersection is: ";

}
bool TrafficSim::addVehicle(char direction, Vehicle &x)
{
	int getInt1, getInt2;
	while (myfile.getline != NULL)
	{
		myfile.getline;
		myfile >> direction >> getInt1 >> getInt2;
	}
	switch (direction)
	{
		case 'E':
			if (getInt1 != 0)
			{
				eastBound.push(x.setType('c'));
				x.setTimeEntered(getInt1 * 60);
				eastBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
			}
			else
				eastBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
		case 'W':
			if (getInt1 != 0)
			{
				westBound.push(x.setType('C'));
				x.setTimeEntered(getInt1 * 60);
				westBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
			}
			else
				westBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
		case 'N':
			if (getInt1 != 0)
			{
				northBound.push(x.setType('C'));
				x.setTimeEntered(getInt1 * 60);
				northBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
			}
			else
				northBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
		case 'S':
			if (getInt1 != 0)
			{
				southBound.push(x.setType('C'));
				x.setTimeEntered(getInt1 * 60);
				southBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
			}
			else
				southBound.push(x.setType('t'));
				x.setTimeEntered(getInt2 * 60);
	}
}
void TrafficSim::DoRun()
{

}