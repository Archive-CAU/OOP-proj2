#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"

inf_int::inf_int() {
	// default value 0
	this->digits = string();
	this->digits.push_back('0');

	this->length = 1;
	this->thesign = true; // only minus is false (0)
}


inf_int::inf_int(int n) {
	char buffer[100];

	if (n < 0) {
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0)
	{
		buffer[i] = n % 10 + '0';
		n /= 10;
		i++;
	}

	if (i == 0) {
		new (this) inf_int();
	}
	else {
		buffer[i] = '\0';

		this->digits = string();
		this->length = i;

		// make digits using buffer
		for (int j = 0; j < i + 1; j++) {
			if (buffer[j] == '\0') 
				break;
			this->digits.push_back(buffer[j]);
		}
	}
}

inf_int::inf_int(const char* str) {
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	unsigned int lengthOfStr = strlen(str);
	this->length = lengthOfStr;

	this->digits = string();

	for (int i = 0; i < lengthOfStr; i++) {
		this->digits.push_back(str[lengthOfStr - 1 - i]);
	}
}

inf_int::inf_int(const inf_int& a) {
	this->digits = string();
	//for (auto digit : a.digits) {
	//	this->digits.push_back(digit);
	//}
	for (int i = 0; i < a.length; i++) {
		this->digits.push_back(a.digits[i]);
	}

	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() {
}

inf_int& inf_int::operator=(const inf_int& a) {
	this->digits = string();
	for (int i = 0; i < a.length; i++) {
		this->digits.push_back(a.digits[i]);
	}

	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
	// we assume 0 is always positive.
	if ((a.digits == b.digits) && a.thesign == b.thesign)	// 부호가 같고, 절댓값이 일치해야함.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
	// to be filled
	// 절대값 비교
	// 둘 다 양수일 경우 절댓값 비교한 것을 그대로 return
	// 둘 다 음수일 경우 절댓값 비교의 것을 반전하여 return
	// 부호가 다를 경우, a가 양수일 경우 b는 음수, a가 음수일 경우 b는 양수이기에 a의 부호진리값을 반환하면 됨
	
	// 값이 동일할 때
	if (a == b) return false;

	// 값이 동일하지 않을 때
	else {
		if (a.thesign && b.thesign) return compareAbs(a, b);
		else if (!a.thesign && !b.thesign) return !compareAbs(a, b);
		else return a.thesign;
	}
}

bool operator<(const inf_int& a, const inf_int& b) {
	if (operator>(a, b) || operator==(a, b)) return false;
	else return true;
}

inf_int operator+(const inf_int& a, const inf_int& b) {
	inf_int c;
	c.digits = string();

	if (a.thesign == b.thesign) {	// 이항의 부호가 같을 경우 + 연산자로 연산
		if (a.length > b.length) {
			int carry = 0;

			// a와 b가 겹치는 범위 연산
			for (int i = 0; i < b.length; i++) {
				int sum = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');
				carry = sum / 10;
			}

			// 남는 a 범위 연산
			for (int i = b.length; i < a.length; i++) {
				int sum = ((a.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');
				carry = sum / 10;
			}

			if (carry) c.digits.push_back(carry + '0');
		}

		else {
			int carry = 0;
			// a와 b가 겹치는 범위 연산
			for (int i = 0; i < a.length; i++) {
				int sum = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');
				carry = sum / 10;
			}

			// 남는 b 범위 연산
			for (int i = a.length; i < (int)b.length; i++) {
				int sum = ((b.digits[i] - '0') + carry);
				c.digits.push_back(sum % 10 + '0');
				carry = sum / 10;
			}

			if (carry) c.digits.push_back(carry + '0');
		}


		c.length = c.digits.length();
		c.thesign = a.thesign;

		return c;
	}
	else {	// 이항의 부호가 다를 경우 - 연산자로 연산
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

//inf_int operator-(const inf_int& a, const inf_int& b)
//{
//	inf_int c;
//	unsigned int i;
//
//	if (a.thesign != b.thesign) {
//		// 5 - (-3) -> 5 + 3
//		// -5 - 3 -> -5 + (-3)
//		c = b;
//		c.thesign = a.thesign;
//		return a + c;
//	}
//	else {
//		// -5 - (-3)
//		// -5 - (-8) = 3
//		// 15 - 3 = 12
//		// 5 - 8
//
//		c.thesign = a > b ? 0 : 1;
//
//	}
//}

//inf_int operator*(const inf_int& a, const inf_int& b)
//{
//	// to be filled
//}


ostream& operator<<(ostream& out, const inf_int& a) {
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}



bool compareAbs(const inf_int& a, const inf_int& b) {
	// compare Abs of a and b
	// if a is larger, return value is true

	if (a.length > b.length) return true;
	else if (a.length < b.length) return false;
	else {
		for (int i = 0; i < a.length; i++) {
			if (a.digits[i] > b.digits[i]) {
				return true;
			}
			else if (a.digits[i] < b.digits[i]) {
				return false;
			}
		}
		return false;
	}
}
