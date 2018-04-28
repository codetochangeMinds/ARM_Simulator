#include <iostream>
#include<bits/stdc++.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
using namespace std;


ifstream fin;
vector<string> lexeme;
int prog=0;
int mem[6000];
int freemem = 5000;
struct loop
{
	int loop_no;
	string loop_name;
};
struct loop1
{
    int loop_no;
    string loop_name;
    int start;
};
struct symb 		//change
{
	string name;
	int pos;
	int type = 0;
};

vector<symb> symbol_table;
vector<symb> temp_symb;

struct Instruction 		//change
{
	int opcode = -11;
	int source = -11;
	int operand1 = -11;
	int operand2 = -11;
	int type = -11;
};

int shut_down = 0;

vector<Instruction> instruction_file;		//change
vector<loop> loops;		//change
vector<loop1> data;
string exit_name = "Exit";
int inst_size = 0;
int r[16];
int end_file_inst = 0;


void make_instruction_file()
{
	while(prog < lexeme.size())
    {
        cout<<prog<<endl;
        if(lexeme[prog]=="Add"||lexeme[prog]=="add"||lexeme[prog]=="ADD"||lexeme[prog]=="Sub"||lexeme[prog]=="sub"||lexeme[prog]=="SUB"||lexeme[prog]=="Mul"||lexeme[prog]=="mul"||lexeme[prog]=="MUL"||lexeme[prog]=="Mov"||lexeme[prog]=="mov"||lexeme[prog]=="MOV"||lexeme[prog]=="Ldr"||lexeme[prog]=="ldr"||lexeme[prog]=="LDR"||lexeme[prog]=="Str"||lexeme[prog]=="str"||lexeme[prog]=="STR")
		{
            
            int p1 = prog;
            int p=1;//execute(prog);
            prog = p1;
            if(p==-1)
            {
            	cout<<"Error in "<<lexeme[prog]<<" instruction"<<endl;
            }
            else
            {
            	
            	if(lexeme[prog]=="Add"||lexeme[prog]=="add"||lexeme[prog]=="ADD")		//Addition
            	{
            		Instruction temp_i;
            		temp_i.opcode = 1;
            		temp_i.source = stoi(&lexeme[prog+1][1]);
            		temp_i.operand1 = stoi(&lexeme[prog+3][1]);
            		//Add rd,rop1,rop2
            		if(lexeme[prog+5][0]=='r')
            		{
            			temp_i.operand2 = stoi(&lexeme[prog+5][1]);
            			temp_i.type = 1;
            		}
            		//Add rd rop1,#Imm
            		else
            		{	
						temp_i.operand2 = stoi(&lexeme[prog+5][1]);
						temp_i.type = 2;
            		}
            		instruction_file.push_back(temp_i);
            		prog+=6;
            	}
            	else if(lexeme[prog]=="Sub"||lexeme[prog]=="sub"||lexeme[prog]=="SUB")		//Subtract
            	{
            		Instruction temp_i;
            		temp_i.opcode = 2;
            		temp_i.source = stoi(&lexeme[prog+1][1]);
            		temp_i.operand1 = stoi(&lexeme[prog+3][1]);
            		//Sub rd,rop1,rop2
            		if(lexeme[prog+5][0]=='r')
            		{
            			temp_i.operand2 = stoi(&lexeme[prog+5][1]);
            			temp_i.type = 1;
            		}
            		//Sub rd,rop1,#Imm
            		else
            		{	
						temp_i.operand2 = stoi(&lexeme[prog+5][1]);
						temp_i.type = 2;
            		}
            		instruction_file.push_back(temp_i);
            		prog+=6;
            	}
            	else if(lexeme[prog]=="Mul"||lexeme[prog]=="mul"||lexeme[prog]=="MUL")		//Multiply
            	{
            		Instruction temp_i;
            		temp_i.opcode = 3;
            		temp_i.source = stoi(&lexeme[prog+1][1]);
            		temp_i.operand1 = stoi(&lexeme[prog+3][1]);
            		//Mul rd,rop1,rop2
            		if(lexeme[prog+5][0]=='r')
            		{
            			temp_i.operand2 = stoi(&lexeme[prog+5][1]);
            			temp_i.type = 1;
            		}
            		//Mul rd, rop1,#Imm
            		else
            		{	
						temp_i.operand2 = stoi(&lexeme[prog+5][1]);
						temp_i.type = 2;
            		}
            		instruction_file.push_back(temp_i);
            		prog+=6;
            	}
            	else if(lexeme[prog]=="Mov"||lexeme[prog]=="mov"||lexeme[prog]=="MOV")		//Move
            	{
            		Instruction temp_i;
            		
            		temp_i.opcode = 4;
            		temp_i.source = stoi(&lexeme[prog+1][1]);
            		temp_i.operand2 = -1;
            		if(lexeme[prog+3][0]=='r')	//Mov rd rop1
            		{
            			temp_i.operand1 = stoi(&lexeme[prog+3][1]);
            			temp_i.type = 1;
            		}
            		else//Mov rd #12
            		{	
						temp_i.operand1 = stoi(&lexeme[prog+3][1]);
						temp_i.type = 2;
            		}
            		instruction_file.push_back(temp_i);
            		prog+=4;
            		
            	}
            	else if(lexeme[prog]=="Ldr"||lexeme[prog]=="ldr"||lexeme[prog]=="LDR")			//Load
            	{
            		cout<<"ramlal \n";
            		Instruction temp_i;
            		temp_i.opcode = 5;
            		temp_i.source = stoi(&lexeme[prog+1][1]);
            		if(lexeme[prog+3][0]=='[')		//Ldr rd, [rop1]
            		{
            			if(lexeme[prog+5][0] == ']')
	            		{	temp_i.operand1 = stoi(&lexeme[prog+4][1]);
	            			temp_i.operand2 = -1;
	            			temp_i.type = 1;
	            			prog+=6;
            			}
            			else
            			{
            				temp_i.operand1 = stoi(&lexeme[prog+4][1]);
							temp_i.operand2 = stoi(&lexeme[prog+6][1]);
							temp_i.type = 2;
            				prog+=8;
            			}
            		}
            		else if (lexeme[prog+3][0] == '=')		//Ldr rd, =AA
            		{
            			temp_i.operand1 = -2;
	            		symb tem;										//change
	            		tem.name = lexeme[prog + 3].substr(1);
	            		tem.pos = instruction_file.size();
	            		tem.type = 1;
						temp_symb.push_back(tem);
						temp_i.operand2 = -1;
						temp_i.type = 3;
            			prog+=4;													//change
            		}
            		instruction_file.push_back(temp_i);
            	}
            	else		//Store
            	{
            		Instruction temp_i;
            		temp_i.opcode = 6;
            		temp_i.source = stoi(&lexeme[prog+1][1]);
            		if(lexeme[prog+4][0]=='r' && lexeme[prog+5][0] == ']')		//Str rd, [rop1]
            		{
            			temp_i.operand1 = stoi(&lexeme[prog+4][1]);
            			temp_i.operand2 = -1;
            			temp_i.type = 1;
            			prog+=6;
            		}
            		else		//Str rd, [rop1, #21]
            		{	
						temp_i.operand1 = stoi(&lexeme[prog+4][1]);
						temp_i.operand2 = stoi(&lexeme[prog+6][1]);
						temp_i.type = 2;
            			prog+=8;
            		}
            		instruction_file.push_back(temp_i);
            	}
            }
        }
    	else if(lexeme[prog]=="Cmp"||lexeme[prog]=="cmp" ||lexeme[prog]=="CMP")			//compare
    	{
            int q1 =prog;
            int q=1;//compare(prog);
            prog = q1;
            if(q==-1)
            {
            	cout<<"Error in cmp instruction"<<endl;
            }
            else if(lexeme[prog+4] == "Bne" ||lexeme[prog+4] == "bne" ||lexeme[prog+4]=="BNE")		//cmp and bne
    		{
    				Instruction temp_i;
    				temp_i.opcode = 7;
            		temp_i.source = -2;								//change
            		symb tem;									//change
            		tem.name = lexeme[prog + 5];
            		tem.pos = instruction_file.size();
            		temp_symb.push_back(tem);
            		if(lexeme[prog+1][0]=='r' && lexeme[prog+3][0] == 'r')			//cmp rd, rop
            		{
            			temp_i.operand1 = stoi(&lexeme[prog+1][1]);									//change
            			temp_i.operand2 = stoi(&lexeme[prog+3][1]);									//change
            			temp_i.type = 1;
            			prog+=6;
            		}
            		else if (lexeme[prog+1][0]=='r' && lexeme[prog+3][0] == '#')		//cmp rd, #5
            		{	
						temp_i.operand1 = stoi(&lexeme[prog+1][1]);									//change
						temp_i.operand2 = stoi(&lexeme[prog+3][1]);									//change
						temp_i.type = 2;
            			prog+=6;
            		}
            		instruction_file.push_back(temp_i);
    		}
    		else if(lexeme[prog+4] == "Bge"||lexeme[prog+4] == "bge" ||lexeme[prog+4] == "BGE")			//cmp and bge
    		{
    				Instruction temp_i;
    				temp_i.opcode = 8;
            		temp_i.source = -2;																//change
            		symb tem;																		//change
            		tem.name = lexeme[prog + 5];
            		tem.pos = instruction_file.size();
            		temp_symb.push_back(tem);
            		if(lexeme[prog+1][0]=='r' && lexeme[prog+3][0] == 'r')			//cmp rd, rop
            		{
            			temp_i.operand1 = stoi(&lexeme[prog+1][1]);									//change
            			temp_i.operand2 = stoi(&lexeme[prog+3][1]);
            			temp_i.type = 1;
            			prog+=6;
            		}
            		else if (lexeme[prog+1][0]=='r' && lexeme[prog+3][0] == '#')		//cmp rd, rop
            		{	
						temp_i.operand1 = stoi(&lexeme[prog+1][1]);									//change
						temp_i.operand2 = stoi(&lexeme[prog+3][1]);
						temp_i.type = 2;
            			prog+=6;
            		}
    				instruction_file.push_back(temp_i);
    		}
    		else if(lexeme[prog+4] == "Bl"||lexeme[prog+4] == "bl" ||lexeme[prog+4] == "BL")			//cmp and bge
    		{
    				Instruction temp_i;
    				temp_i.opcode = 9;
            		temp_i.source = -2;
            		symb tem;																		//change
            		tem.name = lexeme[prog + 5];
            		tem.pos = instruction_file.size();
            		temp_symb.push_back(tem);
            		if(lexeme[prog+1][0]=='r' && lexeme[prog+3][0] == 'r')			//cmp rd, rop
            		{
            			temp_i.operand1 = stoi(&lexeme[prog+1][1]);
            			temp_i.operand2 = stoi(&lexeme[prog+3][1]);
            			temp_i.type = 1;
            			prog+=6;
            		}
            		else if (lexeme[prog+1][0]=='r' && lexeme[prog+3][0] == '#')		//cmp rd, rop
            		{	
						temp_i.operand1 = stoi(&lexeme[prog+1][1]);
            			temp_i.operand2 = stoi(&lexeme[prog+3][1]);
						temp_i.type = 2;
            			prog+=6;
            		}
    				instruction_file.push_back(temp_i);
    		}
    	}
    	else if (lexeme[prog] == "B" || lexeme[prog] == "b")		//branch
    	{
    				Instruction temp_i;
    				temp_i.opcode = 10;
            		temp_i.source = -2;
        			temp_i.operand1 = -1;
        			temp_i.operand2 = -1;
        			temp_i.type = 1;
               		symb tem;																	//change
            		tem.name = lexeme[prog + 1];
            		tem.pos = instruction_file.size();
            		temp_symb.push_back(tem);
        			prog+=2;
    				instruction_file.push_back(temp_i);
    	}
    	else if(lexeme[prog] == ":")
    	{
    		symb tem;
    		tem.name = lexeme[prog-1];
    		if(lexeme[prog+1] == ".space")
    		{	
    			tem.pos = freemem;
    			freemem = freemem + stoi(lexeme[prog+2]);
    			tem.type = 2;
    		}
    		else
    		{
    			tem.pos = instruction_file.size();
    		}
    		symbol_table.push_back(tem);
    		prog++;
    	}
    	else if(lexeme[prog] == "Exit" || lexeme[prog] == "exit" || lexeme[prog] == "EXIT")
    	{
    		Instruction temp_i;
			temp_i.opcode = 11;
    		temp_i.source = -1;
			temp_i.operand1 = -1;
			temp_i.operand2 = -1;
			temp_i.type = -1;
			instruction_file.push_back(temp_i);
       		//symb tem;
       		prog++;
    	}
        else prog++;
    }
}


