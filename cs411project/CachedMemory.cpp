/**************************
	James Bilbrey (bilbrey1@umbc.edu)
	CachedMemory.h
	CMSC 411 Fall 2015 Project
**************************/

#include "CachedMemory.h"

/** Intended cache structure
**	[index|description]
**	[00|undecided]
**	[01|addresses of slots 4-7]
**	[02|addresses of slots 8-11]
**	[03|addresses of slots 12-15]
**	[04-15|stored item]
**
**	(Supports addresses up to 255. Even that is way larger than our program needs.)
**
**	int instructionCache[16], // 4B * 16 = 64B
**		dataCache[16],
**		memory[1024]; // 4B * 1024 = 4kB
*/

union SimpleConverter
{
	int cint;
	char chars[4];
} conv;

CachedMemory::CachedMemory(int* asmCode)
{
	memory = asmCode;
}

int CachedMemory::isCached(int* side, int address)
{
	if (address > 0xFF)
	{
		return -1;
	}
	
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			conv.cint = side[i];
			if (conv.chars[j] == (char) address)
			{
				return i * 4 + j;
			}
		}
	}
	return -1;
}

int CachedMemory::access(int* side, int address)
{
	return side[isCached(side, address)];
}

void CachedMemory::cache(int* side, int address, int data)
{
	if (address > 0xFF)
	{
		return;
	}
	
	int slot = isCached(dataCache, address);
	if (slot >= 0) // isCached
	{
		dataCache[slot] = data;
	}
	else
	{
		dataCache[dataCache[0]] = data;
		conv.cint = dataCache[dataCache[0] / 4];
		conv.chars[dataCache[0] % 4] = (char) address;
	}
}

bool CachedMemory::isInstructionCached(int address)
{
	return isCached(instructionCache, address) >= 0;
}

int CachedMemory::accessInstruction(int address)
{
	access(instructionCache, address);
}

bool CachedMemory::isDataCached(int address)
{
	return isCached(dataCache, address) >= 0;
}

int CachedMemory::accessData(int address)
{
	access(dataCache, address);
}

void CachedMemory::writeData(int address, int data)
{
	memory[address] = data;
}
