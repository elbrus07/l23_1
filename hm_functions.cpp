#include <iostream>
#include <cmath>
#include <algorithm>


// 1. Определить периметр треугольника, заданного координатами вершин.
// Длину стороны треугольника вычислять в функции. Посчитать среднее
// арифметическое периметров трех треугольников, координаты которых ввести с клавиатуры.

double sideLength(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

double trianglePerimeter(double x1, double y1, double x2, double y2, double x3, double y3) {
    return sideLength(x1, y1, x2, y2) +
          sideLength(x2, y2, x3, y3) +
          sideLength(x3, y3, x1, y1);
}


// 2. Написать функцию для сортировки массива. Выбор метода сортировки
// осуществляется путем передачи соответствующего параметра.

void bubbleSort(int num[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (num[j] > num[j + 1]) {
                std::swap(num[j], num[j + 1]);
            }
        }
    }
}

void selectSort(int num[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minn = i;
        for (int j = i + 1; j < size; j++) {
            if (num[j] < num[minn]) {
                minn = j;
            }
        }
        std::swap(num[i], num[minn]);
    }
}

void sortNum(int num[], int size, int method) {
    if (method == 1) {
        bubbleSort(num, size);
        std::cout << "Отсортировано методом пузырька" << std::endl;
    } else if (method == 2) {
        selectSort(num, size);
        std::cout << "Отсортировано методом выбора" << std::endl;
    }
}


//  3. Написать функцию табуляции функции  в точках x = 1,2,3,..., 12.

double calcFunction(double x) {
    return pow(x, 2) + 2 * x + 1;
}

void tabulateFunction() {
    std::cout << "\nТабуляция функции f(x) = x^2 + 2x + 1:" << std::endl;
    std::cout << "x\tf(x)" << std::endl;
    
    for (int x = 1; x <= 12; x++) {
        double result = calcFunction(x);
        std::cout << x << "\t" << result << std::endl;
    }
}


//4. Написать функцию, вычисляющую количество совпадений числа x 

int countMatches(int arr[], int size, int x) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    return count;
}

int main() {

    // 1 задание
    
    // double sum = 0;
    // std::cout << "Вычисление среднего периметра 3 треугольников\n";
    
    // for (int i = 0; i < 3; i++) {
    //     std::cout << "\nТреугольник " << i+1 << ":\n";
    
    //     double x1, y1, x2, y2, x3, y3;
    //     std::cout << "Введите координаты (x1 y1 x2 y2 x3 y3): ";
    //     std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
    //     double p = trianglePerimeter(x1, y1, x2, y2, x3, y3);
    //     sum += p;
    //     std::cout << "Периметр: " << p << "\n";
    // }
    // std::cout << "\nСредний периметр: " << sum / 3 << std::endl;
    
    // 2 задание
    
    // int num[] = {7, 3, 9, 1, 4};
    // int size = 5;  
    // int method = 1; // 1 - пузырьком, 2 - выборкой
    
    // std::cout << "Исходный массив: ";
    // for (int i = 0; i < size; i++) {
    //     std::cout << num[i] << " ";
    // }
    // std::cout << std::endl;
    
    // int copy[5]; 
    // for (int i = 0; i < size; i++) {
    //     copy[i] = num[i];
    // }
    // sortNum(copy, size, method);
    
    // std::cout << "Отсортированный массив: ";
    // for (int i = 0; i < size; i++) {
    //     std::cout << copy[i] << " ";
    // }
    // std::cout << std::endl;
    
    // 3 задание
    
    // tabulateFunction();
    
    //4 задание
    
    // int num[] = {5, 2, 9, 2, 4, 12, 5, 2, 16, 2};
    // int size = 10;
    // int x = 2;  // число, которое ищем
    
    // int result = countMatches(num, size, x);
    // std::cout << "Число " << x << " встречается " << result << " раз(а)" << std::endl;
    
    return 0;
}