void flush();

int PCSrc = 0;

struct IF_ID
{
	Instruction recent_instruction ;
	int prog_cnt = -1;
};

struct ID_EX
{
	int src;
	int r1;
	int r2;
	int address;
	int offset;
	int prog_cnt;
	//Controll
	int opcode = -1;
	int type;
};

struct EX_MEM
{
	int val_arith;
	int val_address;
	int src;
	bool zero;
	int prog_cnt;
	//Controll
	int opcode = -1;
	int type;
};

struct MEM_WB
{
	int write_data;
	int src;
	//Controll
	int opcode = -1;
	int type;
};

IF_ID Register_IF_ID;
ID_EX Register_ID_EX;
EX_MEM Register_EX_MEM;
MEM_WB Register_MEM_WB;

int termin;
void IF()
{
	if(PCSrc = 0)
	{	prog++;
		if(prog >= instruction_file.size())
		{
			Instruction end_file;
			end_file.opcode = 12;
			end_file.source = -1;
			end_file.operand1 = -1;
			end_file.operand2 = -1;
			end_file.type = -1;
			Register_IF_ID.recent_instruction = end_file;
			Register_IF_ID.prog_cnt = prog;
		}
		else
		{
			Register_IF_ID.recent_instruction = instruction_file[prog];
			Register_IF_ID.prog_cnt = prog;
		}
	}
	else
	{
		flush();
		PCSrc = 0;
		IF();
	}

}

