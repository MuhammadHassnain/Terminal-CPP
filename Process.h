#pragma once
#include <string>
#include <vector>
#include <fstream>
class Process
{
	unsigned int pid;
	int value;
	int start_time;  //store start time of process
	int cpu_used;	//store currently cpu used time
	string IR;		//store instruction in execution

	string* instructions;
	int noOfInstruction;

public:
	static unsigned int PID;
	Process(){
		pid= 0;
		value=-1;
		cpu_used =-1;
		start_time = -1;
	}
	Process(int st){
		pid= PID;
		PID++;
		cout<<PID<< " iN CONSTRUCTOR"<<endl;
		value=1;
		cpu_used =2;
		start_time = st;
	}
	string* GetInstr_Array(){
		return instructions;
	}
	unsigned int Getpid(){
		return pid;
	}
	int GetValue(){
		return value;
	}
	int GetStartTime(){
		return start_time;
	}
	int GetCPU_Used(){
		return cpu_used;
	}
	void LoadInstructions(string& file){
		fstream _file(file,ios::in);
		string inst;
		Queue<string> temp;
		while(getline(_file,inst,'\n')){
			temp.enqueue(inst);
		}
		noOfInstruction = temp.Size();
		instructions = new string[noOfInstruction];

		for (int i = 0; i < noOfInstruction; ++i)
		{
			instructions[i] = temp.dequeue();
		}

		for (int i = 0; i < noOfInstruction; ++i)
		{
			cout<<instructions[i]<<endl;
		}

		
	}
	~Process();
	friend ostream& operator << (ostream& out,Process& p){
	
	}
	
};