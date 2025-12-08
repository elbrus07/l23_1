#include <iostream>
#include <cmath>

//1  Определить периметр треугольника, заданного координатами вершин.
// Длину стороны треугольника вычислять в функции. 
// Посчитать среднее арифметическое периметров трех треугольников, 
// координаты которых ввести с клавиатуры.
/*
double vector(double x1, double y1,double x2 , double y2){
	double len;
	len = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return len;
}

int main() {
	double x1, x2, x3, y1, y2, y3;
	std::cout << "Введите координаты вершин треугольника ";
	std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	double perimetr = vector(x2, x1, y2, y1) + vector(x2, x3, y2, y3) + vector(x1, x3, y1, y3);
	std::cout << perimetr;
	return 0;
}
*/

//2 

/*
void bubbleSort(int list[], int listLength)
{
	while (listLength --)
	{
		bool swapped = false;

		for (int i = 0; i < listLength; i++)
		{
			if (list[i] > list[i + 1])
			{
				std::swap(list[i], list[i + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

void sort(int list[],int listLength) {
	int choice;
	std::cout << "введите цифру для выбора сортировки" << std::endl;
	std::cout << "1 - Сортировка пузырьком" << std::endl;
	std::cin >> choice;
	switch (choice) {
	case 1:
		bubbleSort(list, listLength);
	}
}
int main()
{
	int list[5] = {1,5,6,3,0 };
	for (int i = 0; i < 5; i++)
		std::cout << list[i];
	std::cout << std::endl;

	sort(list,5);

	for (int i = 0; i < 5; i++)
		std::cout << list[i];
	std::cout << std::endl;
}
*/
//4 Написать функцию, вычисляющую количество совпадений числа x с элементами числового массива

/*
int counter(int x, int list[],int listLength) {
	int k = {0};
	for (int i{0}; i <= listLength; i++) {
		if (list[i] == x) {
			k++;
		}
	}
	return k;
}
int main() {
	int x;
	int list[13] = {3, 1,2,4,5,26,734,5,6,7,3,3,3 };
	std::cout << "введите число которое хотите посчитать";
	std::cin >> x;
	std::cout << counter(x, list, 13);
}
*/
