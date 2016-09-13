// assembler_m.c
//
// contains main method for the assembler. reads in the input assembly code
// file and splits up labels and converts to the appropriate bytecode

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

int main(int argc, char* argv[]) {
    char* token;
    int lnNum;
    brkpnts* labels;
    char fname[33];
    char strln[256];
    FILE* ifile;

    // write output file
    FILE* ofile = fopen(argv[2], "w");
    
    // open input file
    ifile = fopen(argv[1], "r");
    
    if(ifile == 0)
        printf("Could not open file/n");

    // try to open file
    if(ifile == NULL) {
        fprintf(stderr, "Could not open file: %s\n", fname);
        exit(1);
    }

    // initialze breakpoints to add keywords to labels
    labels = brkpnts_init();
    
    lnNum = 0;

    while(fgets(strln, 256, ifile) != NULL) {
        token = strtok(strln, "\t\v\r\n\f ");

        // checking to see if first character is a keyword
        // doesn't care if it is
        if((token != NULL) && (token[0] == ':')) {
            brkpnts_update(labels, token, lnNum);
            token = strtok(NULL, "\t\v\r\n\f ");

            // added later to make sure line, might not work
            int isHash = 0;
            if(token != NULL && token[0] == '#') {
                isHash = 1; // increase to next line if comment
            }

            while((token == NULL && fgets(strln, 256, ifile) != NULL) ||
                  (isHash == 1 && fgets(strln, 256, ifile))) {

                // test next inst, increase line number after check
                token = strtok(strln, "\t\v\r\n\f ");

                if(token != NULL) {
                    // two labels share same line num      
                    if(token[0] == ':') {
                        brkpnts_update(labels, token, lnNum);
                        token = strtok(NULL, "\t\v\r\n\f ");
                    }

                    if(token != NULL && token[0] != '#')
                        isHash = 0;
                }
            }
        }

        // whole line is comment, ignore
        if(token != NULL && token[0] != '#')
            lnNum++;
    }

    // array test
    /*
    int j = 0;
    while(j < labels->size){
        char *temp = labels->keywords[j].name;
        printf("%d %s %d\n", j, temp, labels->keywords[j].lineNum);
        j++;
    }
    */

    // next pass, rewind the file to produce the opcodes
    rewind(ifile);        
    
    // start of section to read file for converting to machine code
    lnNum = 0;
    
    while( fgets (strln, 256, ifile) != NULL){
        int hash = 0;
        int instCode;
        token = strtok(strln, "\t\v\r\n\f ");

        if(token != NULL && token[0] != '#') {
            lnNum++;
            char *instruc;
            char itype;
            char firstCh = token[0];

            switch(firstCh) {
                case ':': // label line
                    token = strtok(NULL, "\t\v\r\n\f ");

                    // in case if label is by itself or has an coment afterit
                    while((token == NULL && fgets (strln, 256, ifile) != NULL)
                          || ((hash == 1) && fgets(strln, 256, ifile))) {
                        
                        token = strtok(strln, "\t\v\r\n\f ");

                        // comment checking
                        hash = 0;
                        if (token != NULL) {
                            firstCh = token[0];
                            if(firstCh == '#')
                                hash = 1;

                            if(firstCh == ':')
                                token = strtok(NULL, "\t\v\r\n\f ");               
                        }
                    }

                    // assume its an instruction
                    instruc = token;                    
                    break;

                default :
                    instruc = token;
            }

            if(hash == 0) { // should always be true
                char* tempStr;
                int regt;
                int regs;
                int regd;
                char* imm;

                itype = findType(instruc);

                switch(itype) {
                    // op rs rt rd func

                    // all registers first, special case: jr and jalr
                    case 'r':
                        token = strtok(NULL, "\r\v\r\n\f ");
                        tempStr = registerConv(token);

                        // jr, rs
                        if((strcmp(instruc, "jr") == 0) &&
                            strcmp(instruc, "jalr") == 0) {

                            sscanf(tempStr, "%i", &regs);
                            regd = 0;
                            regt = 0;
                        }

                        // rd rs rt
                        else {
                            sscanf(tempStr, "%i", &regd);
                            token = strtok(NULL, "\r\v\r\n\f ");
                            tempStr = registerConv(token);
                            sscanf(tempStr, "%i", &regs);
                            token = strtok(NULL, "\r\v\r\n\f ");
                            tempStr = registerConv(token);
                            sscanf(tempStr, "%i", &regt);
                        }
                        instCode = rType(instruc, regd, regs, regt);
                        fprintf(ofile, "0x%08x, \n", instCode);
                        break;

                    // op rs rt imm
                    case 'i':
                        // immediate can be label or a value
                        token = strtok(NULL, "\r\v\r\n\f ");

                        // rs if label follow rt
                        char* tempStr1 = registerConv(token);
                        token = strtok(NULL, "\r\v\r\n\f ");
                        int regsControl = isLabel(labels, token);

                        // not label, then instuction is rs rd imm
                        if(regsControl == 0 && instruc[0] != 'b' &&
                           instruc[0] != 'l' && instruc[0] != 's') {

                            // instruc addi, addui; rt rs imm
                            sscanf(tempStr1, "%i", &regt);  
                            tempStr = registerConv(token);
                            sscanf(tempStr, "%i", &regs);
                            token = strtok(NULL, "\r\v\r\n\f ");
                            imm = token;
                        }

                        else if((regsControl == 0) &&
                                (strcmp(instruc, "lui") != 0) &&
                                (instruc[0] == 'b' || instruc[0] == 'l' ||
                                 instruc[0] == 's')) {
                            
                            // instruction beq, bne; rs rt imm
                            if(instruc[0] == 'l' || instruc[0] == 's') {
                                sscanf(tempStr1, "%i", &regt);                             
                                tempStr = registerConv(token);
                                sscanf(tempStr, "%i", &regs);
                                token = strtok(NULL, "\r\v\r\n\f ");
                                imm = token;
                            }
                            else {
                                sscanf(tempStr1, "%i", &regs);                             
                                tempStr = registerConv(token);
                                sscanf(tempStr, "%i", &regt);
                                token = strtok(NULL, "\r\v\r\n\f ");
                                imm = token;
                            }
                        }

                        // instruc rt imm
                        else if(strcmp(instruc, "lui") == 0) { 
                            sscanf(tempStr1, "%i", &regt);
                            regs = 0;
                            imm = token;            
                            
                        }

                        // instuciton rs label
                        else {
                            sscanf(tempStr1, "%i", &regs);
                            regt = 0;
                            imm = token;
                        }

                        instCode = iType(instruc, regt, regs, imm, labels,
                                         lnNum);
                        fprintf(ofile, "0x%08x, \n", instCode);
                        break;

                    // j or jal instruction
                    case 'j':
                        token = strtok(NULL, "\r\v\r\n\f ");
                        imm = token;
                        instCode = jType(instruc, imm, labels);
                        fprintf(ofile, "0x%08x, \n", instCode);
                        break;

                    // c-type
                    case 'c':
                        token = strtok(NULL, "\r\v\r\n\f ");  // scan $rd
                        tempStr = registerConv(token);
                        sscanf(tempStr, "%i", &regd);

                        // get imm
                        if(strcmp(instruc, "scn") != 0) {
                            token = strtok(NULL, "\r\v\r\n\f ");
                            imm = token;
                        }
                        else {
                            token = "0";
                            imm = token; // imm of scn instruction = 0
                        }

                        instCode = cType(instruc, regd, imm, labels, lnNum);
                        fprintf(ofile, "0x%08x, \n", instCode);
                        break;

                    default: 

                        // jump location marker
                        if(token[0] != '#') {
                            token = strtok(NULL, "\r\v\r\n\f ");
                            while(token != NULL && token[0] != '#') {
                                int tData;
                                sscanf(token, "%i", &tData);
                                fprintf(ofile, "0x%08x, \n", tData);
                                token = strtok(NULL, "\r\v\r\n\f ");
                            }
                        }
                }        
            }        
        }
    }

    labels_delete(labels);
    
    // getchar();
    return 0;    
}
