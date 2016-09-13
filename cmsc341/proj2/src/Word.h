/*
** Filename: Word.h
** Project: Project2
** Class: CMSC341
** Name: Dong Sun
** Date: 10/21/2014
** Email: dongsun1@umbc.edu
**
** set valuables and function of Word class
**
*/





#ifndef WORD_H
#define WORD_H
#include <string>
#include <queue>

using namespace std;

class Word{
private:
	int count;
	queue<int> lineNumber;
	string wordText;
public:
	Word();
	Word(string inWord, int lineNumber = 0);
	void CountWord(int lineNumber);
	string GetWord();
	int GetCount();
	bool operator < ( Word &RHS);
	Word operator =( Word &RHS);
	bool operator == ( Word &RHS);
	friend ostream operator << (const ostream out, Word &inWord);
};


#endif