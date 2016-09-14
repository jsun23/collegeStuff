Create your project here.

Replace this file with a description of the state of your project at
each deadline.
===============================================================================
Project Phase1:
Due 9/30/2015
To run project run the following commands (outputFile should be code.h):
	$ make
	$ ./toOpCode input_file output_file
	$ make clean
	$ ./Main
Once running the user must press enter to simulate once clock cycle of the processor.

Known Errors:
	-Debugging prints to STD out (fixed)
	-For an unknown reason if a list of MIPS instructions is given to toOpCode and it contains C-type
	instructions, it may print out the final opcode instruction twice (I think it is an issue with newlines chars at the end of MIPS files)
	this happened once before and I can't get it to repeat, but I don't recal fixing it

	-Parsing issues with parsing rd from commands our interpreter for non-robot opcodes:
		-Negative numbers such as homework 1's 0x2021fffc, ( addi $1 $1 #-4   ; i-type op=0x08, rd=1, rs=1, imm=-4) 
		are not handled and may cause a segfault in following lines as the number is read in as 65532

	-Ignore main.c it is not used
=============================================================================