void ID()
{
	Register_ID_EX.prog_cnt = Register_IF_ID.prog_cnt;
	if(Register_IF_ID.recent_instruction.opcode <=3 && Register_IF_ID.recent_instruction.type == 1 && Register_IF_ID.recent_instruction.opcode > 0)
	{
		Register_ID_EX.src = Register_IF_ID.recent_instruction.source;
		if(Register_IF_ID.recent_instruction.type == 1)
		{	
			Register_ID_EX.r1 = r[Register_IF_ID.recent_instruction.operand1];
			Register_ID_EX.r2 = r[Register_IF_ID.recent_instruction.operand2];
		}
		else if(Register_IF_ID.recent_instruction.type == 2)
		{	
			Register_ID_EX.r1 = r[Register_IF_ID.recent_instruction.operand1];
			Register_ID_EX.r2 = Register_IF_ID.recent_instruction.operand2;	
		}
	}
	else if(Register_IF_ID.recent_instruction.opcode == 4)
	{	
		Register_ID_EX.src = Register_IF_ID.recent_instruction.source;
		if(Register_IF_ID.recent_instruction.type == 1)
		{
			Register_ID_EX.r1 = r[Register_IF_ID.recent_instruction.operand1];
		}
		else 
		{
			Register_ID_EX.r1 = Register_IF_ID.recent_instruction.operand1;
		}
	}
	else if(Register_IF_ID.recent_instruction.opcode == 5 || Register_IF_ID.recent_instruction.opcode == 6)
	{
		Register_ID_EX.src = Register_IF_ID.recent_instruction.source;
		if(Register_IF_ID.recent_instruction.type == 1)
		{
			Register_ID_EX.address = Register_IF_ID.recent_instruction.operand1;
		}
		else if(Register_IF_ID.recent_instruction.type == 2)
		{
			Register_ID_EX.address = Register_IF_ID.recent_instruction.operand1;
			Register_ID_EX.offset = Register_IF_ID.recent_instruction.operand2;
		}
		else
		{
			Register_ID_EX.address == -2;
		}
	}
	else if(Register_IF_ID.recent_instruction.opcode > 6 && Register_IF_ID.recent_instruction.opcode < 10 )
	{
		if(Register_IF_ID.recent_instruction.type == 1)
		{
			Register_ID_EX.r1 = r[Register_IF_ID.recent_instruction.operand1];
			Register_ID_EX.r2 = r[Register_IF_ID.recent_instruction.operand2];	
		}
		else
		{
			Register_ID_EX.r1 = r[Register_IF_ID.recent_instruction.operand1];
			Register_ID_EX.r2 = Register_IF_ID.recent_instruction.operand2;	
		}
		Register_ID_EX.address == Register_IF_ID.recent_instruction.source;
	}
	else if(Register_IF_ID.recent_instruction.opcode == 10)
	{
		Register_ID_EX.address = Register_IF_ID.recent_instruction.source;
	}
	Register_ID_EX.opcode = Register_IF_ID.recent_instruction.opcode;
	Register_ID_EX.type = Register_IF_ID.recent_instruction.type;

}

