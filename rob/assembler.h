// assembler.h

#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

// breakpoint in assembler code
typedef struct breakpnt {
    char *name; 
    int lineNum;
} breakpnt;

typedef struct brkpnts {
    int maxSize;  // size of entire allocation
    int size;     // number of elements 
    breakpnt *keywords;
} brkpnts;


// function headers
brkpnts* brkpnts_init();

char* registerConv(char* token);
void brkpnts_update(brkpnts* plabels, char* token, int lineNum);

// handlers for different instruction types
int jType(char* instruc, char* address, brkpnts* labels);
int iType(char* instruc, int rt, int rs, char* imm, brkpnts* labels,
          int lineptr);
int rType(char* instruc, int rd, int rs, int rt);
int cType(char* instruc, int regd, char *imm, brkpnts *labels, int lineptr);

int findFC(char* instruc);
char findType(char* instruc);

// lable parsing
void labels_delete(brkpnts *plabels);
int isLabel(brkpnts* labels, char* imm);

#endif
