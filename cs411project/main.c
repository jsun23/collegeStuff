/*
Name: Jeffery D. Sun
File: Sample main
*/




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//get the stored hex values from mem
int storeInstruction(int *mem, int pc) {
    return mem[pc];
}

int main() {
    // compile machine code file 
    int mem[1024] = {
        #include "code.h"
    };

    int reg[32];    // registers
    reg[0] = 0;
    int pc = 0;     // current program counter
    char line[256]; // line from keyboard
    int tPC;
	
    // program counter init
    tPC = pc;

    // wait for input
    fgets(line, sizeof(line), stdin);

    int test, i=0;
	
   /*test function by check if all the hex code stored inside the memory*/	
    	for(; i<sizeof(mem)/sizeof(mem[0]);i++){
    	test = storeInstruction(mem, i);
    	printf("0x%08x,\n",test);

	}

	return 0;


}