void EX()
{
	Register_EX_MEM.prog_cnt = Register_ID_EX.prog_cnt;
	if( Register_ID_EX.opcode <10 && Register_ID_EX.opcode > 0)
	{	
		Register_EX_MEM.src = Register_ID_EX.src;
		if(Register_ID_EX.opcode == 1)
		{
			Register_EX_MEM.val_arith = Register_ID_EX.r1 + Register_ID_EX.r2;
		}
		else if(Register_ID_EX.opcode == 2)
		{
			Register_EX_MEM.val_arith = Register_ID_EX.r1 - Register_ID_EX.r2;	
		}
		else if(Register_ID_EX.opcode == 3)
		{
			Register_EX_MEM.val_arith = Register_ID_EX.r1 * Register_ID_EX.r2;	
		}
		else if(Register_ID_EX.opcode == 4)
		{
			Register_EX_MEM.val_arith = Register_ID_EX.r1;
		}
		else if(Register_ID_EX.opcode == 5 || Register_ID_EX.opcode == 6)
		{
			if (Register_ID_EX.type == 1)
			{
				Register_EX_MEM.val_address = Register_ID_EX.address;
			}
			else if (Register_ID_EX.type == 2)
			{
				Register_EX_MEM.val_address = Register_ID_EX.address + Register_ID_EX.offset;
			}
			else
			{
				Register_EX_MEM.val_address = Register_ID_EX.address;
			}
		}
		else
		{
			if((Register_ID_EX.r1 - Register_ID_EX.r2) == 0)
				Register_EX_MEM.zero = 1;
			else
				Register_EX_MEM.zero = 0;
		}
	}
	else  if (Register_ID_EX.opcode == 10)
	{
		Register_EX_MEM.val_address = Register_ID_EX.address;
	}
	Register_EX_MEM.opcode = Register_ID_EX.opcode;
	Register_EX_MEM.type = Register_ID_EX.type;
}

