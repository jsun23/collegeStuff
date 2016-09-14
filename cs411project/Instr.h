/**************************************************************
 * File:    FileParser.h
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Header file for the Instr Class, main information container for instructions 
 *
 *************************************************************/
#ifndef INSTR_H
#define INSTR_H
#include <string>

using namespace std;


class Instr{

	public: 
		Instr();
		Instr(string line, int number);
		//prints limited info about the object
		void printInfo();
		//prints more detailed information
		void parseInfo();
		string type;
		string opcode;
		string rs;
		string rt;
		string rd;
		string sh;
		string func;
		string immediate;
		//original line number
		string address;
		//value for psudo instructions
		string value; 
		int instrNum;
		//address value in bytes
		int addressNum; 
		string label; 
	private:
};
#endif
