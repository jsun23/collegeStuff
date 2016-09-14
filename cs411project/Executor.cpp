/*******************
	Executor.c
	James Bilbrey (bilbrey1@umbc.edu)
	Jeffery D. Sun (dongsun1@umbc.edu)
	Eric Forte (eforte1@umbc.edu)
	
	guys put your names here****
	CMSC 411 Fall 2015 Project
*******************/

#include "Executor.h"
#include <stdio.h>

int Executor::execute(Interpretation* data)
{
	//printf("FROM DATA BEFORE COMMAND: Source(rs): %d Tool(rt): %d Dest(rd): %d, Imm %d \n", reg[data->getSource()], reg[data->getTool()], reg[data->getDest()], data->getImm());
	bool isRobotInstruction = false;
	switch(data->getAction())
	{
		case JR:
			jr(data);
			break;
		case JALR:
			jalr(data);
			break;
		case ADD:
			add(data);
			break;
		case ADDU:
			addu(data);
			break;
		case SUB:
			sub(data);
			break;
		case SUBU:
			subu(data);
			break;
		case AND:
			andf(data);
			break;
		case OR:
			orf(data);
			break;
		case XOR:
			xorf(data);
			break;
		case NOR:
			nor(data);
			break;
		case J:
			jump(data);
			break;
		case JAL:
			jal(data);
			break;
		case BEQ:
			beq(data);
			break;
		case BNE:
			bne(data);
			break;
		case BLEZ:
			blez(data);
			break;
		case BGTZ:
			bgtz(data);
			break;
		case ADDI:
			addi(data);
			break;
		case ADDIU:
			addiu(data);
			break;
		case ANDI:
			andi(data);
			break;
		case ORI:
			ori(data);
			break;
		case XORI:
			xori(data);
			break;
		case LUI:
			lui(data);
			break;
		case LW:
			lw(data);
			break;
		case SW:
			sw(data);
			break;
		case SPD:
			spd(data);
			isRobotInstruction = true;
			break;
		case ROT:
			rot(data);
			isRobotInstruction = true;
			break;
		case ASCN:
			ascn(data);
			isRobotInstruction = true;
			break;
		case DSCN:
			dscn(data);
			isRobotInstruction = true;
			break;
		case FIR:
			fir(data);
			isRobotInstruction = true;
			break;
		default:
			return false;
	}

	// force register 0 to remain 0, even if changed in code
	reg[0] = 0;

	//printf("FROM DATA AFTER COMMAND: Source(rs): %d Tool(rt): %d Dest(rd): %d, Imm %d \n", reg[data->getSource()], reg[data->getTool()], reg[data->getDest()], data->getImm());
	return counter;
}

void Executor::add(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = reg[data->getSource()] + reg[data->getTool()];
	printf("N");
}

void Executor::addu(Interpretation* data)
{
	reg[data->getDest()] = reg[data->getSource()] + reg[data->getTool()];
	counter++;
	printf("N");
}

void Executor::jump(Interpretation* data)
{
	counter = static_cast<int>(data->getAddress());
	printf("N");
}

void Executor::jal(Interpretation* data)
{
	reg[31] = ++counter;
	counter = static_cast<int>(data->getAddress());
	printf("N");
}

void Executor::spd(Interpretation* data)
{
	printf("M %i", reg[data->getDest()] + data->getImm());
	counter++;
}

void Executor::rot(Interpretation* data)
{
	printf("R %i", reg[data->getDest()] + data->getImm());
	counter++;
}

void Executor::ascn(Interpretation* data)
{
	char line[16];
	printf("A");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%i", reg + data->getDest());
	counter++;
}

void Executor::dscn(Interpretation* data)
{
	char line[16];
	printf("D");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%i", reg + data->getDest());
	counter++;
}

void Executor::fir(Interpretation* data)
{
	printf("F %i", reg[data->getDest()] + data->getImm());
	counter++;
}

void Executor::sub(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = reg[data->getSource()] - reg[data->getTool()];
	printf("N");
}

void Executor::subu(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = reg[data->getSource()] - reg[data->getTool()];
	printf("N");
}

void Executor::addi(Interpretation* data)
{
	counter++;
	reg[data->getTool()] = reg[data->getSource()] + data->getImm();	
	printf("N");
}

void Executor::addiu(Interpretation* data)
{
	counter++;
	reg[data->getTool()] = reg[data->getSource()] + data->getUImm();	
	printf("N");
}

void Executor::andi(Interpretation* data)
{
	counter++;
	reg[data->getTool()] = reg[data->getSource()]& data->getImm();
	printf("N");
}

void Executor::andf(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = reg[data->getSource()] & reg[data->getTool()];
	printf("N");
}

void Executor::orf(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = reg[data->getSource()] | reg[data->getTool()];
	printf("N");
}

void Executor::xorf(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = reg[data->getSource()] ^ reg[data->getTool()];
	printf("N");
}

void Executor::jr(Interpretation* data)
{
	counter = reg[data->getSource()];
	printf("N");
}

void Executor::jalr(Interpretation* data)
{
	int target = reg[data->getSource()];
	reg[31]  = ++counter;
	counter = target;
	printf("N");
}

void Executor::beq(Interpretation* data)
{
	//the Imm is the offset
	if(reg[data->getSource()] == reg[data->getTool()]){

		counter = counter + data->getImm() + 1; 
	}
	else{
		counter++;
	}
	printf("N");
}

void Executor::bne(Interpretation* data)
{
	//the Imm is the offset
	if(reg[data->getSource()] != reg[data->getTool()]){

		counter = counter + data->getImm() + 1;
	}
	else{
		counter++;
	}
	printf("N");
}

void Executor::bgtz(Interpretation* data)
{
	//the Imm is the offset
	if(reg[data->getSource()]  > 0){

		counter = counter + data->getImm() + 1;
	}
	else{
		counter++;
	}
	printf("N");
}


void Executor::blez(Interpretation* data)
{
	//the Imm is the offset
	//printf("Source %d ", reg[data->getSource()]);
	if(reg[data->getSource()] <= 0){

		counter = counter + data->getImm() + 1;
	}
	else{
		counter++;
	}
	printf("N");
}

void Executor::ori(Interpretation* data)
{
	
	reg[data->getTool()]=reg[data->getSource()] | data->getImm();
	counter++;
	printf("N");

}

void Executor::xori(Interpretation* data)
{
	
	reg[data->getTool()]=reg[data->getSource()] ^ data->getImm();
	counter++;
	printf("N");
}

void Executor::lw(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = mem[reg[data->getSource()] + data->getImm()];
	printf("N");
}

void Executor::sw(Interpretation* data)
{
	counter++;
	mem[reg[data->getSource()] + data->getImm()] = reg[data->getDest()];
	printf("N");
}

void Executor::lui(Interpretation* data)
{
	reg[data->getTool()] = data->getImm()<<16;
	counter++;
	printf("N");

}

void Executor::nor(Interpretation* data)
{
	counter++;
	reg[data->getDest()] = ( (~reg[data->getSource()])  |  (~reg[data->getTool()]) );
	printf("N");
}
