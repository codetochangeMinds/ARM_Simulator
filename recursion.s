.equ SWI_Exit,  0x11
main:
MOV r0,#6;
BL fact 
B Exit
fact:
SUB r13,r13,#8;
STR r14,[r13,#4];
STR r0,[r13,#0];
CMP r0,#1
BGE L1
MOV r0,#1;
ADD r13,r13,#8;
MOV pc,r14;
L1: SUB r0,r0,#1;
BL fact
MOV r12,r0;
LDR r0,[r13,#0];
LDR LR,[r13,#4];
ADD r13,r13,#8;
Mov r1,r0;
MUL r0,r1,r12;
MOV pc,r14;
Exit:
swi SWI_Exit
