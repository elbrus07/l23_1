#include <iostream>
#include <cmath>
using namespace std;

// 1. Определить периметр треугольника, заданного координатами вершин.
// Длину стороны треугольника вычислять в функции. 
// Посчитать среднее арифметическое периметров трех треугольников, 
// координаты которых ввести с клавиатуры.

double calculateDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

double calculatePerimeter(double x1, double y1, double x2, double y2, double x3, double y3) {
    double side1 = calculateDistance(x1, y1, x2, y2);
    double side2 = calculateDistance(x2, y2, x3, y3);
    double side3 = calculateDistance(x3, y3, x1, y1);
    return side1 + side2 + side3;
}

void task1() {
    const int triangleCount = 3;
    double totalSum = 0;
    
    for(int i = 0; i < triangleCount; i++) {
        cout << "Треугольник " << i + 1 << endl;
        double x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        
        double perimeter = calculatePerimeter(x1, y1, x2, y2, x3, y3);
        cout << "Периметр: " << perimeter << endl;
        
        totalSum += perimeter;
    }
    
    double average = totalSum / triangleCount;
    cout << "Среднее: " << average << endl;
}

// 2. Написать функцию для сортировки массива.
// Выбор метода сортировки осуществляется путем передачи соответствующего параметра.

void bubbleSort(int array[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int array[], int size) {
    for(int position = 1; position < size; position++) {
        int currentElement = array[position];
        int previousIndex = position - 1;
        
        while(previousIndex >= 0 && array[previousIndex] > currentElement) {
            array[previousIndex + 1] = array[previousIndex];
            previousIndex--;
        }
        array[previousIndex + 1] = currentElement;
    }
}

void applySort(int array[], int size, int sortMethod) {
    switch(sortMethod) {
        case 1:
            bubbleSort(array, size);
            break;
        case 2:
            insertionSort(array, size);
            break;
        default:
            break;
    }
}

void printArray(int array[], int size) {
    for(int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void task2() {
    int array[] = {7, 3, 9, 1, 5, 2, 8, 4, 6};
    int arraySize = 9;
    
    cout << "Массив до: ";
    printArray(array, arraySize);
    
    int selectedMethod;
    cout << "Выберите 1 (пузырек) или 2 (вставки): ";
    cin >> selectedMethod;
    
    applySort(array, arraySize, selectedMethod);
    
    cout << "Массив после: ";
    printArray(array, arraySize);
}

double calculateFunction(double x) {
    if(x - 1 >= 0) {
        return sqrt(x - 1);
    }
    return -1;
}

// 3. Написать функцию табуляции функции f(x) = sqrt(x - 1) 
// в точках x = 1,2,3,..., 12.

void task3() {
    const int start = 1;
    const int end = 12;
    
    for(int x = start; x <= end; x++) {
        double functionValue = calculateFunction(x);
        if(functionValue >= 0) {
            cout << "x=" << x << " f(x)=" << functionValue << endl;
        } else {
            cout << "x=" << x << " не определено" << endl;
        }
    }
}

// 4. Написать функцию, вычисляющую количество совпадений числа x 
// с элементами числового массива

int countOccurrences(int targetValue, int array[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(array[i] == targetValue) {
            count++;
        }
    }
    return count;
}

void task4() {
    int array[] = {3, 7, 2, 3, 8, 3, 5, 7, 3, 1, 4, 3, 6};
    int arraySize = 13;
    
    cout << "Массив: ";
    printArray(array, arraySize);
    
    int targetValue;
    cout << "Введите число: ";
    cin >> targetValue;
    
    int result = countOccurrences(targetValue, array, arraySize);
    cout << "Совпадений: " << result << endl;
}

int main() {
    task1();
    task2();
    task3();
    task4();
    
    return 0;
}