void MEM()
{
	if(Register_EX_MEM.opcode < 5 && Register_EX_MEM.opcode > 0)
	{
		Register_MEM_WB.write_data = Register_EX_MEM.val_arith;
		Register_MEM_WB.src = Register_EX_MEM.src;
	}
	else if(Register_EX_MEM.opcode == 5)
	{
		Register_MEM_WB.write_data = mem[(Register_EX_MEM.val_address)/4];
		Register_MEM_WB.src = Register_EX_MEM.src;
	}
	else if(Register_EX_MEM.opcode == 6)
	{
		mem[(Register_EX_MEM.val_address)/4] = Register_EX_MEM.src;
	}

	if(Register_EX_MEM.opcode > 6 && Register_EX_MEM.opcode < 10 && Register_EX_MEM.zero == 1)
	{
		PCSrc = 1;
	}
	Register_MEM_WB.opcode = Register_EX_MEM.opcode;
	Register_MEM_WB.type = Register_EX_MEM.type;
}

void WB()
{
	if(Register_MEM_WB.opcode <= 5 && Register_MEM_WB.opcode > 0)
	{
		r[Register_MEM_WB.src] = Register_MEM_WB.write_data;
	}
	else if (Register_MEM_WB.opcode == 11)
	{
		shut_down = 1;
	}
	else if(Register_MEM_WB.opcode == 12)
	{
		end_file_inst = 1;
	}
}

