/**************************************************************
 * File:    FileParser.h
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Header file for the FileParser Class, parses a file into a map of 
 * labels and instruction objects
 *
 *************************************************************/
#ifndef FILEPARSER_H
#define FILEPARSER_H
#include <iostream>
#include <string>
#include <queue>
#include "Instr.h"
#include <map>
using namespace std;
//File parser for MIPS input
class FileParser{
	public:
		FileParser();
		FileParser(string fileName);
		//parses the file into instruction objects
		void parseFile();
		//not used but can be used to iterate through instructions
		string* getNextInstruction();
		//returns the full deque of instructions parsed from the file supplied in the constructor
		deque<Instr*> getAllInstructions();
		map<string, int> getLabels();
		
	private:
		string fileName;
		deque<string> Instructions;
		//queue of parsed instruction objects in readable format
		deque<Instr*> orderedInstr;
		//int instructionPointer;
		FILE* readFile;
		//map of labels 
		map<string, int> labels;
};
#endif
