/*
** Filename: Word.h
** Project: Project2
** Class: CMSC341
** Name: Dong Sun
** Date: 10/21/2014
** Email: dongsun1@umbc.edu
**
** set valuables and function of Indexer class
**
*/


#ifndef INDEXER_H
#define INDEXER_H
#include "BinarySearchTree.h"
#include "Word.h"
#include "Exceptions.h"
#include <fstream>

class Indexer
{

private:
	BinarySearchTree<Word> filteredBST;
	BinarySearchTree<Word> indexedBST;
	string datefile;
	string filterfile;
	bool fildExists(char* filename);
	BinarySearchTree<Word> fileFilterReader(string filename);
	BinarySearchTree<Word> fileWordReader(string filename);
	void outputResulte();

public:
	Indexer(string filterName, string dateFile);
	void DoIndex();


};




#endif
