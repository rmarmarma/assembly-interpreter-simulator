# assembly-interpreter-simulator

This project is a programming assignment from the Introduction to Computer Systems course taught at Trinity College
in Hartford Connecticut. The purpose of the assignment is to create a program that will simulate a machine that will
accept instructions written in the assembly language. 

### Project Description:
The SM-275 is a new machine that is in the design phase right now. Your assignment is to write
a simulator for the machine, which will interpret instructions to test its design. The simulator
will be written in C, and it should accept instructions in the assembly language of the SM-275,
SMA. All instructions and operands are to be case-insensitive. The first operand of all two-operand 
instructions must be followed by a comma. Rather than detailed messages, the interpreter can 
just complain of an invalid instruction with “???”

The instruction set is as follows:

- READ data, Mk. Input data is stored at Mk. OF set if data out of range.
- WRITE Rk|Mk. Value stored at register or memory location is output.
- PRINTS. Print the current state of the machine (see sample output below).
- MOVE Rj|Mj, Rk|Mk. Value stored at first operand copied to second, except 
both cannot be memory locations. Example: MOVE M2, R1
- ADD, SUB, MULT, DIV, MOD. These are all two-operand instructions. 
Each operand can be either a register or a memory location, except both cannot 
be memory locations. The result is always stored in R0. The order of operands 
for subtraction is “subtract arg1 from arg2”. The order of both division 
operations is “arg1 div/mod arg2”. Examples:
- ADD R2, M1
- MOD M3, R1
- COMP Rj,Rk. sets flags according the table below. (This instruction is only 
required for the third program machine.c.)
- QUIT. Quit the simulator.

#### script.c

This program should be a revision of interp.c that reads a sequence of instructions from a file 
and performs them just as the interp.c would do rather than reading the instructions from the 
command-line.
