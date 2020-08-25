#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include <deque>

using namespace std;

int main(int argc, char const *argv[]){
	Queue<int> qu;
	
	for (int i = 10; i > 0; --i)
	{
		qu.enqueue(i*i);
	}
	cout<<qu.dequeue()<<endl;

	return 0;
}