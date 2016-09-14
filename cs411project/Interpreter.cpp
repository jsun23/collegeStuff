/********************
	James Bilbrey (bilbrey1@umbc.edu)
	Interpreter.c
	CMSC 411 Fall 2015 Project

	This file converts assembled machine code into
	separate wrapper pieces to be used by a C program.
*********************/

#include "Interpreter.h"
#include <stdint.h>
#include <stdio.h>
Interpreter::Interpreter()
{
	// 
}

Interpreter::~Interpreter()
{
	// 
}

void Interpreter::interpret(int& machineCode, Interpretation* wrapper)
{
	Converter convert;
	convert.cint = machineCode;
	interpret(convert.ccuint, wrapper);
}

void Interpreter::interpret(uint32_t machineCode, Interpretation* wrapper)
{
	uint32_t opcode = machineCode >> 26;
	
	if (opcode == 0) // r-type
	{
		wrapper->setAction((machineCode << 26) >> 26);
        
		switch (wrapper->getAction().cint)
		{
			case JR:
			case JALR:
			case ADD:
			case ADDU:
			case SUB:
			case SUBU:
			case AND:
			case OR:
			case XOR:
			case NOR:
				wrapper->setInstructionType(RTYPE);
				wrapper->setSource((machineCode << 6) >> 27);
				wrapper->setTool((machineCode << 11) >> 27);
				wrapper->setDest((machineCode << 16) >> 27);
				wrapper->setShift((machineCode << 21) >> 27);
				break;
			default:
				wrapper->setError(true); // Error
		}
	}
	else if (opcode == 19) // c-type
	{
		wrapper->setAction((machineCode << 6) >> 27);
		
		switch (wrapper->getAction().cint)
		{
			case SPD:
			case ROT:
			case ASCN:
			case DSCN:
			case FIR:
				wrapper->setInstructionType(CTYPE);
				wrapper->setDest((machineCode << 11) >> 27);
				wrapper->setImm((machineCode << 16) >> 16);
				break;
			default:
				wrapper->setError(true); // Error
		}
	}
	else if (opcode == 2) // J
	{
		wrapper->setInstructionType(JTYPE);
		wrapper->setAction(J);
        wrapper->setAddress((machineCode << 6) >> 6);
	}
	else if (opcode == 3) // JAL
	{
		wrapper->setInstructionType(JTYPE);
		wrapper->setAction(JAL);
        wrapper->setAddress((machineCode << 6) >> 6);
	}
	else // I-type
	{
		wrapper->setAction(opcode);
		
		switch (wrapper->getAction().cint)
		{
			case BEQ:
			case BNE:
			case BLEZ:
			case BGTZ:
			case ADDI:
			case ADDIU:
			case ANDI:
			case ORI:
			case XORI:
			case LUI:
			case LW:
			case SW:
				wrapper->setInstructionType(ITYPE);
				wrapper->setSource((machineCode << 6) >> 27);
				wrapper->setDest((machineCode << 11) >> 27);
				wrapper->setImm((machineCode << 16) >> 16);
				//this is here because MIPS says use $t but Olano's code uses $d for I-types
				wrapper->setTool((machineCode << 11) >> 27);
				break;
			default:
				wrapper->setError(true); // Error
		}
	}
	//printf("FROM wrapper: Source(rs): %d Tool(rt): %d Dest(rd): %d, Imm %d \n", wrapper->getSource(), wrapper->getTool(), wrapper->getDest(), wrapper->getImm());

}
