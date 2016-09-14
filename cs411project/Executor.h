/**************************
	James Bilbrey (bilbrey1@umbc.edu)
	Executor.h
	CMSC 411 Fall 2015 Project
**************************/

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Interpretation.h"

class Executor
{
	public:
		
		Executor(int* asmCode, int* registers, int programCounter)
		{
			mem = asmCode;
			reg = registers;
			counter = programCounter;
		}
		
		int execute(Interpretation* data);
	
	private:
		
		int *mem, *reg, counter;
		
		// MIPS
		void jr(Interpretation* data);
		void jalr(Interpretation* data);
		void add(Interpretation* data);
		void addu(Interpretation* data);
		void sub(Interpretation* data);
		void subu(Interpretation* data);
		void andf(Interpretation* data);
		void orf(Interpretation* data);
		void xorf(Interpretation* data);
		void nor(Interpretation* data);
		void jump(Interpretation* data);
		void jal(Interpretation* data);
		void beq(Interpretation* data);
		void bne(Interpretation* data);
		void blez(Interpretation* data);
		void bgtz(Interpretation* data);
		void addi(Interpretation* data);
		void addiu(Interpretation* data);
		void andi(Interpretation* data);
		void ori(Interpretation* data);
		void xori(Interpretation* data);
		void lui(Interpretation* data);
		void lw(Interpretation* data);
		void sw(Interpretation* data);
		
		// Robot
		void spd(Interpretation* data);
		void rot(Interpretation* data);
		void ascn(Interpretation* data);
		void dscn(Interpretation* data);
		void fir(Interpretation* data);
};

#endif
