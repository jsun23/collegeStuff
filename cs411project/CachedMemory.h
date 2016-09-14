/**************************
	James Bilbrey (bilbrey1@umbc.edu)
	CachedMemory.h
	CMSC 411 Fall 2015 Project
**************************/

#ifndef CACHEDMEMORY_H
#define CACHEDMEMORY_H

class CachedMemory
{
	public:
   	 
		CachedMemory(int* asmCode);
	
		bool isInstructionCached(int address);

		bool isDataCached(int address);

		int accessInstruction(int address);

		int accessData(int address);
		
		void writeData(int address, int data);
	
	private:
	
		/** Intended cache structure
		**	[index|description]
		**	[00|undecided]
		**	[01|addresses of slots 4-7]
		**	[02|addresses of slots 8-11]
		**	[03|addresses of slots 12-15]
		**	[04-15|stored item]
		**/
		
		int isCached(int* side, int address);
		
		int access(int* side, int address);
		
		void cache(int* side, int address, int data);
	
		int instructionCache[16], // 4B * 16 = 64B
			dataCache[16],
			memory[1024]; // 4B * 1024 = 4kB
		
};

#endif
