/*
** Filename: Word.cpp
** Project: Project2
** Class: CMSC341
** Name: Dong Sun
** Date: 10/21/2014
** Email: dongsun1@umbc.edu
** 
** Basic declare functions of Word.h
*/



#include "Word.h"

//Empty Construct for Word class
Word::Word()
{

}
//Construct for Word class
Word::Word(string inWord, int lineNumber)
{
	wordText = inWord;
	lineNumber = lineNumber;

}
/*
CountWrod function to store the linenumber into a queue and count the numbers
*/
void Word::CountWord(int linenumber)
{
	if (lineNumber.front != linenumber)
	{
		lineNumber.push(linenumber);
		CountWord(linenumber);
	}
	else
		count += 1;

}
//getting for count valuable
int Word::GetCount()
{ 
	return count; 
}

/*
	getting for wordText
*/
string Word::GetWord()
{
	return wordText;
}
/*
	overloading < operation
*/
bool Word::operator<(Word& RHS)
{
	if (RHS.GetWord() < wordText)
		return true;
	else
		return false;
}
/*
	overloading operator =
*/
Word Word::operator=(Word& RHS)
{
	return RHS;
}
/*
	overloading operator ==
*/
bool Word::operator == (Word& RHS)
{
	return RHS.GetWord() == wordText;
}
/*
	overloading operator <<
	set the output for the program.
*/
ostream operator << (const ostream out, Word &inWord)
{
	out << "<" << inWord.GetWord() << ">" << ".............." << "<"<< inWord.GetCount() << ">" << inWord.lineNumber.pop;	
}
