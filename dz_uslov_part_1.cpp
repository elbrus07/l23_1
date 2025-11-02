#include <iostream>
#include <cmath>

using namespace std;

/*
int main() {
	setlocale(LC_ALL, "RU");
	int a,b,c;
	cout << "Введите три числа";
	cin >> a >> b >> c;
	if (a>b and a>c) {
		cout << "a-max";
	}
	else if (b>a and b>c) {
		cout << "b-max\n";
	}
	else {
		cout << "c-max\n";

	}
	return 0;
}
*/

/*
int main() {
	setlocale(LC_ALL, "RU");

	int a, b, c;

	cout << "Введите три числа";
	cin >> a >> b >> c;

	if (a*b*c == 0) {
		cout << a+b+c << endl;
	}
	else {
		cout << a*b*c;

	}
	return 0;
}
*/

/*
int main() {
	setlocale(LC_ALL, "RU");

	int a, b, c;
	cout << "Введите три числа: ";
	cin >> a >> b >> c;

	if (a <= b && a <= c) {
		if (b <= c) {
			cout << a << " " << b << " " << c << endl;
		}
		else {
			cout << a << " " << c << " " << b << endl;
		}
	}
	else if (b <= a && b <= c) {
		if (a <= c) {
			cout << b << " " << a << " " << c << endl;
		}
		else {
			cout << b << " " << c << " " << a << endl;
		}
	}
	else {
		if (a <= b) {
			cout << c << " " << a << " " << b << endl;
		}
		else {
			cout << c << " " << b << " " << a << endl;
		}
	}

	return 0;
}
*/

/*
int main() {
	setlocale(LC_ALL, "RU");
	int a, b, c;

	cout << "Введите три числа";
	cin >> a >> b >> c;
	if (a * b * c != 0) {

		if (a < (b + c) && b < (a + c) && c < (b + a)) {
			cout << "стороны abc стороны треугольника " << endl;
		}

		else {
			cout << "стороны abc стороны треугольника"<< endl;
		}
	}
	else {
		cout << "сторона равна нулю" << endl;
	}
	
	return 0;
}
*/

/*
int main() {
	setlocale(LC_ALL, "RU");

	int a, b, c;
	cout << "Введите коэфиценты квадратного уравнения начиная со старшей степени";
	cin >> a >> b >> c;
	
	cout <<"x1 = " << (-b + pow((b * b - 4 * a * c), 1 / 2)) / (2 * a) << endl;

	cout << "x2 = "<<(-b - pow((b * b - 4 * a * c), 1 / 2)) / (2 * a);
	return 0;
}
*/
/*
int main() {
	setlocale(LC_ALL, "RU");

	int x,y;
	cout << "Введите координаты";
	cin >> x >> y;
	if (x > 0 && y > 0) {
		cout << "Точка находится в I четверти" << endl;
	}
	else if (x < 0 && y > 0) {
		cout << "Точка находится во II четверти" << endl;
	}
	else if (x < 0 && y < 0) {
		cout << "Точка находится в III четверти" << endl;
	}
	else if (x > 0 && y < 0) {
		cout << "Точка находится в IV четверти" << endl;
	}
	else if (x == 0 && y == 0) {
		cout << "Точка является началом координат" << endl;
	}
	else if (x == 0) {
		cout << "Точка лежит на оси Y" << endl;
	}
	else if (y == 0) {
		cout << "Точка лежит на оси X" << endl;
	}

	return 0;
}

*/

	