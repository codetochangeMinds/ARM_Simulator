#include <iostream>
#include<bits/stdc++.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
using namespace std;


ifstream fin;
vector<string> lexeme;
int prog=0;
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
vector<loop> loops;
vector<loop1> data;
string exit_name = "Exit";


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
    	cout<<lexeme[i]<<endl;
    }

    //driver statement
    while(prog < lexeme.size())
    {
        //cout<<prog<<endl;
        if(lexeme[prog]=="Add"||lexeme[prog]=="add"||lexeme[prog]=="ADD"||lexeme[prog]=="Sub"||lexeme[prog]=="sub"||lexeme[prog]=="SUB"||lexeme[prog]=="Mul"||lexeme[prog]=="mul"||lexeme[prog]=="MUL"||lexeme[prog]=="Mov"||lexeme[prog]=="mov"||lexeme[prog]=="MOV"||lexeme[prog]=="Ldr"||lexeme[prog]=="ldr"||lexeme[prog]=="LDR"||lexeme[prog]=="Str"||lexeme[prog]=="str"||lexeme[prog]=="STR")
		{
            int c=prog;
            int p=execute(prog);
            if(p==-1)
            {
            	cout<<"Error in "<<lexeme[c]<<" instruction"<<endl;
            }
        }
    	else if(lexeme[prog]=="Cmp"||lexeme[prog]=="cmp" ||lexeme[prog]=="CMP")
    	{
            int q=compare(prog);
            if(q==-1)
            {
            	cout<<"Error in cmp instruction"<<endl;
            }
    	}
        else prog++;
        
    }
}