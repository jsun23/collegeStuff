/**
** Project: Project 3
** Filename: Util.h
** Author: Dong Sun
** Email: dongsun1@umbc.edu
** Date: 11/4/2014
**
** Util.h support Node.h to check the string in the node make sure there is no
** case problem or spaces.
**
**/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#ifndef UTIL_H
#define UTIL_H

class Util{
public:	
	static string  Lower(string inString)
	{
		
		transform(inString.begin(), inString.end(), inString.begin(), tolower);
		return inString;
		
	};
	bool FileExists(char *fileName)
	{
		if (fileName != NULL)
		{
			return true;
		}
		else
			return false;
	
	};
	static string Strip(string inString)
	{
		if (inString != " "||"_"||","||".")
		{
			return inString;
		}
	};

};

#endif