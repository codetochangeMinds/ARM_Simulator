## Problem Statement
There is a need to visualize what is going at lower layer of abstraction when we execute the high level or low level program on a Von Neuman machine. The projects aims to build a ARM language simulator to visualize the execution of ARM language(low level) instructions. As in case of advanced processors the concept of pipelining are used, the simulator should be able to visualize the execution of instructions using pipelining concept. The simulator should simulate the recursive function, if statements, for loops statement etc.

## Abstract of the Development Phase
We developed the project using c++ and the concept of pipelining. Instruction are read from a file along with the latency of the instructions. The simulator was able to visualize the execution of the instruction and displayed on the terminal.

## Command to Run Program
1. Open Terminal and cd Src_Code
2. g++ -std=c++11 armSim.cpp -o processor_simulator
3. ./processor_simulator
*input to simulator is given through latency.txt and in.txt*


## Assumption
1. Cmp and Branch(bge and bne) are considered to be one instruction.
2. Pseudo Memory is of size 5000,label is assigned memory according to .data section.
3. Input is taken from in.txt while latency data is taken from latency.txt 

## GUI
1. Diffrent color are used for every pipeline stage.
2. Instruction in particular stage is shown just below it in white color.
3. If there is no instruction in particular stage then there will be nothing written below it.
4. When instruction is flushed then it is shown by printing **flush** in that stage.
5. Whereas when we need stall to remove hazard **stall** will be written below that stage.

## Instruction Set
1. Add rd,rop1,rop2
2. Add rd,rop1,#Imm
3. Add SP,SP,#Imm
4. Sub rd,rop1,rop2
5. Sub rd,rop1,#Imm
6. Sub SP,SP,#Imm
7. Mul rd,rop1,rop2
8. Mul rd,rop1,#Imm
9. Mov rd,rop1
10. Mov pc, lr
11. Mov rd,#Imm
12. Ldr rd,[rop1,#Imm]
13. Ldr rd,[rop1]
14. Ldr rd,=label
15. Ldr LR,[SP,#Imm]
16. Ldr rd,[SP,#Imm]
17. Str rd,[rop1,#Imm]
18. Str rd,[rop1]
19. Str Lr,[SP,#Imm]
20. Str rd,[SP,#Imm]
21. cmp rop1,rop2 bge label
22. cmp rop1,rop2 bne label
23. Bl procedurelabel
24. B label
25. Exit
