/*******************
	States.cpp
	James Bilbrey (bilbrey1@umbc.edu )
	Jeffery D. Sun (dongsun1@umbc.edu )
	Eric Forte (eforte1@umbc.edu)

	CMSC 411 Fall 2015 Project
*******************/

#include "States.h"
#include <stdio.h>
#include <stdlib.h> 

uint32_t signExtend(uint32_t target, unsigned int from, unsigned int to = 32)
{
	if (from >= to)
		return target;
	
	switch (from)
	{
		case 16:
			return (target & 0x8000) == 0x8000 ? (target | 0xffff0000) : target;
		case 26:
			return (target & 0x2000000) == 0x2000000 ? (target | 0xfc000000) : target;
		default:
			return target; // Not supported yet
	}
}

void signExtend(Converter& target, unsigned int from, unsigned int to = 32)
{
	target.ccuint = signExtend(target.ccuint, from, to);
}

States::States(int& programCounter, int* asmCode, int* registers, int* stateRegisters)
{
	mem = asmCode;
	reg = registers;
	statereg = stateRegisters;
	cycleNum = 22;
	state = IFSTART;
	counter = programCounter;
	isError = 0; 
	
	//States that are missing e.g. 2 -16 are the same as what was previously there (InstructionFetchWait for 2 -16)
	
	states[IFSTART] = &States::InstructionFetchStart;
	states[IFWAIT] = &States::InstructionFetchWait;
	states[IFFINISH] = &States::InstructionFetchFinish;
	states[IFLW] = &States::InstructionFetchLoadWord;
	states[ID] = &States::InstructionDecode;
	states[WBNORM] = &States::WriteBackNormal;
	states[WBROBO] = &States::WriteBackRobotOut;
	states[WBMEM] = &States::WriteBackMemData;
	states[WBREG] = &States::WriteBackRegWD;
	states[DMNORM] = &States::DataMemoryRegular;
	states[DMROBOINSTART] = &States::DataMemoryRobotInStart;
	states[DMROBOINWAIT] = &States::DataMemoryRobotWait;
	states[DMROBOINFINISH] = &States::DataMemoryRobotFinish;
	states[DMROBOOUTSTART] = &States::DataMemoryRobotOutStart;
	states[DMROBOOUTWAIT] = &States::DataMemoryRobotOutWait;
	states[DMROBOOUTFINISH] = &States::DataMemoryRobotOutFinish;
	states[JUMPREG] = &States::JumpRegister;
	states[JUMPLINKREG] = &States::JumpAndLinkRegister;
	states[ADDF] = &States::Addf;
	states[ADDUF] = &States::AddU;
	states[SUBF] = &States::Sub;
	states[SUBUF] = &States::SubU;
	states[ANDF] = &States::Andf;
	states[ORF] = &States::Orf;
	states[XORF] = &States::XOrf;
	states[NORF] = &States::NOr;
	states[JUMPIMM] = &States::Jump;
	states[JUMPLINKIMM] = &States::JumpAndLink;
	states[BRANCHEQ] = &States::BranchIfEqual;
	states[BRANCHNEQ] = &States::BranchIfNotEqual;
	states[BRANCHLTE] = &States::BranchIfLessThanOrEqual;
	states[BRANCHGTE] = &States::BranchIfGreaterThanOrEqual;
	states[ADDIF] = &States::AddI;
	states[ADDIUF] = &States::AddIU;
	states[ANDIF] = &States::AndI;
	states[ORIMMEX] = &States::OrImmediateEx;
	states[EXCLORIMMEX] = &States::ExclusiveOrImmediateEx;
	states[LUIF] = &States::LuI;
	states[LOADWORD] = &States::LoadWord;
	states[STOREWORD] = &States::StoreWord;
	states[SPEED] = &States::spd;
	states[ROTATE] = &States::rot;
	states[ANGLE] = &States::ascn;
	states[DISTANCE] = &States::dscn;
	states[FIRE] = &States::fir;
}

