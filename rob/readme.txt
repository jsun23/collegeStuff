Assembler project

------
Compilation and execution instructions

First compile the assembler:
    gcc -Wall -g -o assembler assembler.c assembler_m.c assembler_labels.c

The output file "assembler" will be able to take in an assembly code file and
output a bytecode file. Output the bytecode file to "code.h" as it is used in
the following program for execution:
    ./assembler [input-assembly-file] code.h

The input-assembly-file is any file containing hopefully valid assembler code.
Some samples are included.

Next compile the final program:
    gcc -Wall -g -o exec_asm exec_asm.c

This will compile "exec_asm.c" with the appropriate bytecode file "code.h" into
an executable "exec_asm", which can be run with:
    ./exec_asm

If assembly code is valid and complete, this should run without errors. If there
are errors in compilation, it is most likely due to a problem in the assembly
code file.

When running exec_asm, each instruction that is parsed will require user input
to advance to next instruction (done by hitting Enter).


------
Some information

Assembly code file format:
    operation operand1 [operand2 ...]

- Registers are labeled as $0 to $31.
- Immediate values are decimal numbers.
- Labels are prefixed with ":" (for example: :label). These are used in branching
and jumping.
- Addresses are denoted by labels.
- Comments are prefixed by "#".

See sample input files for examples on how the assembly code should look.


The assembler supports the following instruction types:
        opcode
R-type  000000 *        (the opcode for all R-type instructions is 000000,
                         but the following codes apply to the func part of the
                         bytecode)
        001000 jr
        001001 jalr
        011000 mult
        011001 multu
        011010 div
        011100 divu
        100000 add
        100001 addu
        100010 sub
        100011 subu
        100100 and
        100101 or
        100110 xor
        100111 nor

I-type
        000100 beq
        000101 bne
        000110 blez
        000111 bgtz
        001000 addi
        001001 addiu
        001100 andi
        001101 ori
        001110 xori
        001111 lui
        100011 lw
        101011 sw

J-type
        000010 j
        000011 jal


The bytecode is broken up into the following 32bit sequence for each
instruction type:
                6b      5b     5b     5b     5b     6b     
bit length:    [______][_____][_____][_____][_____][______]
R-type:        [opcode][ rs  ][ rt  ][ rd   [ sh  ][ func ]
I-type:        [opcode][ rs  ][ rd  ][      immediate     ]
J-type:        [opcode][              address             ]
C-type:        [opcode][ Cfn ][ rd  ][      immediate     ]


Additionally, there is an instruction called "int," used to store word-sized
integers in sequential order. The syntax for it is usually as follows:
    :data
        int     1   2   3  6  9
        int     34  12  76 22 12


------
Output information

The output only displays outputs for the robot instructions (C-type), so
it can display:

    Output line    Response       Info
    M    <rate>    none           movement speed set to <rate> inches/second
    R    <rate>    none           rotation speed set to <rate> degree/second
    S              dist           scan in current direction, dist will be
                                  the distane of nearby objects in feet,
                                  negative distance if object is a wall or
                                  dead robot
    F    <dist>    none           fire in the current direction at point <dist>
                                  feet away, if dist = 0 kills your own robot
    N              none           not a robot command (or noop)


-------
Implementation notes

The control signals in exec_asm.c are shorthand form for the decompostion
of the instruction so that control signals don't need to take extra registers.

Order of implementation of stages of the pipeline is as follows in exec_asm.c:
    Write Back                 (WB)
    Data Memory/Robot Control  (DM)
    Execution                  (EX)
    Instruction Decode         (ID)
    Instrcution Fetch          (IF)
In practice though, the pipeline is executed from IF -> WB (in reverse order).

Pipeline registers are implement as variables which can be passed between
cycles.

ALU mult/div instructions are implemented ouside of the ALU function to simplify
the code in the multicycle pipeline. Since those functions are often accessed
outside of solely the ALU, it was more convenient to place them in the main
loop.

Also includes forwarding. We can forward results from the ID stage to the ID
stage of the next cycle. There is no DM -> DM forwarding because such forwarding
only has a use in the case of SW (store word) appearding after an LW (load word)
or SCN (scan) instruction, which would rarely ever happen in our test cases.

If there is some improper instruction in the assembly code, the exec_asm will
quit. There is no error checking (because that would only increase complexity)
at all, so the input assembly file should be correct.
