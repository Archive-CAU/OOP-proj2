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
	if ((a.digits == b.digits) && a.thesign == b.thesign)	// ��ȣ�� ����, ������ ��ġ�ؾ���.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b) {
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
	// to be filled
	// ���밪 ��
	// �� �� ����� ��� ���� ���� ���� �״�� return
	// �� �� ������ ��� ���� ���� ���� �����Ͽ� return
	// ��ȣ�� �ٸ� ���, a�� ����� ��� b�� ����, a�� ������ ��� b�� ����̱⿡ a�� ��ȣ�������� ��ȯ�ϸ� ��

	// ���� ������ ��
	if (a == b) return false;

	// ���� �������� ���� ��
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

	if (a.thesign == b.thesign) {	// ������ ��ȣ�� ���� ��� + �����ڷ� ����
		if (a.length > b.length) {
			int carry = 0;

			// a�� b�� ��ġ�� ���� ����
			for (int i = 0; i < b.length; i++) {
				int addition = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
			}

			// ���� a ���� ����
			for (int i = b.length; i < a.length; i++) {
				int addition = ((a.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
			}

			if (carry) c.digits.push_back(carry + '0');
		}

		else {
			int carry = 0;
			// a�� b�� ��ġ�� ���� ����
			for (int i = 0; i < a.length; i++) {
				int addition = ((a.digits[i] - '0') + (b.digits[i] - '0') + carry);
				c.digits.push_back(addition % 10 + '0');
				carry = addition / 10;
			}

			// ���� b ���� ����
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
	else {	// ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
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

			// a�� b ��ġ�� �κ� ���
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

			// ���� a ���� ���
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

			// ���ڸ����� ���ǹ��� 0 ����
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

			// a�� b ��ġ�� �κ� ���
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

			// b ���� �κ� ���
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

			// ���ڸ����� ���ǹ��� 0 ����
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
		// ���� Ŭ ��츦 ����ؼ� ũ�� ��Ƶα�
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

		// ��� ��ģ �� ASCII
		for (int i = 0; i < c.digits.length(); i++) {
			c.digits[i] += '0';
		}

		// ũ�� ��Ƶ� ������ ����� �°� ���̱�
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
	if (a.digits[a.length - 1] != '0') return false;
	if (a.thesign != true) return false;

	return true;
}
