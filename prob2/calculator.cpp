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

		// 종료조건
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
	istringstream iss(str);             // istringstream에 str을 담는다.
	string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼

	vector<string> result;

	// istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
	while (getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
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