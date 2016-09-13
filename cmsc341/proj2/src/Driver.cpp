/**************************************************************
* File:    driver.cpp
* Project: CMSC 341 - Project 2 - Index Creator
* Author : Mr. Lupoli (with help)
* Date   : 17-June-2014
* Section: Lecture-02
* E-mail:  slupoli@cs.umbc.edu
*
* Main Program Driver.
*
*************************************************************/
#include <iostream>
#include <string>
#include "Indexer.h"
#include "Word.h"

using namespace std;

int main(int argc, char *argv[]) {


	//Do we have the right number of aruguments?  We will validate those
	//arguments later.
	if (argc != 3) {
		cout << "Usage:  ./Proj2.out filter.file data.file\n" << endl;
		cout << "filter.file - The file that contains the list of words";
		cout << " not to be included." << endl;
		cout << "data.file - The file that contains the text";
		cout << " to be indexed.\n" << endl;

		//This is the main driver.
	}
	else {
		string inFilterFile = argv[1]; //Filter file.
		string inDataFile = argv[2];   //Data file.

		try {
			Indexer *index = new Indexer(inFilterFile, inDataFile);
			index->DoIndex();
			delete index;
			index = NULL;
		}
		//Something went wrong.
		catch (Exceptions &cException) {
			cout << "EXCEPTION: " << cException.GetMessage() << endl;
			return 1;
		}
	}
	//Uncomment for number of seconds running.
	//cout << clock() / (float)CLOCKS_PER_SEC) << endl;
	return 0;
}
