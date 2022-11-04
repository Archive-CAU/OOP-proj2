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
	if (str[0] == '-') this->thesign = false;
	else this->thesign = true;
	

	unsigned int lengthOfStr = strlen(str);
	this->digits = string();

	if (this->thesign) {
		for (int i = 0; i < lengthOfStr; i++) {
			this->digits.push_back(str[lengthOfStr - 1 - i]);
		}
		this->length = lengthOfStr;
	}
	else {
		for (int i = 0; i < lengthOfStr - 1; i++) {
			this->digits.push_back(str[lengthOfStr - 1 - i]);
		}
		this->length = lengthOfStr - 1;
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
				int addition = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
			}

			// 남는 a 범위 연산
			for (int i = b.length; i < a.length; i++) {
				int addition = ((a.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
			}

			if (carry) c.digits.push_back(carry + '0');
		}

		else {
			int carry = 0;
			// a와 b가 겹치는 범위 연산
			for (int i = 0; i < a.length; i++) {
				int addition = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
			}

			// 남는 b 범위 연산
			for (int i = a.length; i < b.length; i++) {
				int addition = ((b.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
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

inf_int operator-(const inf_int& a, const inf_int& b)
{
	inf_int c;
	// a > b
	if (compareAbs(a, b)) {
		if (a.thesign == b.thesign) {
			c.digits = string();
			int carry = 0;

			// a와 b 겹치는 부분 계산
			for (unsigned int i = 0; i < b.length; i++) {
				int subtraction = ((a.digits[i] - '0') - (b.digits[i] - '0') - carry);
				if (subtraction < 0) {
					subtraction = subtraction + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(subtraction + '0');
			}

			// 남는 a 범위 계산
			for (unsigned int i = b.length; i < a.length; i++) {
				int subtraction = ((a.digits[i] - '0') - carry);
				if (subtraction < 0) {
					subtraction = subtraction + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(subtraction + '0');
			}

			// 뒷자리부터 무의미한 0 제거
			unsigned int numOfZero = 0;
			for (unsigned int i = c.digits.length() - 1; i > 0; i--) {
				if (c.digits[i] == '0') numOfZero++;
				else break;
			}
			c.digits = c.digits.substr(0, c.digits.length() - numOfZero);

			c.length = c.digits.length();
			c.thesign = a.thesign;
			
			return c;
		}
		else {
			
			inf_int temp = b;
			temp.thesign = a.thesign;
			c = a + temp;
			return c;
		}
	}

	// a == b
	else if (a.digits == b.digits) {
		if (a.thesign == b.thesign) {
			c = inf_int(); // return 0
		}
		else {
			c = a + a;
			c.thesign = a.thesign;
		}
		return c;
	}

	// a < b
	else {
		if (a.thesign == b.thesign) {
			c.digits = string();
			int carry = 0;

			// a와 b 겹치는 부분 계산
			for (unsigned int i = 0; i < a.length; i++) {
				int subtraction = ((b.digits[i] - '0') - (a.digits[i] - '0') - carry);
				if (subtraction < 0) {
					subtraction = subtraction + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(subtraction + '0');
			}

			// b 남는 부분 계산
			for (unsigned int i = a.length; i < b.length; i++) {
				int subtraction = ((b.digits[i] - '0') - carry);
				if (subtraction < 0) {
					subtraction = subtraction + 10;
					carry = 1;
				}
				else {
					carry = 0;
				}
				c.digits.push_back(subtraction + '0');
			}

			// 뒷자리부터 무의미한 0 제거
			unsigned int numOfZero = 0;
			for (unsigned int i = c.digits.length() - 1; i > 0; i--) {
				if (c.digits[i] == '0') numOfZero++;
				else break;
			}
			c.digits = c.digits.substr(0, c.digits.length() - numOfZero);

			c.length = c.digits.length();
			
			if (a.thesign) c.thesign = false;
			else c.thesign = true;
			
			return c;
		}
		else {
			inf_int temp = b;
			temp.thesign = a.thesign;
			c = a + temp;
			return c;
		}
	}
}


inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int c;
	// a or b is zero
	if (isZero(a) || isZero(b)) {
		c = inf_int();
		return c;
	}

	else {
		// 가장 클 경우를 대비해서 크게 잡아두기
		c.digits = string(a.length + b.length, 0);

		// sign determination
		if (a.thesign == b.thesign) c.thesign = true;
		else c.thesign = false;

		for (int i = 0; i < a.length; i++) {
			for (int j = 0; j < b.length; j++) {
				int production = c.digits[i + j] + (a.digits[i] - '0') * (b.digits[j] - '0');
				c.digits[i + j] = production % 10;
				c.digits[i + j + 1] += production / 10;
			}
		}

		// 계산 마친 후 ASCII
		for (int i = 0; i < c.digits.length(); i++) {
			c.digits[i] += '0';
		}

		// 크게 잡아둔 범위를 결과에 맞게 줄이기
		if (c.digits[c.digits.length() - 1] == '0') {
			c.digits = c.digits.substr(0, c.digits.length() - 1);
		}

		c.length = c.digits.length();
		return c;
	}

}


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

bool isZero(const inf_int& a) {
	if (a.length != 1) return false;
	if (a.thesign != true) return false;
	if (a.digits[a.length - 1] != '0') return false;
	return true;
}

