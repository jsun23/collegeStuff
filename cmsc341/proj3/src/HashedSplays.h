/**
** Project: Project 3
** Filename: HashedSplays.h
** Author: Dong Sun
** Email: dongsun1@umbc.edu
** Date: 11/4/2014 
**
** HashedSplays.h is most of the functions to set up the splaytree and looking 
** through the tree find the index and the words
**/



#ifndef HASHED_SPLAYS_H
#define HASHED_SPLAYS_H
#include "SplayTree.h"
#include "Exception.h"
#include "Node.h"
#include <fstream>
#define ALPHABET_SIZE 26

using namespace std;
class HashedSplays{

public:
	//size of tree
    int trees;
	//construct of HashedSplays
    HashedSplays(int size);
	//deconstruct
    ~HashedSplays();
	//read the elements inside the file
    void FileReader(string Filename);
	//print the elemnets inside in a specific index
    void PrintTree(int index);
	//print the elemnets with the specific node of letter
    void PrintTree(string letter);
	//count the frequence of the word
    void PrintHashCountResults();
	//find all the elements with the node of sample
    void FindAll(string sample);
private:
	//array table
	SplayTree<Node> table[];
	//get the index of the specific node
    string GetIndex(string inLetter);





};




#endif // HASHED_SPLAYSS_H
