/*
Name: Jeffery D. Sun
File: Sample main
Updated by Eric Forte (eforte1@umbc.edu) on 9/29/2015
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include "FileParser.h"
#include "Assembler.h"
#include "Interpretation.h"
#include "Interpreter.h"

#include "States.h"

//get the stored hex values from mem
int storeInstruction(int *mem, int pc) {
    return mem[pc];
}

int main(int argc, char** argv) {

	// this avoids some compile problems initializing signed int with
	// numbers big enough to be negative (>= 0x80000000)
    unsigned int umem[1024] = {
        #include "code.h"
    };
	int *mem = (int*)umem;

    int reg[32];    // registers
    reg[0] = 0;
    reg[1] = 0;
    reg[2] = 0;
    reg[3] = 0;
    int pc = 0;     // current program counter
    char line[256]; // line from keyboard
    int tPC;
	
    // program counter init
    tPC = pc;

    // wait for input
    // fgets(line, sizeof(line), stdin);

    int test, i;
    Interpretation terp;
    Interpreter interpreter;
    //Executor exe(mem, reg, tPC);


    //initialize the State of the Regesters from our RTL
    // PC, NPC, IR, MDR, R1, R2, IMM, RD, SUM, WD, BOTOUT
    int stateReg[11] = {0,0,0,0,0,0,0,0,0,10,0};

    //create a States object
    States myStates(tPC, mem, reg, stateReg); 	

    //prints the clock speed
    printf("%d\n", 22);

	myStates.execute();
   /*test function by check if all the hex code stored inside the memory*/	

    /*
    for(i=0; i<1023 ;i++){
		//waits for prompt for first simulated clock cycle
		fgets(line, sizeof(line), stdin);

		//stores instruction for debugging
    		test = storeInstruction(mem, tPC);
		    	
		//clears previous interpretation
		terp.clear();
		
		//sends program counter to be interpreted
		interpreter.interpret(mem[tPC], &terp);
		
		if(terp.error()){
			//unrecognized command, error
			//skip and go to next command
			printf("Error:unrecognized command \n"); 
			tPC++; 
		}
		else{

			//excecutes interpreted commands
		 	//tPC = exe.execute(&terp);
			//run the execute function on the state object and obtaitn new program counter(NPC)
		}
		
		//prints out debugging test information test
        //	printf("0x%08x, %d \n",test, tPC);
		//printf("state of the regestrs %d %d %d %d \n", reg[0], reg[1], reg[2], reg[3], reg[4]); 
	}
	*/
	return 0;


}
