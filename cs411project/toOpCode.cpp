/**************************************************************
 * File:    main.cpp
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Driver Class, takes two arguments and input for commands and an output file for
 * hex code for the MIPS instruction set 
 *
 *************************************************************/
#include <iostream>
#include <string>
#include "FileParser.h"
#include "Assembler.h"
#include <bitset>
int toOpCode(string argOne, const char* argTwo) {
	//This is the main driver of the program for testing
	//if(argc < 2 ){
	
	//	cout << "Usage: ./Main.out input_file output_file" << endl;
	//	return 0;
	//}
	//string argOne = argv[1];
	//const char* argTwo= argv[2];
	//FileParser* myParser = new FileParser("testMIPS.txt");	
	
	//real code
	FileParser myParser(argOne);
	myParser.parseFile();
	Assembler myAsmb(myParser.getAllInstructions(), myParser.getLabels());
	myAsmb.outputHex(argTwo);
	

	//test code
	
	
        //size 6 bytes
        //
		/*
        unsigned int maxA = 63;
        maxA = maxA << 26;
        fprintf(oFile, "0x%08x,\n", maxA);

        //size 5 bytes
        //can be moved up by 4
        unsigned int maxB = 31;
        maxB = maxB << 21;
        fprintf(oFile, "0x%08x,\n", maxB);

        unsigned int maxC = maxA | maxB;
        string binary = std::bitset<32>(maxC).to_string();
        cout << binary << endl;
        fprintf(oFile, "0x%08x,\n", maxC);


		*/
	
	
	
	//int x = 6;
	//string binary = std::bitset<32>(x).to_string(); //to binary
	//cout << binary << endl;    

	//deque<string> myLines;
	//myLines = myParser.getAllInstructions();
	//send myLines to Assembler to do the rest there
	
	return 0;

}

int main(int argc, char** argv) {
	//This is the main driver of the program for testing
	if(argc < 2 ){
	
		cout << "Usage: ./Main.out input_file output_file" << endl;
		return 0;
	}
	string argOne = argv[1];
	const char *  argTwo = argv[2];
	toOpCode(argOne, argTwo);
	return 0; 
}

