/********************
	James Bilbrey (bilbrey1@umbc.edu)
	Interpreter.h
	CMSC 411 Fall 2015 Project

	This class will convert assembled machine code into
	separate data pieces to be used by a C program.
*********************/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Interpretation.h"

class Interpreter
{
	public:
		
		Interpreter();
		~Interpreter();
		void interpret(uint32_t machineCode, Interpretation* wrapper);
		void interpret(int& machineCode, Interpretation* wrapper);
};

#endif