int States::execute(){
	//for each block of memory
	for(int i=0; i<1023 ;i++){
		//run the instruction fetch
		//fprintf(stderr, "From excecute state of the regestrs %d %d %d %d \n", reg[0], reg[1], reg[2], reg[3]);
		//printf("IF state = %d\n", state);
		(this->*states[state])();
		//printf("First next state = %d\n", state);
		/*
		if(isError != 0){
				state = 0;
				counter = 0;
				isError = 0; 
			}
		*/
		while(state != 0){
			//keep running for as long as it takes to get to another instruction fetch
			(this->*states[state])();
			//printf("While next state = %d\n", state);
			/*
			if(isError != 0){
				state = 0;
				counter = 0;
				isError = 0; 
			}
			*/
		}
		//flaw this needs to be limited by the number of instructions there are
		if(i == 500){
			i = 0; 
		}
	}
	return 0; 
}


//NOTE PRINTS ARE NOT IN THERE RIGHT PLACES

//state = 0
void States::InstructionFetchStart()
{
	waiting[IF] = mem[counter];
	waiting[MEM] = mem[statereg[PC]];
	statereg[NPC] = statereg[PC] + 4; 
	//fprintf(stderr,"!!!!!!!!!!!Fetching Instruction From %d \n ", statereg[PC]);
	
	if(waiting[IF] == cache[counter]){
		//found in cache can go directly to decode
		//fprintf(stderr,"@@@@@@@@@@@@@found in cache can go directly to decode %d \n ", waiting[IF]);
		state = ID;
		statereg[IR] = waiting[IF];
		statereg[MDR] = waiting[MEM];
		fgets(line, sizeof(line), stdin);
		printf("N\n");
	}
	
	else{
		state = 1;
		fgets(line, sizeof(line), stdin);
		printf("N\n");
	}
}

//state = 1
void States::InstructionFetchWait()
{
	//loop to simulate function states 1 -16
	for(int i = 0; i < 17; i++){
		//fgets(line, sizeof(line), stdin);
		state += 1;
		fgets(line, sizeof(line), stdin);
	printf("N\n");
	}
	state = 17;
	
}

