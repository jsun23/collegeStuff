// assembler_labels.c

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

// todo: init array for keyword labels

brkpnts* brkpnts_init() {
    brkpnts temp;
    brkpnts* ptemp = (brkpnts*)malloc(1 * sizeof(brkpnts));
    assert(ptemp != NULL);

    temp.size = 0;
    temp.maxSize = 10;
    temp.keywords = (breakpnt*)malloc(10 * sizeof(breakpnt));
    ptemp[0] = temp;

    return ptemp;
}

// add to label array
void brkpnts_update(brkpnts* plabels, char *token, int lineNum) {
    int strlgth;

    if(plabels->size == plabels->maxSize) {
        // increase array size
        plabels->maxSize = plabels->maxSize * 2;
        breakpnt *ptemp = (breakpnt *) malloc(plabels->maxSize*sizeof(breakpnt));
        assert(ptemp != NULL);

        int i = 0;
        while(plabels->size > i) {
            ptemp[i] = plabels->keywords[i];
            i++;
        }

        free(plabels->keywords);
        plabels->keywords = ptemp;
    }
     
    strlgth = strlen(token);

    // copying string without the :
    char* newLbl;
    newLbl = (char*)malloc(strlgth * sizeof(char));

    int i = 0;
    while(i < strlgth) {
        newLbl[i] = token[i+1];
        i++;
    }

    breakpnt btemp;
    btemp.name = newLbl;
    btemp.lineNum = lineNum;
    // printf("%s", btemp.name);

    // assigning the new breakpoint to the end of the array
    plabels->keywords[plabels->size] = btemp;
    plabels->size = plabels->size + 1;
    
    // printf("%s %d \n", plabels->keywords[plabels->size - 1].name,
    //         plabels->keywords[plabels->size - 1].lineNum);
}

// frees up the structure after program is done
void labels_delete(brkpnts* plabels) {
    free(plabels->keywords);
    free(plabels);
}
