#include <iostream>
#include <string>
using namespace std;
int main(){

	int num[5]{2,4,5,1,7};	// объявляем и инициализируем массив целых чисел
	
	int n = size(num);	// размер массива
	
	for (int i = 0; i<n; i++){		// цикл по индексам массива
		cout << num[i] <<"\n";
	}
	
	cout <<"\n";
	
	for (int i: num){		// цикл по элементам массива
		cout << i <<"\n";
	}
}



