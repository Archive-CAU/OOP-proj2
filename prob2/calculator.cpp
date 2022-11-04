#include "Calculator.h"
#include "string"
#include "vector"
#include <sstream>
#include <iostream>

using namespace std;

Calculator::Calculator() {
	getInput();
}

void Calculator::getInput() {
	string input;
	while (1) {
		cout << "Input: ";
		getline(cin, input);

		// ��������
		if (input == "0") break;

		vector<string> result = split(input, ' ');
		inf_int operand1 = inf_int(result[0].c_str());
		inf_int operand2 = inf_int(result[2].c_str());
		string oper = result[1];

		if (oper.compare("+") == 0) {
			cout << "Output: " << add(operand1, operand2) << endl;
		}
		else if (oper.compare("-") == 0) {
			cout << "Output: " << subtract(operand1, operand2) << endl;
		}
		else if (oper.compare("*") == 0) {
			cout << "Output: " << multiply(operand1, operand2) << endl;
		}
		else {
			cout << "Wrong Input! try ex) 1234 + 5678" << endl;
		}
	}
}
vector<string> Calculator::split(string str, char Delimiter) {
	istringstream iss(str);             // istringstream�� str�� ��´�.
	string buffer;                      // �����ڸ� �������� ����� ���ڿ��� ������� ����

	vector<string> result;

	// istringstream�� istream�� ��ӹ����Ƿ� getline�� ����� �� �ִ�.
	while (getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);               // ����� ���ڿ��� vector�� ����
	}

	return result;
}

inf_int Calculator::add(inf_int a, inf_int b) {
	return a + b;
}

inf_int Calculator::subtract(inf_int a, inf_int b) {
	return a - b;
}

inf_int Calculator::multiply(inf_int a, inf_int b) {
	return a * b;
}