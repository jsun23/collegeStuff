/**************************************************************
 * File:    Assembler.cpp
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Implementation for the Assembler class which takes Instruction Objects and assembles them
 *
 *************************************************************/


#include "Assembler.h"
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <string.h>
using namespace std;

map<string,string> funcOp = {
	{"jr","001000"},
	{"jalr","001001"},
	{"add","100000"},
	{"addu","100001"},
	{"sub","100010"},
	{"subu","100011"},
	{"and","100100"},
	{"or","100101"},
	{"xor","100110"},
	{"nor","100111"},
};
map<string,string> opCodes = {
    {"j","000010"},
    {"jal","000011"},
	{"beq","000100"},
	{"bne","000101"},
	{"blez","000110"},
	{"bgtz","000111"},
	{"addi","001000"},
	{"addiu","001001"},
	{"andi","001100"},
	{"ori","001101"},
	{"xori","001110"},
	{"lui","001111"},
	{"lw","100011"},
	{"sw","101011"},
	{"spd","010011"},	
	{"rot","010011"},
	{"ascn","010011"},
	{"dscn","010011"},
	{"fir","010011"}
};
map<string,string> cfn = {
        {"spd","00000"},
        {"rot","00001"},
        {"ascn","00010"},
        {"dscn","00011"},
        {"fir","00100"},
};


map<string,string> branchIntr = {
	{"000100","beq"},
	{"000101","bne"},
	{"000110","blez"},
	{"000111","bgtz"},

//	{"beq","000100"},
//	{"bne","000101"},
//	{"blez","000110"},
//	{"bgtz","000111"},



};

Assembler::Assembler(deque<Instr*> myInstr, map<string, int> labels ){
	
	//test to see if transefer works properly
	 //for(deque<Instr*>::iterator it = myInstr.begin(); it != myInstr.end(); ++it){
    		//cout << "Type " << num ;
		//cout <<  << endl;
		//(*it)->parseInfo();
		
	//}	

	instrToAsmb = myInstr;
	labelsForAsmb = labels; 	
	//takes in a queue of instruction objects
	
	
}

