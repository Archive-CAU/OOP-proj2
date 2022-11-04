#pragma once
#include "inf_int.h"
#include "string"
#include "vector"

using namespace std;

class Calculator {
public:
	Calculator();

	void getInput();
	vector<string> split(string str, char Delimiter);

	inf_int add(inf_int a, inf_int b);
	inf_int subtract(inf_int a, inf_int b);
	inf_int multiply(inf_int a, inf_int b);
};