void flush()
{
	prog = Register_EX_MEM.val_address;
	Register_ID_EX.opcode = -1;
	Register_ID_EX.type = -1;
	Register_EX_MEM.opcode = -1;
	Register_EX_MEM.type = -1;
}


int main()
{

	char s;
    char *t;
    int capacity = 10;
    t = new char[capacity];
    int ssize = 0;
    int k =1;
    vector<string> temps;
    //int k =1;
    int sum = 0;
    int pmax=0;
    bool comment = 0 ;
    bool loop_or_data = 0;
	fin.open("in.txt");
	while (!fin.eof())
    {
            fin.get(s);
            {
                if (int(s)==64)
                {
                    if(comment == 0)
                        comment = 1;
                }
                else
                if (int(s)==10 && comment == 1)
                {
                    comment= 0;
                }

                if(comment == 0)
                {
                if(!(s<123&&int(s)>96||int(s)==39||int(s)>64&&int(s)<91||int(s)==46||int(s)==95||int(s)>47&&int(s)<58||int(s)>39&&int(s)<43||int(s)==35||int(s)==61))
                {
                    if(int(s) == 44 || int(s) == 58|| int(s) == 59|| int(s)==91 || int(s)==93)
                    { 
						if(ssize>=2)
	                    {
	                        t[ssize]='\0';
	                        lexeme.push_back(t);
	                        
	                		
	                        if(int(s) == 44)
	                        lexeme.push_back(",");
	                    	else if(int(s) == 58)
	                        {
	                        	
	                        	if(loop_or_data == 0)
	                            {
	                            	loop temp;
	                            	temp.loop_name =  lexeme[lexeme.size()-1];
		                            temp.loop_no = lexeme.size()-1;
		                        	loops.push_back(temp);
		                        }
	                        	else
	                        	{  
	                        		loop1 temp;
	                                temp.loop_name =  lexeme[lexeme.size()-1];
	                                temp.loop_no = lexeme.size()-1;
	                                temp.start = 0;
	                                data.push_back(temp);
	                                
	                            } 
	                        	lexeme.push_back(":");
	                        }
	                    	else if(int(s) == 59)
	                        lexeme.push_back(";");
	                        else if(int(s) == 91)
	                        lexeme.push_back("[");
	                        else if(int(s) == 93)
	                        lexeme.push_back("]");

	                    } 
	                    else
	                    {	
	                        if(int(s) == 44)
	                        lexeme.push_back(",");
	                    	if(int(s) == 58)
	                        {
	                        	loop temp;
	                        	temp.loop_name =  lexeme[lexeme.size()-1];
	                        	temp.loop_no = lexeme.size()-1;
	                        	if(loop_or_data == 0)
	                        	loops.push_back(temp);
	                        	else
	                        	{  
	                        		loop1 temp;
	                                temp.loop_name =  lexeme[lexeme.size()-1];
	                                temp.loop_no = lexeme.size()-1;
	                                temp.start = -1;
	                                data.push_back(temp);
	                                
	                            } 

	                        	lexeme.push_back(":");
	                        }
	                    	if(int(s) == 59)
	                        lexeme.push_back(";");	
	                        else if(int(s) == 91)
	                        lexeme.push_back("[");
	                        else if(int(s) == 93)
	                        lexeme.push_back("]");
	                    }
	                }
	                	else
		                {	
		                	t[ssize]='\0';
		                    if(ssize>=1)
		                    {
		                        lexeme.push_back(t);

		                    }
							if(lexeme.size()>0)
		   					{
		                        if( lexeme[lexeme.size() - 1] == ".data")
		                            {//cout<<"DATA"<<endl;
		                            loop_or_data = 1;}
			                    else
			                    if(lexeme[lexeme.size() - 1] == ".text")
			                            {loop_or_data = 0;}
			                               // cout<<"TEXT"<<endl;}
			                    else if(lexeme[lexeme.size()-1]=="0x11")
		                    	exit_name = lexeme[lexeme.size()-3];
		                    }
					
                    }
                    sum = 0;
                    ssize= 0;
                    capacity=10;
                    t=new char [capacity];
                }

                else
                    {   
                        if(ssize<capacity)
	                    {    
	                    	t[ssize]=s;
	                        ssize++;
	                    }
	                    else
	                    {   
	                    	char*temp = t;
		                    t = new char[capacity*2];
		                    capacity = 2*capacity;
		                    for(int i=0; i<ssize;i++)
		                        t[i] = temp[i];
		                    t[ssize] = s;
		                    ssize++;
		                    delete []temp;
	                    }
                    }
                }
                }
    }
    fin.close();
    for (int i = 0; i < lexeme.size(); ++i)
    {
    	cout<<lexeme[i]<<"   "<<i<<endl;
    }

    //driver statement
make_instruction_file();
    
    for (int i = 0; i < instruction_file.size(); i++)
    {
    	cout<<instruction_file[i].opcode<<" "<<instruction_file[i].source<<" "<<instruction_file[i].operand1<<" "<<instruction_file[i].operand2<<" "<<instruction_file[i].type<<"\n";
    }
    for (int i = 0; i < temp_symb.size(); ++i)
    {
    	cout<<temp_symb[i].name<<"\t"<<temp_symb[i].pos<<"\t"<<temp_symb[i].type<<"\n";
    }
    for (int i = 0; i < symbol_table.size(); ++i)
    {
    	cout<<symbol_table[i].name<<"\t"<<symbol_table[i].pos<<"\t"<<symbol_table[i].type<<"\n";
    }
    for (int i = 0; i < symbol_table.size(); ++i)
    {
    	for (int j = 0; j < temp_symb.size(); ++j)
    	{
    		if(symbol_table[i].name == temp_symb[j].name)
    		{
    			if(temp_symb[j].type == 0)
    			{	instruction_file[temp_symb[j].pos].source = symbol_table[i].pos;
    			}
    			else
    			{
    				instruction_file[temp_symb[j].pos].operand1 = symbol_table[i].pos;
    			}
    		}
    	}
    }
    for (int i = 0; i < temp_symb.size(); ++i)
    {
    	cout<<temp_symb[i].name<<"\t"<<temp_symb[i].pos<<"\t"<<temp_symb[i].type<<"\n";
    }
    for (int i = 0; i < instruction_file.size(); i++)
    {
    	cout<<instruction_file[i].opcode<<" "<<instruction_file[i].source<<" "<<instruction_file[i].operand1<<" "<<instruction_file[i].operand2<<" "<<instruction_file[i].type<<"\n";
    }
    prog = -1;
    cout<<Register_MEM_WB.write_data<<" "<<Register_MEM_WB.src<<" "<<Register_MEM_WB.opcode<<" "<<Register_MEM_WB.type<<"\n";
    cout<<Register_EX_MEM.val_arith<<" "<<Register_EX_MEM.val_address<<" "<<Register_EX_MEM.src<<" "<<Register_EX_MEM.zero<<" "<<Register_EX_MEM.prog_cnt<<" "<<Register_EX_MEM.opcode<<" "<<Register_EX_MEM.type<<"\n";
    cout<<Register_ID_EX.src<<" "<<Register_ID_EX.r1<<" "<<Register_ID_EX.r2<<" "<<Register_ID_EX.address<<" "<<Register_ID_EX.offset<<" "<<Register_ID_EX.prog_cnt<<" "<<Register_ID_EX.opcode<<" "<<Register_ID_EX.type<<"\n";
    cout<<Register_IF_ID.recent_instruction.opcode<<" "<<Register_IF_ID.recent_instruction.operand1<<" "<<Register_IF_ID.recent_instruction.operand2<<" "<<Register_IF_ID.recent_instruction.type<<" "<<Register_IF_ID.prog_cnt<<"\n";
    while(shut_down == 0)
    {
    	WB();
    	MEM();
    	EX();
    	ID();
    	IF();
    	for (int i = 0; i < 16; ++i)
    	{
    		cout<<r[i]<<"\t";
    	}
    	cout<<"\n";
    }
}