/**************************************************************
 * File:    FileParser.cpp
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Implementation for the FileParser Class, parses a file into a map of 
 * labels and instruction objects
 *
 *************************************************************/
#include "FileParser.h"
#include <string>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>
const int BUFFER_SIZE = 256;

using namespace std;

map<string,string> typeCheck = {
	{"j","j"},
	{"jal","j"},
	{"jr","r"},
	{"jalr","r"},
	{"add","r"},
	{"addu","r"},
	{"sub","r"},
	{"subu","r"},
	{"and","r"},
	{"or","r"},
	{"xor","r"},
	{"nor","r"},
	{"beq","i"},
	{"bne","i"},
	{"blez","i"},
	{"bgtz","i"},
	{"addi","i"},
	{"addiu","i"},
	{"andi","i"},
	{"ori","i"},
	{"xori","i"},
	{"lui","i"},
	{"lw","i"},
	{"sw","i"},	
	{"spd","c"},
	{"rot","c"},
	{"ascn","c"},
	{"dscn","c"},
	{"fir","c"},


};
//File parser implementation

//	variable referance	
//	Private:
//		string fileName;
//		queue<string*> Instructions;
//		int instructionPointer;

FileParser::FileParser(string fileName){
	//int instructionPointer = 0; 
	ifstream infile(fileName.c_str());
	if(infile.good())
	{
		//open file 
		readFile = fopen(fileName.c_str(), "r");

	}
	else
	{
		cout << "Error creating FileParser, invalid file" << endl;
	}
	//check to see if file exists
	
	//if file exists set vars to correct values
	
	//else quit and print error
}

