#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
struct CPU
{
	string* ptr_instruction;
	string* pc;
	int integer_value;
	int cpu_used;	
};