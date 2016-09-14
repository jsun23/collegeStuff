/*******************************
	James Bilbrey (bilbrey1@umbc.edu)
	Interpretation.h
	CMSC 411 Fall 2015 Project

	Universal wrapper class to be used by
	function implementations.
*******************************/

#ifndef INTERPRETATION_H
#define INTERPRETATION_H

#include <stdint.h>

enum InstructionType
{
	CTYPE, ITYPE, JTYPE, RTYPE, UNKNOWN
};

enum ITYPES
{
	BEQ = 4,
	BNE = 5,
	BLEZ = 6,
	BGTZ = 7,
	ADDI = 8,
	ADDIU = 9,
	ANDI = 12,
	ORI = 13,
	XORI = 14,
	LUI = 15,
	LW = 35,
	SW = 43
};

enum RTYPES
{
	JR = 8,
	JALR = 9,
	ADD = 32,
	ADDU = 33,
	SUB = 34,
	SUBU = 35,
	AND = 36,
	OR = 37,
	XOR = 38,
	NOR = 39
};

enum CTYPES
{
	SPD, ROT, ASCN, DSCN, FIR
};

enum JTYPES
{
	J = 2,
	JAL = 3
};
		
union Converter
{
	int cint;
	unsigned int cuint;
	uint32_t ccuint;
	RTYPES rtype;
	ITYPES itype;
	CTYPES ctype;
	JTYPES jtype;
};

class Interpretation
{
	public:
		void setError(bool e)
		{	err = e;	}
		void setInstructionType(InstructionType t)
		{	type = t;	}
		void setAction(Converter a)
		{	action = a;	}
		void setAction(uint32_t a)
		{	action.ccuint = a;	}
		void setAction(CTYPES a)
		{	action.ctype = a;	}
		void setAction(ITYPES a)
		{	action.itype = a;	}
		void setAction(JTYPES a)
		{	action.jtype = a;	}
		void setAction(RTYPES a)
		{	action.rtype = a;	}
		void setSource(uint32_t s)
		{	rs = s;		}
		void setDest(uint32_t d)
		{	rd = d;		}
		void setTool(uint32_t t)
		{	rt = t;		}
		void setImm(uint32_t i)
		{	imm = i;	}
		void setShift(uint32_t s)
		{	imm = s;	}
		void setAddress(uint32_t a)
		{	imm = a;	}
		
		bool error()
		{	return err;		}
		InstructionType getInstructionType()
		{	return type;	}
		Converter getAction()
		{	return action;	}
		uint32_t getSource()
		{	return rs;		}
		uint32_t getDest()
		{	return rd;		}
		uint32_t getTool()
		{	return rt;		}
		uint32_t getImm()		/* signed immediate */
		{	return (-(imm & 0x8000) | imm);	}
		uint32_t getUImm()		/* unsigned immediate */
		{	return imm;		}
		uint32_t getShift()
		{	return imm;		}
		uint32_t getAddress()
		{	return imm;		}
		
		void clear()
		{
			err = false;
			action.cint = -1;
			rs = rd = rt = imm = 0;
		}
		
	private:
		bool err;
		Converter action;
		InstructionType type;
		uint32_t rs, rd, rt,
		// use for imm, sh, and address;
		imm;
};

#endif
