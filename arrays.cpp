#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
using namespace std;

void inputArray(vector<int>& array, int size) {
    cout << "Введите " << size << " элементов: ";
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
}

void printArray(const vector<int>& array) {
    for (int value : array) {
        cout << value << " ";
    }
    cout << endl;
}

// 1. Организовать ввод элементов массива с клавиатуры. Размер массива 
// также должен задаваться пользователем. Введённый массив вывести на экран.

void task1() {
    int arraySize;
    cout << "Введите размер массива: ";
    cin >> arraySize;
    
    vector<int> array(arraySize);
    inputArray(array, arraySize);
    
    cout << "Массив: ";
    printArray(array);
}

// 2. Создать массив случайного размера, состоящий из случайных целых чисел в заданном диапазоне.

void task2() {
    const int SIZE_MIN = 4;
    const int SIZE_MAX = 20;
    const int VALUE_MIN = 1;
    const int VALUE_MAX = 100;
    
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_int_distribution<> sizeDistribution(SIZE_MIN, SIZE_MAX);
    uniform_int_distribution<> valueDistribution(VALUE_MIN, VALUE_MAX);
    
    int arrayLength = sizeDistribution(generator);
    vector<int> array(arrayLength);
    
    for (int i = 0; i < arrayLength; i++) {
        array[i] = valueDistribution(generator);
    }
    
    cout << "Размер массива: " << arrayLength << endl;
    cout << "Массив: ";
    printArray(array);
}

// 3. Заполнить массив случайным образом нулями и единицами так, чтобы количество 
// единиц было в точности равно количеству нулей.

void task3() {
    int arraySize;
    cout << "Введите размер (четный): ";
    cin >> arraySize;
    
    if (arraySize % 2 != 0) {
        cout << "Размер должен быть четным!" << endl;
        return;
    }
    
    vector<int> array(arraySize);
    int halfSize = arraySize / 2;
    
    for (int i = 0; i < halfSize; i++) {
        array[i] = 1;
    }
    for (int i = halfSize; i < arraySize; i++) {
        array[i] = 0;
    }
    
    random_device randomDevice;
    mt19937 generator(randomDevice());
    shuffle(array.begin(), array.end(), generator);
    
    cout << "Массив 0 и 1: ";
    printArray(array);
}

int calculateAlternatingSum(const vector<int>& array) {
    if (array.size() % 2 != 0) {
        return 0;
    }
    
    int totalSum = 0;
    for (int i = 0; i < array.size(); i += 2) {
        totalSum += array[i] - array[i + 1];
    }
    return totalSum;
}

// 4. Дан массив A из 2n элементов. Вычислить A1−A2 + A3−A4 + … +A2n−1 + A2n.

void task4() {
    vector<int> array;
    cout << "Введите элементы массива (четное количество): ";
    int value;
    while (cin >> value) {
        array.push_back(value);
    }
    
    if (array.size() % 2 != 0) {
        cout << "Количество элементов должно быть четным!" << endl;
        return;
    }
    
    int result = calculateAlternatingSum(array);
    cout << "Результат: " << result << endl;
}

pair<int, int> findClosestSumPair(const vector<int>& array, int target) {
    int minDifference = INT_MAX;
    pair<int, int> result;
    
    for (int i = 0; i < array.size(); i++) {
        for (int j = i + 1; j < array.size(); j++) {
            int sum = array[i] + array[j];
            int difference = abs(sum - target);
            
            if (difference < minDifference) {
                minDifference = difference;
                result = make_pair(array[i], array[j]);
            }
        }
    }
    return result;
}

// 5. Дан массив и число p. Найти два различных числа в массиве, сумма которых наиболее близка к p.

void task5() {
    vector<int> array = {5, 12, 8, 3, 15, 7, 9, 4};
    int target;
    cout << "Введите число p: ";
    cin >> target;
    
    pair<int, int> closestPair = findClosestSumPair(array, target);
    int sum = closestPair.first + closestPair.second;
    
    cout << "Массив: ";
    printArray(array);
    cout << "Два числа с суммой, наиболее близкой к " << target << ": ";
    cout << closestPair.first << " и " << closestPair.second;
    cout << " (сумма = " << sum << ")" << endl;
}

void replaceEvenIndices(vector<int>& array) {
    for (int i = 2; i < array.size(); i += 2) {
        array[i] = array[i - 1];
    }
}

// 6. Дан массив чисел. Заменить каждый элемент с чётным индексом на соседний слева элемент.

void task6() {
    vector<int> array;
    cout << "Введите элементы массива: ";
    int value;
    while (cin >> value) {
        array.push_back(value);
    }
    
    cout << "Исходный массив: ";
    printArray(array);
    
    replaceEvenIndices(array);
    
    cout << "После замены: ";
    printArray(array);
}

void swapMinMax(vector<int>& array) {
    auto minIterator = min_element(array.begin(), array.end());
    auto maxIterator = max_element(array.begin(), array.end());
    
    if (minIterator != array.end() && maxIterator != array.end()) {
        swap(*minIterator, *maxIterator);
    }
}

// 7. Дан массив. Поменять местами наибольший и наименьший элементы массива.

void task7() {
    vector<int> array;
    cout << "Введите элементы массива: ";
    int value;
    while (cin >> value) {
        array.push_back(value);
    }
    
    cout << "Исходный массив: ";
    printArray(array);
    
    swapMinMax(array);
    
    cout << "После обмена: ";
    printArray(array);
}

vector<int> findCommonElements(const vector<int>& firstArray, const vector<int>& secondArray) {
    vector<int> commonElements;
    
    for (int i = 0; i < firstArray.size(); i++) {
        bool found = false;
        for (int j = 0; j < secondArray.size(); j++) {
            if (firstArray[i] == secondArray[j]) {
                found = true;
                break;
            }
        }
        
        if (found) {
            bool alreadyExists = false;
            for (int k = 0; k < commonElements.size(); k++) {
                if (commonElements[k] == firstArray[i]) {
                    alreadyExists = true;
                    break;
                }
            }
            if (!alreadyExists) {
                commonElements.push_back(firstArray[i]);
            }
        }
    }
    return commonElements;
}

// 8. Даны два массива. Сформировать третий массив, состоящий из тех элементов, 
// которые присутствуют в обоих массивах.

void task8() {
    vector<int> firstArray = {1, 2, 3, 4, 5, 2};
    vector<int> secondArray = {3, 4, 5, 6, 7, 4};
    
    vector<int> commonElements = findCommonElements(firstArray, secondArray);
    
    cout << "Первый массив: ";
    printArray(firstArray);
    cout << "Второй массив: ";
    printArray(secondArray);
    cout << "Общие элементы: ";
    printArray(commonElements);
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    
    return 0;
}

