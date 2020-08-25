#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include <sstream>
#include "Queue.h"
#include "Stack.h"
#include "Process.h"
#include <fstream>
#include "CPU.h"
using namespace std;


#define READ_END 0
#define WRITE_END 1
#define BUF_SIZE 100

int CPU_TIME =0; 

bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}
//CPU for CONTROLLER PROCESS
CPU* cpu;


//array to store file descripter for commiunication of 
//of in charge and controller processs
int fd[2];
//buffer to read and write message
char read_msg[BUF_SIZE],write_msg[BUF_SIZE];

//fifo queues for running,blocked and ready process;
Queue<Process*> *RunningPrcoess,*BlockedProcess,*ReadyProcess;

//variable to store id of child processs i.e controller process
pid_t id;


void myhandler(int a){
	read(fd[READ_END],read_msg,BUF_SIZE);
	string temp;
	istringstream s(read_msg);
	getline(s,temp,' ');
	if(temp=="CRT"){
		getline(s,temp,'\n');
		if(!fexists(temp)){
			cout<<" File doesn't exits"<<endl;
			return ;
		}

		Process* p = new Process(CPU_TIME);
		p->LoadInstructions(temp);
		ReadyProcess->enqueue(p); //put this in ready state

		if(RunningPrcoess->isEmpty()){ //if running is empty then 
										//put one process from ready to running
			RunningPrcoess->enqueue(ReadyProcess->dequeue());   
		}
	}else if(strcmp(read_msg,"INC")==0){
		//Load the Process in Running Queue to CPU
		cpu->ptr_instruction = ReadyProcess->Top()->GetInstr_Array();
		cout<<cpu->ptr_instruction[0];
	}

}

//function take input after every 2 sec

void alarm_handler(int s){
	cout<<">>";
	cin.getline(write_msg,BUF_SIZE);
	if((strcmp(write_msg,"UNB")==0) || 
	(strcmp(write_msg,"INC")==0) ||
	(strcmp(write_msg,"PRT")==0) ||
	(strcmp(write_msg,"END")==0) )	{
		write(fd[WRITE_END],write_msg,strlen(write_msg)+1);
		kill(id,SIGUSR1);
	}
	else {
		string temp;
		istringstream s(write_msg);
		getline(s,temp,' ');
		if(temp=="CRT" && strlen(write_msg)>4){
			write(fd[WRITE_END],write_msg,strlen(write_msg)+1);
			kill(id,SIGUSR1);
		}
		else{
			cout<<"Invalid Command"<<endl;
		}
	}
	alarm(2);
}
unsigned int Process::PID = 0;
int main(int argc, char const *argv[])
{

	if(pipe(fd)==-1){
		cout<<"Can't create pipe "<<endl;
	}
	id = fork();
	if(id==0){
		signal(SIGUSR1,myhandler);
		RunningPrcoess = new Queue<Process*>;
		BlockedProcess = new Queue<Process*>;
		ReadyProcess = new Queue<Process*>;

		//alocate memory to CPU 
		cpu = new CPU;



		while(1){
		//	pause();
		}
	}
	else if (id>0){
		alarm(2);
		signal(SIGALRM,alarm_handler);
		while(1){
		}
	}
	return 0;
}