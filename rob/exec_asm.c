// exec_asm.c
//
// takes code file code.h and executes the instructions, or terminates if the
// instructions do not make sense
//
// now with instruction pipelining, causing several conditions to become
// indecipherable in the code
//
// stages of pipeline:
// 1. IF = inst fetch
// 2. ID = inst decode
// 3. EX = execute
// 4. DM = data memory      (also contains robot control)
// 5. WB = write back       (start with 5 and work upwards in main)


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// stuff
#define NOOP 0xffffffff
#define DEFAULTFN 0
#define DEFAULTCFN 8
#define DEFAULTWB 0

// IF stage helper func
int storeInstruction(int *mem, int pc) {
    return mem[pc];
}

// ID stage helper func
int instDecodeitype(int tempinstruc) {

    if(tempinstruc == 0)
        return 0;       // r-type
    else if(tempinstruc == 19)
        return 1;       // c-type
    else if(tempinstruc == 2 || tempinstruc == 3)
        return 2;       // j-type
    else
        return 3;       // i-type
}

int idR1(int iR) {
    return (iR >> 21) & 31;
}

int idR2(int iR) {
    return (iR >> 16) & 31;
}

int idimm(int iR) {
    int imm;
    imm = iR & 0x0000ffff;

    // sign extension in mips so no ALU operation
    if((imm & 0x00008000) > 0)
        imm = 0xffff0000 | imm;

    return imm;
}

// EX stage helper function
int alu(int val1, int val2, int opcd, int fn, int brVal) {

    // opcd and fn are control signals, fn could be function or cfn
    int zeroResult;  //As seen in the book for alu
    int signResult;
    
    if(opcd == 0 && fn == 32) {       // add
        return (val1 + val2);
    }
    else if(opcd == 0 && fn == 33) {  // addu
        // alu logic to flip the top bits
        unsigned int d, p1, p2;
        p1 = val1;
        p2 = val2;
        d = p1 + p2;
        return d;
    }
    else if(opcd == 0 && fn == 34) {  // sub
        return (val1 - val2);
    }
    else if(opcd == 0 && fn == 35) {  // subu
        unsigned int d, p1, p2;
        p1 = val1;
        p2 = val2;
        d = p1 - p2;
        return d;
    }
    else if(opcd == 0 && fn == 36) {  // and
        return (val1 & val2);
    }
    else if(opcd == 0 && fn == 37) {  // or
         return(val1 | val2);
    }
    else if(opcd == 0 && fn == 38) {  // xor
        return(val1 ^ val2);
    }
    else if(opcd == 0 && fn == 39) {  // nor
        return ~(val1 | val2);
    }
    else if(opcd == 19 && (fn ==0 || fn == 1 || fn == 3)) { // spd, rot, fir
        return (val1 + val2);
    }
    
    // alu has logic inside to ouput 1 if zero is true or 0 if not true
    // for the branch instuctions
    else if(opcd == 4) {              // beq
        if((val1 - brVal) == 0)
            zeroResult =1;            // pc = pc + imm;
        else
            zeroResult = 0;

        return zeroResult;
    }
    else if(opcd == 5) {              // bne
        if ((val1 - brVal) != 0)
            zeroResult = 0;
        else 
            zeroResult = 1;

        return zeroResult;
    }

    // alu has logic inside for certain branch instruction to return 0
    // if positive or 1 for negative
    else if(opcd == 6) {              // blez
        if((val1 - 0) <= 0)
            signResult = 0;
        else
            signResult = 1;

        return signResult;
    }
    else if(opcd == 7) {              // bgtz
        if((val1 - 0) > 0)
            signResult = 1;
        else
            signResult = 0;

        return signResult;
    }
    else if(opcd == 8 || opcd == 9 ) { // addi + addiu
        if(opcd == 9)                  // addiu
            val2 = 0x0000ffff & val2;  // no sign extend
        return (val1 + val2);
    }
    else if(opcd == 12)                // andi
        return (val1 & val2);
    else if(opcd == 13)                // ori
        return (val1 | val2);
    else if(opcd == 14)                // xori
        return (val1 ^ val2);

    // alu will be able to logically shift bits within
    else if(opcd == 15)                // lui
        return (val2 << 16);
    else if(opcd == 35  || opcd == 43) // lw + sw
        return (val1 + val2);
    else {                             // invalid instruction, kill
        exit(1);
    }
}

