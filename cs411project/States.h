
/**************************
	James Bilbrey (bilbrey1@umbc.edu)
	States.h
	CMSC 411 Fall 2015 Project
**************************/

#ifndef STATES_H
#define STATES_H

#include "Interpreter.h"
#include <stdio.h>

class States
{
	public:
	
   	enum StateReg // These are the registers used to cross section boundaries
   	{
   		PC, NPC, IR, MDR, R1, R2, IMM, RD, SUM, WD, BOTOUT
   	};
   	 
   	 enum Waitpoints // These are where an operation will take more than one cycle
   	{
		IF, MEM, REG, ROBO
   	};
   	 
   	enum StateID
	{
		IFSTART, // 0
		IFWAIT,
		IFFINISH = 17,
		IFLW,
		ID,
		WBNORM,
		WBROBO,
		WBMEM,
		WBREG,
		DMNORM,
		DMROBOINSTART,
		DMROBOINWAIT,
		DMROBOINFINISH= 48,
		DMROBOOUTSTART,
		DMROBOOUTWAIT,
		DMROBOOUTFINISH= 72,
		JUMPREG,
		JUMPLINKREG,
		ADDF,
		ADDUF,
		SUBF,
		SUBUF,
		ANDF,
		ORF,
		XORF,
		NORF,
		JUMPIMM,
		JUMPLINKIMM,
		BRANCHEQ,
		BRANCHNEQ,
		BRANCHLTE,
		BRANCHGTE,
		ADDIF,
		ADDIUF, //90
		ANDIF,
		ORIMMEX,
		EXCLORIMMEX,
		LUIF,
		LOADWORD,
		STOREWORD,
		SPEED,
		ROTATE,
		ANGLE,
		DISTANCE,
		FIRE //101
	};
   	 
   	States(int& programCounter, int* asmCode, int* registers, int* stateRegisters);
   	 
   	int execute();
	
	private:
   	 
		int *mem, *reg, *statereg, waiting[ROBO + 1];
		int cycleNum, state, counter;
		int isError;
		int cache[16]; 
		//keyboard input
		char line[256];
		
		Interpretation data;
		Interpreter interpreter;
		 
		void (States::*states[102])(void);

		void InstructionFetchStart();
		void InstructionFetchWait();
		void InstructionFetchFinish();
		void InstructionFetchLoadWord();
		void InstructionDecode();
		void WriteBackNormal();
		void WriteBackRobotOut();
		void WriteBackMemData();
		void WriteBackRegWD();
		void DataMemoryRegular();
		void DataMemoryRobotInStart();
		void DataMemoryRobotWait();
		void DataMemoryRobotFinish();
		void DataMemoryRobotOutStart();
		void DataMemoryRobotOutWait();
		void DataMemoryRobotOutFinish();
		void JumpRegister();
		void JumpAndLinkRegister();
		void Addf();
		void AddU();
		void Sub();
		void SubU();
		void Andf();
		void Orf();
		void XOrf();
		void NOr();
		void Jump();
		void JumpAndLink();
		void BranchIfEqual();
		void BranchIfNotEqual();
		void BranchIfLessThanOrEqual();
		void BranchIfGreaterThanOrEqual();
		void AddI();
		void AddIU();
		void AndI();
		void OrImmediateEx();
		void ExclusiveOrImmediateEx();
		void LuI();
		void LoadWord();
		void StoreWord();
		void spd();
		void rot();
		void ascn();
		void dscn();
		void fir();
};

#endif
