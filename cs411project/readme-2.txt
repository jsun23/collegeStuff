===============================================================================
Project Phase 2:
Due 10/28/2015

Data-path Diagram Notes:
-The decode block is treated as an n level mux as specified and since it only has 1 input the delay is 2
-The diagram follow the general idea of the MIPS multi cycle instruction set but allows for multi-cycle writes by allowing the initial address pointer in memory to be either the instruction pointer or the memory pointer.
 In this way, memory operations can span multiple cycles/ 

RTL Notes:
-The RTL we have does not specifiy the state or number of cycles required for the operation. Only the operations which require control signals are mentioned and those operations may may take more than one cycle.
	For example the robot operations will take may cycles, yet the control signals do not need to be updated to contuniue the operation, so the RTL only has the initial values needed
-It is assumed that the Robot Unit has seperate logic to handle its own commands and that the opcode of teh instruction would provde taht information to the Robot Unit, and thus is not shown in the RTL  	
