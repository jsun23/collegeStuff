=============================================================================== 
Project Phase 4:
Due 12/7/2015

How we run/test: //can substitute Phase4 with any valid asm file or leave to the default testMIPS.txt 
make clean 
make FILE=Phase4.asm

//the compiled progrmam will be Main.out


//From another terminal:

ssh eforte1@gl.umbc.edu -L8080:localhost:1578
//change to project directory
cd CMSC411/projDone/

~olano/robotarena/RobotDriver -w 1578 -r robotsTest.txt

Program Notes (States.cpp)(extra credit):
	-Implemented a basic cache to hold the first 16 instructions from memory
	-It checks to see if the instruction is in the cache befoe checking memory
	-if it is in the cache it will load it from there
	-otherwise it will continue from memory
	-one the instruction is fetched from memory it will be stored in the cache it is one of the first 16 instructions
	-A more robust version of the cache is located in cacheMemory.h and .cpp
Program Potential Errors:
	-The program still has a defined intruction limit of 500 to prevent it from going through all 1024 bocks of memory
	-commented out there is a solution to handle this where the program, once it reaches a postion it does not recogzie will jump 
	to a recognizeable one, but since that was not part of the project should be implemented, it is commented out
