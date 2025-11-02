#include <iostream>

using namespace std;



//1. Для введённого пользователем целого числа выдать максимальную цифру, минимальную цифру и их произведение
/*
int main() {
	setlocale(LC_ALL, "RU");

	int a,flag;
	cout << "Введите целое число ";
	cin >> a;

	flag = a;
	int maxn = 0;
	int k = 0;
	int minn = 1000000;

	while (a > 0) {
		if (flag > 9) {
			k = flag % 10;
		}
		else {
			k = flag;
		}

		//max 
		if (maxn >= k) {
			maxn = maxn;
		}
		else {
			maxn = k;
		}

		//min
		if (minn <= k) {
			minn = minn;
		}
		else {
			minn = k;
		}

		a = a / 10;
		flag = a;
		if (a == 0) {
			break;
		}
	}

	cout << "max " << maxn << endl;
	cout << "min " << minn << endl;
	cout << "product max and min = " << minn * maxn << endl;

	return 0;
}
*/

//2. Последовательность содержит некоторое количество натуральных чисел и заканчивается числом 0 (0 не является элементом последовательности). Найти сумму вех элементов последовательности 
/*
int main() {
	setlocale(LC_ALL, "RU");
	int a;
	cout << "Задайте последовательность ";
	cin >> a;
	int suma = 0;
	for (int i{0}; a > i-1; i++) {
		suma += i;
	}
	cout << suma;
	return 0;
}
*/

//3. Дано целое число. Удалить из него заданную цифру. Например, если задано 1464235 и цифра 4, то должно получиться 16235.

int main() {
	setlocale(LC_ALL, "RU");

	int a,b, flag;
	cout << "Введите целое число и цифру которую нужно удалить ";
	cin >> a >> b ;

	flag = a;
	int k = 0;
	int num = 0;

	while (a > 9) {
		k = a % 10;

		if (k != b) {
			num = num * 10 + k;
		}

		else {
			num = num;
		}

		a = a / 10;
		flag = flag / 10;
	}

	if (flag != b ) {
		num = num * 10 + flag;
	}
		
	k = 0;
	int newnum = 0;

	while (num > 9) {
		k = num % 10;
		num = num / 10;
		newnum = newnum * 10 + k;
		
	}
	newnum = newnum * 10 + num;
	cout << newnum;


	return 0;
}