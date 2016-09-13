/*
** Filename: Indexer.cpp
** Project: Project2
** Class: CMSC341
** Name: Dong Sun
** Date: 10/21/2014
** Email: dongsun1@umbc.edu
**
** Basic declare functions of Indexer.h
*/

#include "Indexer.h"
/*
	Construct of Indexer class, passing in the filename that the program going to use

*/
Indexer::Indexer(string filterName, string dateFile)
{
	filterfile = filterName;
	datefile = dateFile;
}
/*
	check if the file is exist of not
	pre: filename
	post: true or false
*/
bool Indexer::fildExists(char* filename)
{
	if (filename != NULL)
		return true;
	else
		return false;

}
/*
	fileFilterReader get the elements in filter file and pass them in a BST

*/
BinarySearchTree<Word> Indexer::fileFilterReader(string filename)
{
	fstream infile;
	infile.open(filename.c_str(), ios_base::in);
	filteredBST.insert(infile.getline);

	infile.close;
}
/*
	fileWordReader get the elements in data file to find the elements, if the elements are same
	record the linenumber and count the number of the same elements.
	pass each element into the BST

*/
BinarySearchTree<Word> Indexer::fileWordReader(string filename)
{
	fstream infile;
	int linenumber=1;
	infile.open(filename.c_str, ios_base::in);
	if (infile.getline != infile.getline->next)
	{
		indexedBST.insert(infile.getline);
	}
	else if (infile.getline->next == NULL)
	{
		linenumber += 1;
	}
	else if (infile.getline->next == infile.getline || indexedBST.contains(infile.getline))
	{

		Word newWord = Word(infile.getline, linenumber);
		newWord.CountWord(linenumber);

	}
		infile.close;

}
/*
	using the overload << to output the result
*/
void Indexer::outputResulte()
{
	cout << endl ;


}
/*
	run the functions here
	check the given files are exsit
	then run the functions and get output
*/
void Indexer::DoIndex()
{
	if (fildExists(filterfile.c_str))
	{
		//run the filter function to set up the BST for filter file
		fileFilterReader(filterfile);
	}
	if (fildExists(datefile.c_str))
	{
		//run the Reader function to set up and find the same words in data file
		fileWordReader(datefile);
	}
	else
	{
		//if the file doen't exsit, throw an exception
		throw Exceptions("Cannot find the file!!");
	}
	outputResulte();
}
