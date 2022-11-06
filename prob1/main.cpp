#include "inf_int.h"
#include <stdlib.h>
#include <conio.h>

using namespace std;

void Test();

int main()
{
	inf_int a, e;
	inf_int b(100);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	inf_int f = d;
	inf_int g(f);

	// cin >> g ;   // not required

	a = b * c;
	// e=g/f;       // not required

	b = c - d;


	if (f == d) {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
		cout << "d : " << d << endl;
		// cout << "e : " << e << endl;
		cout << "f : " << f << endl;
		// cout << "g : " << g << endl;
	}

	Test();
	_getch();
	return 0;
}

void Test () {
	inf_int a("430");
	inf_int b("919");
	inf_int c("20215406");
	inf_int d("20213132");
	inf_int e(0);
	inf_int f("-567");
	inf_int g("111111111");
	inf_int h("-78987654");
	

	cout << endl;
	cout << "Test is given.." << endl;
	cout << "430 + 919 = " << a + b << endl;
	cout << "430 * 919 = " << a * b << endl;
	cout << "20215406 - 20213132 = " << c - d << endl;
	cout << "20213132 * 0 = " << d * e << endl;
	cout << "111111111 * 111111111 = " << g * g << endl;
	cout << "-567 - 20215406 = " << f - c << endl;
	cout << "-78987654 - (-567) = " << h - f << endl;
	cout << "111111111 - (-78987654) = " << g - h << endl;
	cout << "430 - 919 = " << a - b << endl;
	cout << "919 - 430 = " << b - a << endl;
	cout << "-567 * 0 = " << f * e << endl;
	cout << "0 * 0 = " << e * e << endl;
	cout << "0 + 0 = " << e + e << endl;
	cout << "0 - 0 = " << e - e << endl;
	cout << "-567 * 430 = " << f * a << endl;
	cout << "-567 * -567 = " << f * f << endl;
	cout << "919 * (-567) = " << b * f << endl;

};