//state = 17
void States::InstructionFetchFinish()
{
	statereg[IR] = waiting[IF];
	//put in cache if not in cache
	if(counter < 16){
		cache[counter] = mem[counter];
	}
	statereg[MDR] = waiting[MEM];
	state = ID; //state = 19
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 18
void States::InstructionFetchLoadWord()
{
	//this syntax needs to be fixed
	statereg[MDR] = statereg[mem[SUM]];
	state = 22;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 19
void States::InstructionDecode()
{
	//statereg[PC] = statereg[NPC];

	counter++; 
	data.clear();
	interpreter.interpret(statereg[IR], &data);
	//statereg[PC] = statereg[NPC];
	fgets(line, sizeof(line), stdin);
	//int test = (int)(int)data.getDest();

	printf("N\n");
	//fprintf(stderr, "state of the regestrs %d %d %d %d \n", reg[0], reg[1], reg[2], reg[3]);
	//fprintf(stderr, "state of the data Dest = %d Imm = %d Source = %d Tool = %d \n", (int)data.getDest(), (int)data.getImm(), (int)data.getSource(), (int)data.getDest());
	switch (data.getInstructionType())
	{
		case CTYPE:
			//fprintf(stderr," CTYPE Instruction ");
			statereg[R1] = reg[(int)data.getDest()];
			statereg[RD] = (int)data.getDest();
			statereg[IMM] = signExtend((int)data.getImm(), 16);
			switch (data.getAction().ctype) {
				case SPD:
					state = SPEED;
					break;
				case ROT:
					state = ROTATE;
					break;
				case ASCN:
					state = ANGLE;
					break;
				case DSCN:
					state = DISTANCE;
					break;
				case FIR:
					state = FIRE;
					break;
				/*
				default:
					statereg[R1] = (int)data.getSource();
					state = JUMPREG;
				break;
				*/
			}
			break;
		case RTYPE:
			//fprintf(stderr," RTYPE Instruction ");
			statereg[R1] = reg[(int)data.getSource()];
			statereg[R2] = reg[(int)data.getTool()];
			statereg[RD] = (int)data.getDest();
			switch (data.getAction().rtype) {
				case JR:
					state = JUMPREG;
					break;
				case JALR:
					state = JUMPLINKREG;
					break;
				case ADD:
					state = ADDF;
					break;
				case ADDU:
					state = ADDUF;
					break;
				case SUB:
					state = SUBF;
					break;
				case SUBU:
					state = SUBF;
					break;
				case AND:
					state = ANDF;
					break;
				case OR:
					state = ORF;
					break;
				case XOR:
					state = XORF;
					break;
				case NOR:
					state = NORF;
					break;
				
				/*
				default:
					statereg[R1] = (int)data.getSource();
					state = JUMPREG;
				break;
				*/
			}
			break;
		case ITYPE:
				//fprintf(stderr," ITYPE Instruction ");
				statereg[R1] = reg[(int)data.getSource()];
				statereg[RD] = (int)data.getDest();
				statereg[IMM] = signExtend((int)data.getImm(), 16);
				//printf("state of the data Dest = %d Imm = %d Source = %d Tool = %d \n", (int)data.getDest(), (int)data.getImm(), (int)data.getSource(), (int)data.getDest(), reg[4]);
				//printf("state of the stateRegs SUM = %d R1 = %d R2 = %d RD = %d IMM = %d \n", statereg[SUM], statereg[R1], statereg[R2], statereg[RD], statereg[IMM]);
			switch (data.getAction().itype) {
				case BEQ:
					state = BRANCHEQ;
					break;
				case BNE:
					state = BRANCHNEQ;
					break;
				case BLEZ:
					state = BRANCHLTE;
					break;
				case BGTZ:
					state = BRANCHGTE;
					break;
				case ADDI:
					state = ADDIF;
					break;
				case ADDIU:
					state = ADDIUF;
					break;
				case ANDI:
					state = ANDIF;
					break;
				case ORI:
					state = ORIMMEX;
					break;
				case XORI:
					state = EXCLORIMMEX;
					break;
				case LUI:
					state = NORF;
					break;
				case LW:
					state = LOADWORD;
					break;
				case SW:
					state = STOREWORD;
					break;
				/*
				default:
					statereg[R1] = (int)data.getSource();
					state = JUMPREG;
					break;
				*/
			}
			break;
		case JTYPE:
			//fprintf(stderr," JTYPE Instruction ");
			statereg[IMM] = (int)data.getAddress();
			switch (data.getAction().jtype)
			{
				case J:
					state = JUMPIMM;
					break;
				case JAL:
					state = JUMPLINKIMM;
					break;
			/*
			default:
					statereg[R1] = (int)data.getSource();
					state = JUMPREG;
				break;
			*/
}
			break;
		//If at end of program restart
		default:
					statereg[R1] = (int)data.getSource();
					state = JUMPREG;
			break; 
	}
}

//state = 20
void States::WriteBackNormal()
{
	//syntax needs to be changed for $rd
	//reg[$rd] = statereg[SUM]
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	reg[statereg[RD]] = statereg[SUM]; 
	//printf("state of the regestrs %d %d %d %d %d \n", reg[0], reg[1], reg[2], reg[3], reg[4]);
	//printf("state of the stateRegs SUM = %d R1 = %d R2 = %d RD = %d IMM = %d \n", statereg[SUM], statereg[R1], statereg[R2], statereg[RD], statereg[IMM]);
		
	state = 0;

}

//state = 21
void States::WriteBackRobotOut()
{	fgets(line, sizeof(line), stdin);
	printf("N\n");
	reg[statereg[RD]] = statereg[BOTOUT];
	state = 0; 
}


//state = 22
void States::WriteBackMemData()
{	fgets(line, sizeof(line), stdin);
	printf("N\n");
	reg[statereg[RD]] = statereg[MDR];
	state = 0; 
}

//state = 23
void States::WriteBackRegWD()
{	fgets(line, sizeof(line), stdin);
	printf("N\n");
	reg[31] = statereg[WD];
	state = 0;
}

//state = 24
void States::DataMemoryRegular()
{	fgets(line, sizeof(line), stdin);
	printf("N\n");
	mem[SUM] = statereg[R2];
	state = 0;
}

//state = 25
void States::DataMemoryRobotInStart()
{
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	state = 26;
}

//state = 26
void States::DataMemoryRobotWait()
{
	//loop to simulate function states 26 -48
	for(int i = 26; i < 49; i++){
		//fgets(line, sizeof(line), stdin);
		state += 1;
		fgets(line, sizeof(line), stdin);
	printf("N\n");
	}
	state = 48;
}

//state = 48
void States::DataMemoryRobotFinish()
{
	//statereg[BOTOUT] = statereg[BOTOUT];
	//mem[SUM] = statereg[BOUTOUT]; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	state = 0;
}

//state = 49
void States::DataMemoryRobotOutStart()
{
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	state = 50; 
}


//state = 50
void States::DataMemoryRobotOutWait()
{
	//loop to simulate function states 50 -72
	for(int i = 50; i < 72; i++){
		// fgets(line, sizeof(line), stdin)
		state += 1;
		fgets(line, sizeof(line), stdin);
	printf("N\n");
	}

	state = 72;
}

//state = 72
void States::DataMemoryRobotOutFinish()
{
	//fgets(reg[statereg[RD]], sizeof(reg[statereg[RD]]), stdin);
	fgets(line, sizeof(line), stdin);
	statereg[BOTOUT] = atoi(line); 
	//printf("the value input is %d \n", reg[statereg[RD]]);
	//statereg[BOTOUT] = statereg[BOTOUT];
	printf("N\n");
	state = 21;
}

//state = 73
void States::JumpRegister()
{
	counter = statereg[R1];
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	state = 0; 
}

//state = 74
void States::JumpAndLinkRegister()
{
	int target = statereg[R1];
	reg[31]  = ++counter;
	counter = target;
	state = 0; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 75
void States::Addf()
{
	statereg[SUM] = statereg[R1] + statereg[R2];
	state = 20; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state 76
void States::AddU()
{
	statereg[SUM] = statereg[R1] + statereg[R2];
	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state 77
void States::Sub()
{
	statereg[SUM] = statereg[R1] - statereg[R2];
	state = 20; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state 78
void States::SubU()
{
	statereg[SUM] = statereg[R1] - statereg[R2];
	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 79
void States::Andf()
{
	statereg[SUM] = statereg[R1] & statereg[R2];
	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}


//state = 80
void States::Orf()
{
	statereg[SUM] = statereg[R1] | statereg[R2];
	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 81
void States::XOrf()
{
	statereg[SUM] = statereg[R1] ^ statereg[R2];
	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 82
void States::NOr()
{
	counter++;
	statereg[SUM] = ( (~statereg[R1])  |  (~statereg[R2]) );
	state = 20; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}



//state = 83
void States::Jump()
{
	statereg[WD] = statereg[NPC] ; 
	//statereg[PC] = statereg[IMM << 2];
	//execute can directly modify the program coutner
	//fprintf(stderr, "*****JJJJJJJJJJJJUMP********* %d %d \n ", statereg[PC], statereg[IMM]);
	counter = statereg[IMM];
	state = 0;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 84
void States::JumpAndLink()
{
	// I think this is wrong? shouldn't it be this WD = NPC; PC = imm <<2
	//reg[31] = statereg[IMM] + 1;
	statereg[WD] = statereg[NPC];
	statereg[PC] = statereg[IMM << 2];
	state = 23;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 85
void States::BranchIfEqual()
{
	//the Imm is the offset
	//fprintf(stderr, "$$$$$$Branch if == comparing %d and %d", statereg[R1], statereg[R2]);
	if(statereg[R1] == statereg[R2]){

		counter = counter + statereg[IMM] + 1;
	}
	/*
	else{
		counter++;
	}*/
	state = 0; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 86
void States::BranchIfNotEqual()
{	
	//fprintf(stderr, "$$$$$$Branch if != comparing %d and %d", statereg[R1], statereg[R2]);
	//the Imm is the offset
	if(statereg[R1] != statereg[R2]){

		counter = counter + statereg[IMM] + 1;
	}
	/*
	else{
		counter++;
	}*/
	state = 0; 
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 87
void States::BranchIfLessThanOrEqual()
{
	//the Imm is the offset
	//printf("Source %d ", statereg[R1]);
	//fprintf(stderr, "$$$$$$Branch if <0 comparing %d \n", statereg[R1]);
	if(statereg[R1] <= 0){
		//fprintf(stderr, "NOW SETTING COUNTER = %d FROM COUNTER = %d  \n", counter + statereg[IMM] + 1, counter);
		counter = counter + statereg[IMM] + 1;
	}
	/*
	else{
		counter++;
	}*/
	state = 0;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 88
void States::BranchIfGreaterThanOrEqual()
{
	//the Imm is the offset
	//fprintf(stderr, "$$$$$$Branch if >0 comparing %d \n", statereg[R1]);
	if(statereg[R1]  > 0){

		counter = counter + statereg[IMM] + 1;
	}
	/*
	else{
		counter++;
	}*/
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	state = 0; 
}

//state = 89
void States::AddI()
{
	statereg[SUM] = statereg[R1] + statereg[IMM];	
	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
	//printf("state of the stateRegs SUM = %d R1 = %d R2 = %d RD = %d IMM = %d \n", statereg[SUM], statereg[R1], statereg[R2], statereg[RD], statereg[IMM]);
		
}

//state = 90
void States::AddIU()
{

	statereg[SUM] = statereg[R1] + statereg[IMM];
	state = 20;	
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 91
void States::AndI()
{

	statereg[SUM] = statereg[R1] & statereg[IMM];
	state = 20 ;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 92
void States::OrImmediateEx()
{
	
	statereg[SUM]=statereg[R1] | statereg[IMM];

	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");

}

//state = 93
void States::ExclusiveOrImmediateEx()
{
	
	statereg[SUM] = statereg[R1] ^ statereg[IMM];

	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 94
void States::LuI()
{	//not sure what we are using for X
	statereg[SUM] = statereg[IMM]<<16;

	state = 20;
	fgets(line, sizeof(line), stdin);
	printf("N\n");

}

//state 95
void States::LoadWord()
{
	statereg[SUM] = statereg[R1] + statereg[IMM];
	state = 18;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state 96
void States::StoreWord()
{

	statereg[WD] = statereg[R2];
	statereg[SUM] = statereg[R1] + statereg[IMM];
	state = 24;
	fgets(line, sizeof(line), stdin);
	printf("N\n");
}

//state = 97
void States::spd()
{
	fgets(line, sizeof(line), stdin);
	printf("M %i\n", statereg[RD] + statereg[IMM]);

	state = 25;
}

//state = 98
void States::rot()
{
	fgets(line, sizeof(line), stdin);
	printf("R %i \n", statereg[RD] + statereg[IMM]);


	state = 25;
}

//state = 99 
void States::ascn()
{
	char line[16];
	fgets(line, sizeof(line), stdin);
	printf("A\n");

	//scane finishes in DM
	//sscanf(line, "%i", reg + statereg[RD]);
	state = 50; 

}

//state = 100 
void States::dscn()
{
	char line[16];
	fgets(line, sizeof(line), stdin);
	printf("D\n");

	//scan finishes in state DM 
	//sscanf(line, "%i", reg + statereg[RD]);
	state =  50;

}

//state = 101
void States::fir()
{
		fgets(line, sizeof(line), stdin);
	//fprintf(stderr, "***********FIREING********* %d %d \n ", statereg[R1], statereg[IMM]);
	
		printf("F %i\n", statereg[R1] + statereg[IMM]);


	state  = 25;

}
