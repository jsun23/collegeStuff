/**************************************************************
 * File:    FileParser.cpp
 * Project: CMSC 411 - Homework 1
 * Author : Eric Forte
 * Date   : 9-September-2015
 * E-mail: eforte@umbc.edu
 *
 * Implementation for the Instr Class, main information container for instructions 
 *
 *************************************************************/
#include "Instr.h"
#include <string>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;


Instr::Instr(){


}

//Assumes that the first input is the opcode
Instr::Instr(string line, int number){
	

}

void Instr::printInfo(){
	cout << "inst# " << instrNum;
	cout << " address " << addressNum;
	cout << " TYPE: " << type;
	cout << " LABEL: " << label;
	cout << endl; 
} 

void Instr::parseInfo(){

	//check type and use proper parseing
	
	if(type == "r"){
		cout << "TYPE R "<< opcode << " RS" << rs << " RT" << rt << " RD " << rd << "SH " << sh << " FUNC" << func << endl;		

	}

	else if(type == "i"){
		cout <<"TYPE I" << opcode << " RS" << rs << "RD " << rd << " IMM "  << immediate<< endl;
	}

	else if(type == "j"){
		cout << "TYPE J" << opcode << " ADDDR" << addressNum << endl;
	}
	else{
		cout << "NO TYPE!" << "VALUE" << value<< endl;
	}
	
}
