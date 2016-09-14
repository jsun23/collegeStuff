===============================================================================
Project Phase 3:
Due 11/25/2015

RTL Changes and Notes:
	-The RTL has now been changed to properly allow for multicycle instruction fetch 
	-The RTL for each function e.g ADD shows all of the functionality required to run the function in the RTL  with the RTL for other necessary functions in ()
	-The RTL now has properly labbled states which are the bassis for our simulation with the RTL for other necissary functions in ()
	-The RTL now has properly labbled states which are teh bessis for our simulation
	-New RTL is in *_v2.

Datapath Changes and Notes:
	-We removed an uncecissary mux from our data path and added another register for holding Robout Output data across cycles
	-We changed out cycle time per Dr. Olano's suggestion to 22
	-New Datapath is in *_v2
	
Program Notes On Implementation:
	-States.h and States.cpp are the main components of our simulation, each state is directly mirrored off of the state of the RTL and are
	 in matching order for referance. We use ENUMS for most of the data handleling and conversions

Program Known Errors:
	-the IF always grabs memory too even if it is not needed (may be fine because fizing may require pipelining)
	-Currently there is a bug where the number of instructiosn must be set upfront in our execute function for states.cpp 
	 It is currently set to 4 instructions, 

Clock Speed = 22

IF requires  17 cycles

ID requires  1 cycle

EX requires  1 cycle

DM  23 cycles
WB requires 1  cycle
