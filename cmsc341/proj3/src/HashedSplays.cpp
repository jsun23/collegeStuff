/**
** Project: Project 3
** Filename: HashedSplays.h
** Author: Dong Sun
** Email: dongsun1@umbc.edu
** Date: 11/4/2014
**
** HashedSplays.cpp is most of the functions to set up the splaytree and looking
** through the tree find the index and the words
**/


#include "HashedSplays.h"


HashedSplays::HashedSplays(int size)
{
    trees=size;
}
/*
FileReader function read a file and put the words into a splay tree,
remove all the numbers, period, commar and space
precondition: filename
postcondition: table[]
*/
void HashedSplays::FileReader(string Filename)
{

    ifstream myfile;
    myfile.open(Filename);
	
	for(int i = 0; i<trees;i++)
    {
		int y;
		Node n = Node(myfile.getline, i);
        table[i].insert(n);
	   if (myfile.getline == y || "," || " "||"_"||".")
	   {
		   table[i].remove(n);
	   }
    }

    
	myfile.close();
}
/*
find all function will find all the words in the splay tree begin with sample
precondition: Node with sample
postcondtion: None
*/

void HashedSplays::FindAll(string sample)
{
	
	for (int i = 0; i < trees; i++)
	{
		if(table[i].contains(Node(sample, i)))
		{
			table[i].printTree();
		}
	}
}

/*
PrintTree function will print the splay in the specific index
precondition: index
postcondition: NULL

*/
void HashedSplays::PrintTree(int index)
{
    for(int i=0; i<index; i++)
    {
        table[i].printTree();
    }
}
/*
PrintTree function will print the splay in the specific letter
precondition: letter
postcondition: NULL

*/
void HashedSplays::PrintTree(string letter)
{

	for (int i = 0; i < trees; i++)
	{
		if (table[i].contains(Node(letter,i)))
		{
			table[i].printTree();
		}
	}
}
/*
PrintHashCountResults function will print the frequence of the splay tree and
debug the tree
precondition: NULL
postcondition: NULL

*/
void HashedSplays::PrintHashCountResults()
{
	Node n;
	for (int i = 0; i < trees; i++)
	{
		if (table[i].contains(n))
		{
			n.IncrementFrequency;
		}
	}
}
/*
Deconstruct of HashedSplays class
*/
HashedSplays::~HashedSplays(){}

/*
GetIndex is a private function to find the index of the specific string
*/
string HashedSplays::GetIndex(string inLetter)
{
	for (int i = 0; i < trees; i++)
    if(table[i].contains(Node(inLetter,i)))
    {
        return Node(inLetter,1).GetFrequency;
    }
}