void FileParser::parseFile(){
	//2 pass parsing
	
	//grab all lines
	while(1)
	{
		char line[256];
		//cout << "File Exists " << endl;	
		fgets(line, BUFFER_SIZE, readFile);
		Instructions.push_back(line);
		//cout << Instructions.front();
		//Instructions.pop();
		
		if(line == NULL || feof(readFile))
        	{
                	break;
        	}


		//printf("%s\n",line);

		//printf("\n");
	}
	//parse line by line from queue of lines
	//create instruction objects and add objects to queue of objects to be assembled
	//char* token; 
	//token = strtok(line, " \t\v\r\n\f,()");
	//while(token != NULL)
	//{
	//	printf ("%s ",token);
	//	Instructions.push(token);
	//	cout << Instructions.front();
	//	Instructions.pop();
	//	token = strtok(NULL, " \t\v\r\n\f,()");
	//}
	
	//return a queue of instruction objects ready to be assembled 
	
	//if(line == NULL || feof(readFile))
	//{
	//	break; 
	//}
	deque<string> myLines;
	myLines = Instructions;
	int num = 0;
    for(deque<string>::iterator it = myLines.begin(); it != myLines.end(); ++it){
                //cout << "LINE# " << num ;
                //cout << *it << endl;
		string currLine = *it;
		if(currLine.empty() == false){
			//move the functionality from the Instr constructor to this one
			Instr* myInstr= new Instr();
			//myInstr.printInfo();
			string line = *it;
	            (myInstr)->instrNum = num;
			(myInstr)->addressNum = num * 4;
			char* token; 
			char* tempLine = new char[line.length()+1];
			strcpy(tempLine, line.c_str()); 
			token = strtok(tempLine, " \t\v\r\n\f,()");
			bool first = true;
			int numTokens = 0;
			int firstC = 0; 
			//queue of instructions to parse for intruction object
			deque<string> toParseInstr;
			while(token != NULL)
			{
				if(!strcmp(token, ";")){
					 //printf("FOUND");
					break; 
				}
				toParseInstr.push_back(token);
				if(first){
					//type = typeCheck[token];
					//type = typeCheck.find(token);
					//std::unordered_map<std::string,double>::const_iterator got = typeCheck.find (token);
					//cout << "THE TYPE IS ";
					//cout << "checking against "<<token;
					
					string test = typeCheck[token];
					myInstr->type = test;
					//cout << typeCheck[token] <<  " ";
					//cout<<typeCheck.find(token)->second;
					//type = typeCheck.find(token);
					//cout << type;
					first = false;
					if(test.empty()){
						first = true;
						//(myInstr)->label = token;
						if((token[0] == ':')){
							labels[token] = num * 4;
							//ignore first labels in instructions
							toParseInstr.pop_front();
							//cout << "LABEL " << token << "APEARS ON THIS LINE "  <<labels[token] << endl ;
						}
					}
				}	
				
				//printf ("%s ",token);
				numTokens++;
				token = strtok(NULL, " \t\v\r\n\f,()");
			}
			//printf("\n");
			//myInstr->printInfo();
			//check if valid instruction
			//assumes this is only check for valid instruction
			if(numTokens > 1){
				int numReg = 0;
				int numImm = 0;	
				int hold = 0;
				
				//if type R	
				//cout << "DEQUEUE SIZE!!!" << toParseInstr.size() << endl;
				//DOES NOT DO ANYTHING WITH sh
				if(myInstr->type == "r"){
	
					//for(deque<string>::iterator it = toParseInstr.begin(); it != toParseInstr.end(); ++it){
						//cout << toParseInstr[0];
						//cout << toParseInstr[1];
						//cout << toParseInstr[2];
						//cout << toParseInstr[3];
						//cout << toParseInstr[4];
						//cout << toParseInstr[5];
						myInstr->func = toParseInstr[0];
						myInstr->rd = toParseInstr[1];
						myInstr->rs = toParseInstr[2];
						myInstr->rt = toParseInstr[3];
						//myInstr->sh = toParseInstr[4];
						myInstr->opcode = "0";
					//}
				}

				
				//if type I
				else if(myInstr->type == "i"){
					for(deque<string>::iterator it = toParseInstr.begin(); it != toParseInstr.end(); ++it){
						string toCheck = *it;
						if(toCheck.find("$") == 0){
							numReg++;
							//cout << "REG FOUND!";
							if(numReg > 1){
								myInstr->rd = myInstr->rs;
								myInstr->rs = toCheck;
							}
							else{
								myInstr->rs = toCheck;
							}
						}
						if(toCheck.find("#") == 0 || toCheck.find(":") == 0 ){
							numImm++;
							//cout << "IMM FOUND!";
							myInstr->immediate = toCheck;
						}
						
						if(numReg == 0 && numImm == 0){
							myInstr->opcode = toCheck;
						}
						/*
						else if(numReg == 1){
							myInstr->rs = toCheck;
							checkHold = hold;
						}
						else if(numReg == 2){
							myInstr->rd = toParseInstr[checkHold];
							myInstr->rs = toCheck;
						}
						else if(numImm == 1){
							myInstr->immediate = toCheck;
						}
						*/
						hold++;
						//myInstr->opcode = toParseInstr[0];
						//myInstr->rs = toParseInstr[1];
						//myInstr->rd = toParseInstr[2];
						//myInstr->immediate = toParseInstr[3];
					}

				}
				
				//if type C
				else if(myInstr->type == "c"){
					if(firstC == 0){
						firstC = 1;
						//it++; 
					}
					for(deque<string>::iterator it = toParseInstr.begin(); it != toParseInstr.end(); ++it){
						string toCheck = *it;
						if(toCheck.find("$") == 0){
							numReg++;
							//cout << "REG FOUND!";
							if(numReg > 1){
								//myInstr->rd = myInstr->rs;
								myInstr->rd = toCheck;
							}
							else{
								myInstr->rd = toCheck;
							}
						}
						if(toCheck.find("#") == 0 || toCheck.find(":") == 0 ){
							numImm++;
							//cout << "IMM FOUND!";
							myInstr->immediate = toCheck;
						}
						
						if(numReg == 0 && numImm == 0){
							myInstr->opcode = toCheck;
						}
						/*
						else if(numReg == 1){
							myInstr->rs = toCheck;
							checkHold = hold;
						}
						else if(numReg == 2){
							myInstr->rd = toParseInstr[checkHold];
							myInstr->rs = toCheck;
						}
						else if(numImm == 1){
							myInstr->immediate = toCheck;
						}
						*/
						hold++;
						//myInstr->opcode = toParseInstr[0];
						//myInstr->rs = toParseInstr[1];
						//myInstr->rd = toParseInstr[2];
						//myInstr->immediate = toParseInstr[3];
					}

				}
				
				//if type j
				else if(myInstr->type == "j"){
					//for(deque<string>::iterator it = toParseInstrr.begin(); it != toParseInstr.end(); ++it){
						myInstr->opcode = toParseInstr[0];
						myInstr->immediate = toParseInstr[1];
						//cout << "SETTINT ADDRESS TO LABEL " << labels[temp];
					//}

				}
				//if pseudo-instructions
				
				else{
					for(deque<string>::iterator it = toParseInstr.begin(); it != toParseInstr.end(); ++it){
						//if((it*).find('#') == true){
						//	myInstr->value = it*;
						//}
						string toCheck = *it;
						//cout << "COULD SET VAL " << toCheck;
						if(toCheck.find("#") == 0){
							myInstr->value = toCheck;
							//cout << "TRY TO SET VAL " << toCheck;
						}
					}
				}
				

	
				orderedInstr.push_back(myInstr);
				//myInstr->parseInfo(); 
				num++;
			}
			
		}
        }
	
	
	//while(!Instructions.empty()){
	//	cout << Instructions.front();
	//	Instructions.pop();
	//}

	//iterate over all items in the orderedIntr deque
	int numX = 0;
	  for(deque<Instr*>::iterator it = orderedInstr.begin(); it != orderedInstr.end(); ++it){
    		//cout << "Type " << num ;
		//cout <<  << endl;
		//(*it)->parseInfo();
		numX++;
	}
	//cout << numX << endl;

	//acount for labels
	fclose(readFile);
}


string* FileParser::getNextInstruction(){
	
	//return proper instruction (single string pointer in proper location from queue)
	return NULL;
	
}

deque<Instr*> FileParser::getAllInstructions(){
	//dump all instrructions 
	return orderedInstr;
	
}


 map<string, int> FileParser::getLabels(){

	return labels; 
}
