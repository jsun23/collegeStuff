FILE=testMIPS.txt

compile: toOpCode.out Main.out

toOpCode: Assembler.o FileParser.o Instr.o toOpCode.o
	g++ -Wall -std=c++0x Assembler.o FileParser.o Instr.o toOpCode.o -o "toOpCode"

Main.out: Assembler.o FileParser.o Instr.o Interpreter.o States.o  main.o
	g++ -Wall -std=c++0x Assembler.o FileParser.o Instr.o Interpreter.o States.o  main.o -o "Main.out"

toOpCode.o: toOpCode.cpp
	g++ -Wall -c -std=c++0x  toOpCode.cpp

main.o: main.cpp FileParser.h Assembler.h Interpretation.h Interpreter.h States.h code.h
	g++ -Wall -c -std=c++0x  main.cpp

States.o: States.cpp Interpretation.h Interpreter.h
	g++ -Wall -c -std=c++0x States.cpp

Interpreter.o: Interpreter.cpp Interpreter.h Interpretation.h
	g++ -Wall -c -std=c++0x Interpreter.cpp		

FileParser.o: FileParser.cpp FileParser.h Instr.h
	g++ -Wall -c -std=c++0x FileParser.cpp

Assembler.o: Assembler.cpp Assembler.h Instr.h
	g++ -Wall -c -std=c++0x  Assembler.cpp

Instr.o: Instr.cpp Instr.h
	g++ -Wall -c -std=c++0x Instr.cpp

code.h: toOpCode $(FILE)
	./toOpCode $(FILE) code.h

clean:
	rm -rf *.o
	rm -f nasm
	rm -f toOpCode
	rm -f Main.out
	rm -f *~ *.h.gch *#