int main() {
    // compile machine code file 
    int mem[1024] = {
        #include "code.h"
    };

    int reg[32];    // registers
    reg[0] = 0;
    int pc = 0;     // current program counter
    char line[256]; // line from keyboard
    int killRobot = 0;

    // registers to store values in between cycles
    int nPC1, nPC2, nPC3, nPC4, iR1 = NOOP, iR2 = NOOP, iR3 = NOOP,
        iR4 = NOOP, r1, r2, r22, imm, aluResult, aluResult2, dataResult,
        scnReg, tPC;

    // control signals
    int opCd1, opCd2, opCd3, opCd4, fn1, fn2, fn3, fn4, cFN1, cFN2, cFN3, cFN4,
        conSig1, conSig2,conSig3, conSig4, wBReg1, wBReg2, wBReg3, wBReg4,
        stall = 0;

    // control signal to let cpu know that current stage is going to be used on
    // next stage (forwarding)
    int jumpRecent = 0, contEXStage = 0;

    // alu variables for mult, multi, div, divi
    long long multiplicand, multiplier, product, qr;
    unsigned long long productu, qru;
    int remainder, quotient, bit, divisor;
    unsigned int multiplicandu, multiplieru, remainderu, quotientu, bitu,
                 divisoru;
    
    // program counter init
    tPC = pc;

    // wait for input
    fgets(line, sizeof(line), stdin);

    // main parsing loop begin
    while(killRobot == 0) { 
        reg[0] = 0;
        
        /* START OF STAGE 5 OF PIPELINE */

        /* begin WRITE BACK (WB) phase */
        // code to make contol easier
        // NEED LOGIC FOR VALID
        if(iR4 != NOOP) {
            // printf("Entered S5\n");
            int branches = 0;
            if(opCd4 == 4 || opCd4 == 5 || opCd4 == 6 || opCd4 == 7) {
                branches = 1;
            }
        
            if(branches == 0 && opCd4 != 43 && opCd4 != 2 &&
               (conSig4 != 1 || cFN4 == 2) && fn4 != 8) {
                // branhes, sw, j, scn, jr
            
                int writeReg;       // write destination
                if(conSig4 == 1) {  // scn would be only one in statement
                    writeReg = iR4>>16 & 31;
                    reg[writeReg] = scnReg;
                }
                else if(opCd4 == 35) { // lw only writeback to registers
                    writeReg = iR4>>16 & 31;
                    reg[writeReg] = dataResult;
                }
                else if(fn4 == 9 || opCd4 ==  3) { // jump and link instructions
                    writeReg = 31;
                    reg[writeReg] = nPC4;
                }
                else {  // the rest would be from aluResult
                    if(conSig4 == 0)
                        writeReg = iR4>>11 & 31;
                    else
                        writeReg = iR4>>16 & 31;

                    reg[writeReg] = aluResult2;
                }    
            }
        }
        /* end of WRITE BACK (WB) phase */
        /* END OF STAGE 5 */
        
        /* START OF STAGE 4 OF PIPELINE */
        // the stage combines the data memory and robot control since
        // they never use the same structure at the same time, so  every cycle
        // the robot can control automatically prints N unless it is processing
        // a robot action

        /* begin DATA MEMORY (DM) phase */
        // lw sw
        if(iR3 != NOOP) {
            // printf("entered S4 \n");
            if(opCd3 == 35 || opCd3 ==43) {
                if (opCd3 == 35)
                    dataResult = mem[aluResult];
                else if (opCd3 == 43)
                    mem[aluResult] = r22;
                else
                    exit(1);
            }
        }
        /* end of DATA MEMORY (DM) phase */
        
        /* begin ROBOT CONTROL UNIT (RCU) phase */
        // enter unit only if robot instruction 
        if(conSig3 == 1) {
            if(iR3 != NOOP) {
                if(cFN3 != 2) {
                    if(cFN3 == 0) {
                        printf("M %d\n", aluResult);
                    }
                    else if(cFN3 == 1) {
                        printf("R %d\n", aluResult);
                    }
                    else if(cFN3 == 3) {
                        printf("F %d\n", aluResult);
                    }
                    else {
                        exit(1);
                    }
                }
                else if(cFN3 == 2) {
                    printf("S\n");
                    fgets(line, sizeof(line), stdin);
                    sscanf(line, "%i", &scnReg);
                }
            }
        }
        else {
            printf("N\n");
        }

        // print N even if NOOP
        if(conSig3 == 1 && iR3 == NOOP)
            printf("N\n");
     
        iR4 = iR3;
        nPC4 = nPC3;
        aluResult2 = aluResult;

        // in practice, control signals will not transfer like this but would
        // refer to the iR4 for control signals, however it simplifies coding
        opCd4 = opCd3;
        fn4 = fn3;
        cFN4 = cFN3;
        conSig4 = conSig3;
        wBReg4 = wBReg3;            
        /* end of RCU phase */
        /* END OF STAGE 4 */
        
        
        /* START OF STAGE 3 OF PIPELINE */
        /* begin EXECUTION (EX) phase */
        if(iR2 != NOOP) {
            // printf("Entered S3\n");
            if(contEXStage == 0) {
                if(fn2 != 8 && fn2 != 9 && cFN2 != 2 && conSig2 != 2 ) { 
                    // jr, jalr, scn, j-type
                    // mux signals can point to r2, imm, npc
                    if(conSig2 == 0) { // so use r2 r-type
                        // mult, multu, div, divu all use the ALU but to
                        // implement it in this pipeline the calculations are
                        // done outside the alu method. in reality, the
                        // calculations of these instructions take place in the
                        // ALU
                        if(fn2 != 24 && fn2 != 25 && fn2 != 26 && fn2 != 27)
                            aluResult = alu(r1, r2, opCd2, fn2, 0);

                        else {
                            if(fn2 == 24 || fn2 == 25) { // mult, multu
                                contEXStage = 64;
                                if(fn2 == 24) {
                                    multiplicand = r1, multiplier = r2;
                                    product = 0;

                                    if(multiplier & 1)
                                        product += multiplicand;

                                    multiplier >>= 1;
                                    multiplicand <<= 1;
                                }
                                else {
                                    multiplicandu = r1, multiplieru = r2;
                                    productu = 0;

                                    if(multiplieru & 1) 
                                        productu += multiplicandu;

                                    multiplieru >>= 1;
                                    multiplicandu <<= 1;
                                }

                                contEXStage--;
                            }

                            if(fn2 == 26 || fn2 == 27) {
                                // div, divu are implemented the same way
                                contEXStage = 32;
                                if(fn2 == 26) {
                                    divisor = r2;
                                    qr = r1;
                                    remainder = qr >> 31;
                                    bit = (remainder >= divisor);
                                    if(bit) remainder -= divisor;
                                    qr = ((long long)remainder << 32) |
                                         ((qr << 1) & 0xffffffff) | bit;
                                }
                                else {
                                    divisoru = r2;
                                    qru = r1;
                                    remainderu = qru >> 31;
                                    bitu = (remainderu >= divisoru);
                                    if(bitu) remainderu -= divisoru;
                                    qru = ((long long)remainderu << 32) |
                                          ((qru << 1) & 0xffffffff) | bitu;
                                }

                                contEXStage--;
                            }
                            stall = 1;
                        }
                    }

                    else if(conSig2 == 1) { // use imm c-type
                        aluResult = alu(r1, imm, opCd2, cFN2, 0);
                    }

                    else if(conSig2 == 3) { // i-type
                        // aluResult will equal the zeroResult of the ALU iff
                        // opCd ctrl signal indicates a branch

                        // 1 will be the result if branch is true
                        if(opCd2 ==4 || opCd2 == 5)
                            aluResult = alu(r1, imm, opCd2, 0, r2);
                        else {
                            if(opCd2 == 35 || opCd2 == 43)
                                aluResult = alu(r1, imm >> 2, opCd2, 0, 0);
                            else
                                aluResult = alu(r1, imm, opCd2, 0, 0);
                        }
                        if(opCd2 == 4 || opCd2 == 5 ) { // beq bne 
                            if(opCd2 == 4 && aluResult == 1) {
                                pc = nPC2 + imm;
                                jumpRecent = 1;
                            }
                            else if(opCd2 == 5 && aluResult == 0) {
                                pc = nPC2 + imm;
                                jumpRecent = 1;
                            }
                        }
                        else if(opCd2 == 6 || opCd2 ==7) { // blez bgtz
                            if(opCd2 == 6 && aluResult == 0) {
                                pc = nPC2 + imm;
                                jumpRecent = 1;
                            }
                            else if(opCd2 == 7 && aluResult == 1) {
                                pc = nPC2 + imm;
                                jumpRecent = 1;
                            }
                        }

                        // ?????????
                        if(jumpRecent == 1 ) {
                            iR1 = NOOP;
                        }
                    }    
                }
            }

            if(contEXStage > 0) {
                stall = 1;
                if(fn2 == 24 || fn2 == 25) { // mult, multu
                    if(fn2 == 24) {
                        if(multiplier & 1)
                            product += multiplicand;
                        multiplier >>= 1;
                        multiplicand <<= 1;
                    }
                    else {
                        if(multiplieru & 1) 
                            productu += multiplicandu;
                        multiplieru >>= 1;
                        multiplicandu <<= 1;
                    }

                    contEXStage--;
                }

                if(fn2 == 26 || fn2 == 27) {
                    if(fn2 == 26) {
                        remainder = qr >> 31;
                        bit = (remainder >= divisor);
                        if(bit) remainder -= divisor;
                        qr = ((long long)remainder << 32) |
                             ((qr << 1) & 0xffffffff) | bit;
                    }
                    else {
                        remainderu = qru >> 31;
                        bitu = (remainderu >= divisoru);
                        if(bitu) remainderu -= divisoru;
                        qru = ((long long)remainderu << 32) |
                              ((qru << 1) & 0xffffffff) | bitu;
                    }

                    contEXStage--;
                }

                if(contEXStage == 1) {
                    if(fn2 == 26)
                        aluResult = product;
                    else if(fn2 == 25)
                        aluResult = productu;
                    else if(fn2 == 26) {
                        quotient = qr & 0xffffffff;
                        aluResult = quotient;
                    }
                    else if(fn2 == 27) {
                        quotientu = qru & 0xffffffff;
                        aluResult = quotientu;
                    }

                    contEXStage = 0;
                    stall = 0;
                }
                else {
                    iR3 = NOOP;
                }
            }
        }

        if(contEXStage == 0) {
            iR3 = iR2;
            nPC3 = nPC2;
            r22 = r2;

            opCd3 = opCd2;
            fn3 = fn2;
            cFN3 = cFN2;
            conSig3 = conSig2;
            wBReg3 = wBReg2;
        }        
        /* end EX phase */
        /* END OF STAGE 3 */
        
        
        /* START OF STAGE 2 OF PIPELINE */

        /* begin INSTRUCTION DECODE (ID) phase */
        // results are writen in registers near the end of cycle
        if(iR1 != NOOP && stall == 0) {
            // printf("entered S2\n");
            conSig1 = instDecodeitype(iR1 >> 26);
            opCd1 = (iR1>>26) & 63;
        
            if(conSig1 == 0) { // r-type
                fn1 = iR1 & 63;
                int regnum1 = idR1(iR1);
                int regnum2 = idR2(iR1);

                if(fn1 == 9)
                    wBReg1 = 31;
                else if(fn1 == 8)
                    wBReg1 = DEFAULTWB;
                else
                    wBReg1 = iR1>>11 & 31;

                // checks if the used registers are up to date, if not stalls
                if(fn1 != 9 && fn1 != 8 &&
                   ((iR3 != NOOP && (((regnum1 == wBReg3) ||
                                      (regnum2 == wBReg3))
                                 && wBReg3 != DEFAULTWB)) ||
                   (iR4 != NOOP && (((regnum1 == wBReg4) ||
                                     (regnum2 == wBReg4)) &&
                                      wBReg4 != DEFAULTWB))
                   )
                   ) {
                    stall = 1;
                }

                else if(
                    (iR3 != NOOP && regnum1 == wBReg3 && wBReg3 != DEFAULTWB) ||
                    (iR4 != NOOP && regnum1 == wBReg4 && wBReg4 != DEFAULTWB)) {
                    // jr, jalr
                    stall = 1;
                }
                if(stall == 0) {
                    r1 = reg[regnum1];
                    r2 = reg[regnum2];
                    cFN1 = DEFAULTCFN;
                    if(fn1 == 8 || fn1 == 9) { //jr and jalr
                        pc = r1;
                        jumpRecent = 1;
                    }
                }

                else if(cFN3 != 2 && cFN4 != 2 && opCd3 != 35 && opCd4 != 35) {
                    // stall = 1, so we know that either iR3 is not noop or iR4
                    // is noop and wB reg matches a reg to be used for anything
                    // but lw, which would use aluResult 1 or 2

                    int isR1 = 0, isR2 = 0;

                    // make sure that iR3 aluResult replaces one then
                    // iR4 aluResult should not replace it again giving wrong
                    // result
                    if(iR3 != NOOP && regnum1 == wBReg3 && wBReg3 != DEFAULTWB)
                       {
                        r1 = aluResult;
                        r2 = reg[regnum2];
                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR1 = 1;
                    }

                    if(iR3 != NOOP && fn1 != 8 && fn1 != 9 &&
                       (regnum2 == wBReg3 && wBReg3 != DEFAULTWB)) {
                        r2 = aluResult;

                        if(isR1 == 0) r1 = reg[regnum1];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR2 = 1;
                    }

                    if(isR1 == 0 && iR4 != NOOP && regnum1 == wBReg3 &&
                       wBReg3 != DEFAULTWB) {
                        r1 = aluResult2;

                        if(isR2 == 0) r2 = reg[regnum2];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR1 = 1;
                    }

                    if(isR2 == 0 && iR4 != NOOP && fn1 != 8 && fn1 != 9 &&
                       (regnum2 == wBReg3 && wBReg3 != DEFAULTWB)) {
                        r2 = aluResult2;

                        if(isR1 == 0)
                            r1 = reg[regnum1];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR2 = 1;
                    }
                    if(fn1 == 8 || fn1 == 9) { // jr and jalr
                        pc = r1;
                        jumpRecent = 1;
                    }
                }

                // iff there is a match in iR3 (except fn = 2 and opcd = 35)
                // to write back and none matching in iR4 
                else if(cFN3 != 2 && iR3 != NOOP && opCd3 != 35 &&
                        !((iR4 !=NOOP && fn1 != 8 && fn1 != 9 &&
                        (((regnum1 == wBReg4) || (regnum2 == wBReg4)) &&
                        wBReg4 != DEFAULTWB)) || (iR4 != NOOP &&
                                                  regnum1 == wBReg4 &&
                                                  wBReg4 != DEFAULTWB))
                       ) {

                    int isR1 = 0;
                    if(regnum1 == wBReg3 && wBReg3 != DEFAULTWB) {
                        r1 = aluResult;
                        r2 = reg[regnum2];
                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR1 = 1;
                    }
                    if(fn1 != 8 && fn1 != 9 && (regnum2 == wBReg3 &&
                                                wBReg3 != DEFAULTWB)) {
                        r2 = aluResult;

                        if(isR1 == 0)
                            r1 = reg[regnum1];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                    }
                    if(fn1 == 8 || fn1 == 9) { // jr and jalr
                        pc = r1;
                        jumpRecent = 1;
                    }
                }

                // iff there is a match in iR4 (except fn = 2 and opcd = 35)
                // to write back and none matching in iR3 
                else if(cFN4 != 2 && iR4 != NOOP && opCd4 != 35 &&
                        !((iR3 != NOOP && fn1 != 8 && fn1 != 9 &&
                        (((regnum1 == wBReg3) || (regnum2 == wBReg3)) &&
                        wBReg3 != DEFAULTWB)) || (iR3 != NOOP &&
                                                  regnum1 == wBReg3 &&
                                                  wBReg3 != DEFAULTWB))
                       ) {

                    int isR1 = 0;
                    if(regnum1 == wBReg4 && wBReg4 != DEFAULTWB) {
                        r1 = aluResult2;
                        r2 = reg[regnum2];
                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR1 = 1;
                    }
                    if(fn1 != 8 && fn1 != 9 && (regnum2 == wBReg4 &&
                                                wBReg4 != DEFAULTWB)) {
                        r2 = aluResult2;

                        if(isR1 == 0)
                            r1 = reg[regnum1];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                    }
                    if(fn1 == 8 || fn1 == 9) { // jr and jalr
                        pc = r1;
                        jumpRecent = 1;
                    }
                }

                // if fn4 = 2 and there is a match in iR4 and iR3 is either
                // populated with a write back that is not opcd 35 or fn 2, or
                // no write back at all
                else if(iR4 != NOOP && cFN4 == 2 && (((opCd3 != 35 &&
                        cFN3 != 2 && iR3 != NOOP && fn1 != 8 && fn1 != 9 &&
                        (((regnum1 == wBReg3) || (regnum2 == wBReg3)) &&
                        wBReg3 != DEFAULTWB)) || (opCd3 != 35 && fn3 != 2 &&
                        iR3 != NOOP && regnum1 == wBReg3 &&
                        wBReg3 != DEFAULTWB)) || !((iR3 != NOOP && fn1 != 8 &&
                        fn1 != 9 && (((regnum1 == wBReg3) ||
                        (regnum2 == wBReg3)) && wBReg3 != DEFAULTWB)) ||
                        (iR3 != NOOP && regnum1 == wBReg3 &&
                        wBReg3 != DEFAULTWB)))) {

                    // only for scn in iR4
                    int isR1 = 0;
                    if(regnum1 == wBReg4 && wBReg4 != DEFAULTWB) {
                        r1 = scnReg;
                        r2 = reg[regnum2];
                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR1 = 1;
                    }
                    if(fn1 != 8 && fn1 != 9 && (regnum2 == wBReg4 &&
                                                wBReg4 != DEFAULTWB)) {
                        r2 = scnReg;

                        if(isR1 == 0)
                            r1 = reg[regnum1];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                    }

                    if(iR3 != NOOP && regnum1 == wBReg3 && wBReg3 != DEFAULTWB)
                        r1 = aluResult;
                    if(iR3 != NOOP && fn1 != 8 && fn1 != 9 &&
                       (regnum2 == wBReg4 && wBReg4 != DEFAULTWB))
                        r2 = aluResult;
                    if(iR3 != NOOP && (fn1 == 8 || fn1 == 9)) { // jr and jalr
                        pc = r1;
                        jumpRecent = 1;
                    }
                }

                // if opCd4 = 35 and there is a match in iR4 and iR3 is either
                // populated with a write back that is not opcd 35 or fn 2, or
                // no write back at all
                else if(iR4 != NOOP && opCd4 == 35 &&
                        (((opCd3 != 35 && cFN3 != 2 && iR3 != NOOP &&
                        fn1 != 8 && fn1 != 9 && (((regnum1 == wBReg3) ||
                        (regnum2 == wBReg3)) && wBReg3 != DEFAULTWB)) ||
                        (opCd3 != 35 && fn3 != 2 && iR3 != NOOP &&
                        regnum1 == wBReg3 && wBReg3 != DEFAULTWB)) ||
                        !((iR3 != NOOP && fn1 != 8 && fn1 != 9 &&
                        (((regnum1 == wBReg3) || (regnum2 == wBReg3)) &&
                        wBReg3 != DEFAULTWB)) || (iR3 != NOOP &&
                                                  regnum1 == wBReg3 &&
                                                  wBReg3 != DEFAULTWB)))
                       ) {
                    // lw in iR4
                    int isR1 = 0;
                    if(regnum1 == wBReg4 && wBReg4 != DEFAULTWB) {
                        r1 = dataResult;
                        r2 = reg[regnum2];
                        cFN1 = DEFAULTCFN;
                        stall = 0;
                        isR1 = 1;
                    }
                    if(fn1 != 8 && fn1 != 9 && (regnum2 == wBReg4 &&
                                                wBReg4 != DEFAULTWB)) {
                        r2 = dataResult;

                        if(isR1 == 0)
                            r1 = reg[regnum1];

                        cFN1 = DEFAULTCFN;
                        stall = 0;
                    }

                    if(iR3 != NOOP && regnum1 == wBReg3 && wBReg3 != DEFAULTWB)
                        r1 = aluResult;
                    if(iR3 != NOOP && fn1 != 8 && fn1 != 9 &&
                       (regnum2 == wBReg4 && wBReg4 != DEFAULTWB))
                        r2 = aluResult;
                    if(iR3 != NOOP && (fn1 == 8 || fn1 == 9)) { // jr and jalr
                        pc = r1;
                        jumpRecent = 1;
                    }
                }

                // if no cases matched, STALL until other conds are true
            }

            else if(conSig1 == 1) {         // c-type
                cFN1 = idR1(iR1);           // control signal
                int regnum = idR2(iR1);
                if(cFN1 == 2)
                    wBReg1 = iR1>>16 & 31;
                else
                    wBReg1 = DEFAULTWB;

                // looking for registers not written already, scn does not need
                // to be looked up since it writes to that reg
                if(cFN1 != 2 &&
                   ((iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3) ||
                   (iR4 != NOOP && wBReg4 != 0 && regnum == wBReg4))) {
                    stall = 1;
                }
                if(stall == 0) {
                    r1 = reg[regnum]; 
                    fn1 = DEFAULTFN;
                    imm = idimm(iR1);
                }

                // go in iff ir 3 and 4 are not opcd 35 or fn 2
                else if(cFN3 != 2 && cFN4 != 2 && opCd3 != 35 && opCd4 != 35) {
                    if(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3) {
                        r1 = aluResult;
                        fn1 = DEFAULTFN;
                        imm = idimm(iR1);
                    }
                    else {
                        // has to have the intended result be in iR4 if first
                        // condition is not true
                        r1 = aluResult2;
                        fn1 = DEFAULTFN;
                        imm = idimm(iR1);
                    }
                    stall = 0;
                }

                // go in iff ir3 is not fn 2 or opcd 35 and no writeback in ir4
                else if(cFN3 != 2 && iR3 != NOOP && opCd3 != 35 &&
                        !(iR4 != NOOP && wBReg4 != 0 && regnum == wBReg4)) {
                    r1 = aluResult;
                    fn1 = DEFAULTFN;
                    imm = idimm(iR1);
                    stall = 0;
                }

                // go in iff ir4 is not fn 2 or opcd 35 and no writeback in ir3
                else if(cFN4 != 2 && iR4 != NOOP && opCd4 != 35 &&
                        !(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3)) {
                    r1 = aluResult2;
                    fn1 = DEFAULTFN;
                    imm = idimm(iR1);
                    stall = 0;
                }

                // go in iff fn4 = 2 and there is a match in iR4 and iR3 is
                // either populated with a write back that is not opcd 35 or
                // fn 2, or no write back
                else if(iR4 != NOOP && cFN4 == 2 &&
                        ((opCd3 != 35 && cFN3 != 2 &&
                        (iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3)) ||
                        !(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3))) {

                    // scn instruction result is done
                    r1 = scnReg;
                    fn1 = DEFAULTFN;
                    imm = idimm(iR1);
                    stall = 0;
                }

                // go in iff opCd4 = 35 and there is a match in iR4 and iR3 is
                // either populated with a write back that is not opcd 35 or
                // fn 2, or no write back
                else if(iR4 != NOOP && opCd4 == 35 &&
                        ((opCd3 != 35 && cFN3 != 2 &&
                        (iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3)) ||
                        !(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3))) {

                    // lw instruction result is done
                    r1 = dataResult;
                    fn1 = DEFAULTFN;
                    imm = idimm(iR1);
                    stall = 0;
                }

                // otherwise STALL
            }

            else if(conSig1 == 2) {     // j-type
                if (opCd1 == 3)
                    wBReg1 = 31;
                else
                    wBReg1 = DEFAULTWB;

                pc = iR1 & 0x03ffffff;
                jumpRecent = 1;
                fn1 = DEFAULTFN;
                cFN1 = DEFAULTCFN;
            }

            else if(conSig1 == 3) {     // i-type need modified
                int regnum = idR1(iR1);
                int regoptnum = idR2(iR1);
                if(opCd1 == 4 || opCd1 == 5 || opCd1 == 6 ||
                   opCd1 == 7 || opCd1 == 43) {
                    wBReg1 = DEFAULTWB;
                }
                else {
                    wBReg1 = iR1>>16 & 31;
                }
                
                // checking for register that were not updated already
                if((iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3) ||
                    (iR4 != NOOP && wBReg4 != 0 && regnum == wBReg4)) {
                    stall = 1;
                }
                else if((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                        ((iR3 != NOOP && wBReg3 != 0 && regoptnum == wBReg3) ||
                        (iR4 != NOOP && wBReg4 != 0 && regoptnum == wBReg4))) {
                    // b* and other special case
                    stall = 1;
                }
                if(stall == 0) {
                    r1 = reg[regnum];

                    // branches (all identical snippets apply)
                    if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43) {
                        r2 = reg[regoptnum];
                    }
                
                    imm = idimm(iR1);
                    fn1 = DEFAULTFN;
                    cFN1 = DEFAULTCFN;
                }

                // go in iff there is no fn = 2 or opCd = 35 in write backs
                else if(cFN3 != 2 && cFN4 != 2 && opCd3 != 35 && opCd4 != 35) {
                    int isR1 =0, isROpt = 0;

                    if(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3) {
                        r1 = aluResult;
                        isR1 = 1;

                        if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43) {
                            r2 = reg[regoptnum];
                        }

                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    if(isR1 == 0 && iR4 != NOOP && wBReg4 != 0 &&
                       regnum == wBReg4) {
                        r1 = aluResult2;
                        isR1 = 1;

                        if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43) {
                            r2 = reg[regoptnum];
                        }

                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    if((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                       (iR3 != NOOP && wBReg3 != 0 && regoptnum == wBReg3)) {
                        r2 = aluResult;
                        isROpt = 1;
                        if (isR1 == 0)
                            r1 = reg[regnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    if(isROpt == 0 && (opCd1 == 4 || opCd1 == 5 || opCd1 == 43)
                       && (iR4 != NOOP && wBReg4 != 0 && regoptnum == wBReg4)) {
                        r2 = aluResult2;
                        if (isR1 == 0)
                            r1 = reg[regnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }
                    stall = 0;
                }

                // go in iff iR3 is not fn 2 or opcd 35 and iR4 has no writeback
                else if(cFN3 != 2 && iR3 != NOOP && opCd3 != 35 &&
                        !((iR4 != NOOP && wBReg4 != 0 && regnum == wBReg4) ||
                        ((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                        (iR4 != NOOP && wBReg4 != 0 && regoptnum == wBReg4)))) {

                    int isR1 = 0;
                    if(wBReg3 != 0 && regnum == wBReg3) {
                        r1 = aluResult;
                        isR1 = 1;

                        if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43) {
                            r2 = reg[regoptnum];
                        }

                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    if((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                       (wBReg3 != 0 && regoptnum == wBReg3)) {
                        r2 = aluResult;
                        if (isR1 == 0)
                            r1 = reg[regnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }
                    stall = 0;
                }

                // go in iff iR4 is not fn 2 or opcd 35 and iR3 has no writeback
                else if(cFN4 != 2 && iR4 != NOOP && opCd4 != 35 &&
                        !((iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3) ||
                        ((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                        (iR3 != NOOP && wBReg3 != 0 && regoptnum == wBReg3)))) {
                    int isR1 = 0;

                    if(wBReg4 != 0 && regnum == wBReg4) {
                        r1 = aluResult;
                        isR1 = 1;

                        if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43) {
                            r2 = reg[regoptnum];
                        }

                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    if((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                       (wBReg4 != 0 && regoptnum == wBReg4)) {
                        r2 = aluResult;
                        if (isR1 == 0)
                            r1 = reg[regnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }
                    stall = 0;
                }

                // go in iff fn4 = 2 and there is a match in iR4 and iR3 is
                // either populated with a write back that is not opcd 35 or
                // fn 2, or no write back
                else if(cFN4 == 2 && iR4 != NOOP &&
                        (((cFN3 != 2 && opCd4 != 35 && iR3 != NOOP &&
                        wBReg3 != 0 && regnum == wBReg3) || (fn3 != 2 &&
                        opCd4 != 35 && (opCd1 == 4 || opCd1 == 5 ||
                        opCd1 == 43) && (iR3 != NOOP && wBReg3 != 0 &&
                        regoptnum == wBReg3))) || !((iR3 != NOOP &&
                        wBReg3 != 0 && regnum == wBReg3) || ((opCd1 == 4 ||
                        opCd1 == 5 || opCd1 == 43) && (iR3 != NOOP &&
                        wBReg3 != 0 && regoptnum == wBReg3))))) {
                    int isR1 = 0;

                    if(wBReg4 != 0 && regnum == wBReg4) {
                        r1 = scnReg;
                        isR1 = 1;

                        if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43) {
                            r2 = reg[regoptnum];
                        }

                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }
                    if((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                       (wBReg4 != 0 && regoptnum == wBReg4)) {
                        r2 = scnReg;
                        if (isR1 == 0)
                            r1 = reg[regnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    // at least one of the above would have happened
                    if(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3)
                        r1 = aluResult;
                    if(iR3 != NOOP && wBReg3 != 0 && (opCd1 == 4 ||
                       opCd1 == 5 || opCd1 == 43) && regoptnum == wBReg3)
                        r2 = aluResult;
                    stall = 0;
                }

                // go in iff fn4 = 2 and there is a match in iR4 and iR3 is
                // either populated with a write back that is not opcd 35 or
                // fn 2, or no write back
                else if(opCd4 == 35 && iR4 != NOOP && (((cFN3 != 2 &&
                        opCd4 != 35 && iR3 != NOOP && wBReg3 != 0 &&
                        regnum == wBReg3) || (fn3 != 2 && opCd4 != 35 &&
                        (opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                        (iR3 != NOOP && wBReg3 != 0 && regoptnum == wBReg3))) ||
                        !((iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3) ||
                        ((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                        (iR3 != NOOP && wBReg3 != 0 && regoptnum == wBReg3))))
                       ) {
                    int isR1 = 0;

                    if(wBReg4 != 0 && regnum == wBReg4) {
                        r1 = dataResult;
                        isR1 = 1;
                        if(opCd1 == 4 || opCd1 == 5 || opCd1 == 43)
                            r2 = reg[regoptnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    if((opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                       (wBReg4 != 0 && regoptnum == wBReg4)) {
                        r2 = dataResult;
                        if (isR1 == 0)
                            r1 = reg[regnum];
                        imm = idimm(iR1);
                        fn1 = DEFAULTFN;
                        cFN1 = DEFAULTCFN;
                    }

                    // at least one of the above would have happened
                    if(iR3 != NOOP && wBReg3 != 0 && regnum == wBReg3)
                        r1 = aluResult;
                    if(iR3 != NOOP && wBReg3 != 0 &&
                       (opCd1 == 4 || opCd1 == 5 || opCd1 == 43) &&
                       regoptnum == wBReg3)
                        r2 = aluResult;
                    stall = 0;
                }

                // ALL OTHER CASES STALL
            }        
        }

        if(stall == 1 && contEXStage == 0) {
            iR2 = NOOP;
        }
        else if(contEXStage == 0) {
            iR2 = iR1;
            nPC2 = nPC1;
            opCd2 = opCd1;
            fn2 = fn1;
            cFN2 = cFN1;
            conSig2 = conSig1;
            wBReg2 = wBReg1;
        }

        /* end of instruction decode */
        /* END OF STAGE 2*/
        
        
        /* START OF STAGE 1 OF PIPELINE */
        /* begin instruction fetch (IF) phase */

        if(stall == 0) {
            // printf("entered S1 \n");
            iR1 = storeInstruction(mem, tPC);

            // update program counter
            nPC1 = pc + 1;
            if(jumpRecent == 0) {
                pc = pc + 1;    // pc may be changed later if inst requires
                tPC = pc;
            }

            else {
                tPC = pc;
                iR1 = NOOP;

                // since jump has happened, automatically assigned a noop
                // because next instruction is now irrelevant

                // in reality, this would happen after the cpu calculated that
                // there will be a jump which happens at the same time as
                // everything else marking the noop at end of cycle

                jumpRecent = 0; 
            }
        }

        else {
            // stalling, so do not increase pc counter or fetch instruction since
            // it would overwrite the iR1
            stall = 0;
        }
        /* end of instruction fetch phase*/
        /* END OF STAGE 1*/
       
        // wait for user input to continue processing 
        fgets(line, sizeof(line), stdin);
    }
 
    // end (finally)
    return 0;
}    
