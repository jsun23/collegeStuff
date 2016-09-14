/**************************************************************
 * File:    Assembler.h
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Definition file for the Assembler class which takes Instruction Objects and assembles them
 *
 *************************************************************/
#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <string>
#include <deque>
#include "Instr.h"
#include <map>
//assembler.h file containing teh header information for the assembler

using namespace std;

class Assembler{
        public:
			//takes in a deque of instructions and a map(hastable) of labels and their referances
        	Assembler(deque<Instr*> myInstr,  map<string, int> labels);
		//outputs the hex to a file 
		void outputHex(const char* outFile);
        private: 
			//not used
        	string fileName;
			//list of instructions to assemble
			deque<Instr*> instrToAsmb;
			//map of labels
			map<string, int> labelsForAsmb; 	    	
};

#endif