//uses queue of objects 
//converts them to binary
//converts to hex and outputs to file
//the binary is appended to a string and then it is converted into its proper integer value and then it is converted to hex
void Assembler::outputHex(const char*  outFile){
	FILE *oFile = fopen(outFile, "w");
	int intrNum = 1;
	for(deque<Instr*>::iterator it = instrToAsmb.begin(); it != instrToAsmb.end(); ++it){
		//(*it)->
		//string answ;
		//if r type
		
		if((*it)->type == "r"){
			
			unsigned int myAns = 0; 
			//char* val = "";
			//known hardcoded opcode
			//answ.append("000000");
			
			string rsT = (*it)->rs;
			
			int tempA;
            if(rsT.empty()){
				tempA = 0;

			}
			else{
				rsT.erase(0, 1);
				tempA = stoi(rsT);	
				
			}
			
			//rsT.erase(0, 1);
			//int tempA = stoi(rsT);
			//sscanf(rsT.c_str(), "$%s", val);
			//string rsTEMP = bitset<5>(rsT).to_string();
			//answ.append(bitset<5>(tempA).to_string());	
            tempA  = tempA  << 21;         
			string rtT = (*it)->rt;
			int tempB;
            if(rtT.empty()){
				tempB = 0;

			}
			else{
				rtT.erase(0, 1);
				tempB = stoi(rtT);				
			}
			
                        //rtT.erase(0, 1);
			//int tempB = stoi(rtT);
			//sscanf(rtT.c_str(), "$%s", &val);
                        //rtT = bitset<5>(rtT).to_string();
            //answ.append(bitset<5>(tempB).to_string());
            tempB = tempB << 16;
			
			 
			string rdT = (*it)->rd;
			int tempC;
            if(rdT.empty()){
				tempC = 0;

			}
			else{
				rdT.erase(0, 1);
				tempC = stoi(rdT);				
			}
			tempC = tempC << 11;
                        //rdT.erase(0, 1);
			//int tempC = stoi(rdT);
			//sscanf(rdT.c_str(), "$%s", &val);
                        //rdT = bitset<5>(rdT).to_string();
                        //answ.append(bitset<5>(tempC).to_string());
			
			string shT = (*it)->sh;
			int tempD = 0;
                        //shT = bitset<5>(shT).to_string();
                        //answ.append(bitset<5>(tempD).to_string());
            tempD = tempD << 6;           
			string funcT = (*it)->func;
            funcT = funcOp[funcT];
                        //funcT = bitset<5>(funcT).to_string();
            // answ.append(funcT);
			int tempF = 0;
			char* endF;
			tempF = strtol (funcT.c_str(),&endF,2);
			//answ.append(bitset<5>(tempD).to_string());

			
			//bitset<32> set(answ);
			//set.to_ulong();
			//fprintf(outFilePnt, "0x%08x,\n", answ);

			//int hexAnsw = stoi(answ);
			//bitset<32> set(answ);
			//cout << hex << set.to_ulong() << endl;
			//char * end;
			//long int value = strtol (string,&end,2);
			//cout << answ << endl;
			//char* end;
			//long int value = strtol (answ.c_str(),&end,2);
			//cout << value << endl;
			myAns = tempA | tempB | tempC | tempD | tempF;
			fprintf(oFile, "0x%08x,\n", myAns);
			
			

		}
		
		//if i type
		else if((*it)->type == "i"){
			string opCodeT = opCodes[(*it)->opcode];
			//answ.append(opCodeT);
			unsigned int myAns = 0;
			int tempOp = 0;
			char* endC;
			tempOp = strtol (opCodeT.c_str(),&endC,2);
			tempOp = tempOp << 26;
			
			string rsT = (*it)->rs;
			rsT.erase(0, 1);
			int tempA = stoi(rsT);
			
			//sscanf(rsT.c_str(), "$%s", val);
			//string rsTEMP = bitset<5>(rsT).to_string();
			//answ.append(bitset<5>(tempA).to_string());	
			tempA  = tempA  << 21;
			
			string rdT = (*it)->rd;
			int tempB;
            if(rdT.empty()){
				tempB = 0;

			}
			else{
				rdT.erase(0, 1);
				tempB = stoi(rdT);				
			}
			//sscanf(rdT.c_str(), "$%s", &val);
            //rdT = bitset<5>(rdT).to_string();
            //answ.append(bitset<5>(tempB).to_string());
			tempB = tempB << 16;
			
			string immT = (*it)->immediate;
			//cout << "the immT value is: " << immT << endl; 
			int tempC;
			if(labelsForAsmb[immT] == NULL){					
				immT.erase(0, 1);
				tempC = stoi(immT);
				tempC = tempC & 0xFFFF;
				//cout << "TEMPC NO LABEL! IS " << tempC << endl;
			}
			else{
				tempC = labelsForAsmb[immT];

				//cout << "TEMPC! IS LABEL " << ((tempC/4)-intrNum) << endl; 
					//cout << opCodeT << endl; 
					if(branchIntr.find(opCodeT) == branchIntr.end() ){
						
						tempC = tempC;
					}
					else{
						
						tempC = ((tempC/4)-intrNum);
					}
			}
		 
			//sscanf(rdT.c_str(), "$%s", &val);
            //rdT = bitset<5>(rdT).to_string();
            //answ.append(bitset<16>(tempC).to_string());		
			
		
			
			//char* end;
			//long int value = strtol (answ.c_str(),&end,2);
			//cout << value << endl;
			myAns = tempOp | tempA | tempB | tempC;
			fprintf(oFile, "0x%08x,\n", myAns);
			
			

		}
		//c type
		else if((*it)->type == "c"){
			//cout <<"I get called!" << endl; 
			string opCodeT = opCodes[(*it)->opcode];
			string cfnT = cfn[(*it)->opcode];
			//cout << (*it)->opcode << endl;
			//cout << "OPOODE " << opCodeT << endl; 
			//cout << cfnT << endl;
			//answ.append(opCodeT);
			unsigned int myAns = 0;
			int tempOp = 0;
			int tempcfnT = 0;
			char* endC;
			tempOp = strtol (opCodeT.c_str(),&endC,2);
			tempOp = tempOp << 26;
			
			tempcfnT = strtol (cfnT.c_str(),&endC,2);
			tempcfnT = tempcfnT << 21;
			
			//string rsT = (*it)->rs;
			//rsT.erase(0, 1);
			//int tempA = stoi(rsT);
			
			//sscanf(rsT.c_str(), "$%s", val);
			//string rsTEMP = bitset<5>(rsT).to_string();
			//answ.append(bitset<5>(tempA).to_string());	
			//tempA  = tempA  << 21;
			
			string rdT = (*it)->rd;
			int tempB;
            if(rdT.empty()){
				tempB = 0;

			}
			else{
				//cout << "rdT: "<< rdT << endl;
				rdT.erase(0, 1);
				//cout << "rdT -1 "<< rdT << endl;
				tempB = stoi(rdT);				
			}
			//sscanf(rdT.c_str(), "$%s", &val);
            //rdT = bitset<5>(rdT).to_string();
            //answ.append(bitset<5>(tempB).to_string());
			tempB = tempB << 16;
			
			string immT = (*it)->immediate;
			//cout << "the immT value is: " << immT << endl; 
			int tempC;
			if(labelsForAsmb[immT] == NULL){					
				immT.erase(0, 1);
				if(immT[0] == '\0'){
					tempC = 0;
				}
				else{
					tempC = stoi(immT);
					tempC = tempC & 0xFFFF;
				}
				//cout << "TEMPC NO LABEL! IS " << tempC << endl;
			}
			else{
				tempC = labelsForAsmb[immT];

				//cout << "TEMPC! IS LABEL " << ((tempC/4)-intrNum) << endl; 
					//cout << opCodeT << endl; 
					if(branchIntr.find(opCodeT) == branchIntr.end() ){
						
						tempC = tempC;
					}
					else{
						
						tempC = ((tempC/4)-intrNum);
					}
			}
		 
			//sscanf(rdT.c_str(), "$%s", &val);
            //rdT = bitset<5>(rdT).to_string();
            //answ.append(bitset<16>(tempC).to_string());		
			
		
			
			//char* end;
			//long int value = strtol (answ.c_str(),&end,2);
			//cout << value << endl;
			myAns = tempOp | tempcfnT | tempB | tempC;
			fprintf(oFile, "0x%08x,\n", myAns);
			
			

		}
		//j type
        else if((*it)->type == "j"){
			//cout << "FOUND A J!" << endl;
			
			string opCodeT = opCodes[(*it)->opcode];
			//answ.append(opCodeT);
			
			unsigned int myAns = 0;
			int tempOp = 0;
			char* endC;
			tempOp = strtol (opCodeT.c_str(),&endC,2);
			tempOp = tempOp << 26;
			
			string immT = (*it)->immediate;
			int addressT = labelsForAsmb[immT];
			//cout << "the number "  << addressT << endl;
			addressT = addressT/4;
			//cout << "the number "  << addressT << endl;
			//int tempA = stoi(addressT);
			//answ.append(bitset<26>(addressT).to_string());
			//char* end;
			//long int value = strtol (answ.c_str(),&end,2);
			//cout << "J VALUE " << answ << endl;
			myAns = tempOp | addressT;
			fprintf(oFile, "0x%08x,\n", myAns);
			
        }
		
		else{
			string valueT = (*it)->value;
			int tempA;
			unsigned int myAns = 0;
			if(valueT.empty()){					
				tempA = 0;
			}
			else{
				valueT.erase(0, 1);
				tempA = stoi(valueT);
			}
			//answ.append(bitset<32>(tempA).to_string());
			//char* end;
			//long int value = strtol (answ.c_str(),&end,2);
			//cout << "J VALUE " << answ << endl;
			myAns = tempA;
			fprintf(oFile, "0x%08x,\n", myAns);
		
		}

		

	
		intrNum++;
	}
	
	fclose(oFile);
}
