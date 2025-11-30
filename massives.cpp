#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <clocale>
#include <windows.h>
using namespace std;

    //1.  Организовать ввод элементов массива с клавиатуры. Размер массива также должен задаваться пользователем.
    // Введённый массив вывести на экран.

void create_mass() {
    /*
    Функция организовывает ввод элементов массива с клавиатуры
    Возврат/вывод - пусто / полученный массив
    */
    int value;
    int type_of_mass;

    cout << "Определите размер массива и тип данных массива через пробел:" << endl;
    cout << "(1 - int (целочисленный тип данных)" << endl;
    cout << "2 - double (числа с плавающей точкой)" << endl;
    cout << "3 - string (строки))" << endl;
    cout << "Ответ: " << endl;

    cin >> value >> type_of_mass;

    if (type_of_mass == 1) {
        int* mass = new int[value];
        cout << "Введите элементы через пробел: ";
        for (int i = 0; i < value; i++) {
            cin >> mass[i];
        }

        for (int i = 0; i < value; i++) {
            cout << mass[i] << " ";
        }
        delete[] mass;
    }

    else if (type_of_mass == 2) {
        double* mass = new double[value];

        for (int i = 0; i < value; i++) {
            cin >> mass[i];
        }

        for (int i = 0; i < value; i++) {
            cout << mass[i] << " ";
        }
        delete[] mass;
    }

    else if (type_of_mass == 3) {
        string * mass = new string[value];

        for (int i = 0; i < value; i++) {
            cin >> mass[i];
        }

        for (int i = 0; i < value; i++) {
            cout << mass[i] << " ";
        }
        delete[] mass;
    }

    else {
        cout << "Неверно выбран тип данных!";
    }
}

//2.  Создать массив случайного размера, состоящий из случайных целых чисел в заданном диапазоне.

void create_random_mass(int minlength, int maxlength) {
    /*
    Функция для создания массива из случайных чисел в заданном диапазоне
    minlength - минимальная длина массива(левая граница допустимого диапазона)
    maxlength - иаксимальная длина массива(правая граница допустимого диапазона)

    Возврат/вывод - пусто / полученный массив
    */
    srand(time(0));

    int minnum = 0;
    int maxnum = 100;

    int randomlength = rand() % (maxlength - minlength + 1) + minlength;

    int* mass = new int[randomlength];

    cout << "Полученный массив:\n";

    for (int i = 0; i < randomlength; i++) {
        mass[i] = rand() % (maxnum - minnum + 1) + minnum;
        cout << mass[i] << " ";
    }

    delete[] mass;
}

//3.  Заполнить массив случайным образом нулями и единицами так,
// чтобы количество единиц было в точности равно количеству нулей.

void create_null_one_mass() {
    /*
    Функция для создания массива с равным количеством нулей и единиц как его элементов
    Возврат/вывод - пусто / полученный массив
    */
    const int length = 12;

    int mass[length];

    for (int i = 0; i < length; i++) {
        if (i < length / 2) {
            mass[i] = 0;
        }
        else {
            mass[i] = 1;
        }

        cout << mass[i] << " ";
    }
}

//4.  Дан массив A из 2n элементов.Вычислить A1?A2 + A3?A4 + … + A2n?1 + A2n.

int calculate_sum() {
    /*
    Функция для вычисления A1 - A2 + A3 - A4 + … + A2n - 1 + A2n
    Возврат/вывод - res (целое число) / пусто
    */
    const int length = 6;
    int mass[length] = { 1, 2, 3, 4, 5, 6 };
    int res = 0;

    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            res += mass[i];
        }
        else res -= mass[i];
    }

    return res;
}

//5.  Дан массив и число p. Найти два различных числа в массиве, сумма которых наиболее близка к p.

void find_pair() {
    /*
    Функция находит два различных числа в массиве, сумма которых наиболее близка к p
    Возврат/вывод: пусто/ first, second - найденные числа (целые) / пусто
    */
    const int length = 5;
    int mass[length] = { 1, 8, 11, 23, 5 };
    int p = 33;
    int best_sum = 0;
    int first = mass[0];
    int second = mass[1];
    int min_ost =abs((first + second) - p);
    
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (abs((mass[i] + mass[j]) - p) < min_ost) {
                min_ost = abs(mass[i] + mass[j] - p);
                first = mass[i];
                second = mass[j];
            }
        }
    }
    cout << "Наиболее подходящие числа: " << first << " и " << second;
}

//6.  Дан массив чисел.Заменить каждый элемент с чётным индексом на соседний слева элемент.

void replace_elements() {
    /*
    Функция для замены элементов с четным индексом на соседние слева элементы (меняет исходный массив)
    Возврат/вывод - пусто / поулченный массив
    */
    const int length = 6;
    int mass[length] = { 2334,8976,247,68,46,23 };

    for (int i = 1; i < length; i += 2) {
        mass[i] = mass[i - 1];

    }

    for (int i = 0; i < length; i++) {
        cout << mass[i] << " ";
    }

}

//7.  Дан массив. Поменять местами наибольший и наименьший элементы массива.

void replace_max_min() {
    /*
    Функция меняет местами наибольший и наименьший элементы массива
    Возврат/вывод - пусто / поулченный массив (меняет изначальный массив)
    */
    const int length = 6;

    int mass[length] = { 1, 2, 3, 4, 5, 6 };

    int max = mass[0];
    int min = mass[0];

    int min_index = 0;
    int max_index = 0;

    for (int i = 0; i < length; i++) {
        if (max < mass[i]) {
            max = mass[i];
            max_index = i;
        }
        if (min > mass[i]) {
            min = mass[i];
            min_index = i;
        }
    }
    int perest = mass[max_index];
    mass[max_index] = mass[min_index];
    mass[min_index] = perest;

    for (int i = 0; i < length; i++) {
        cout << mass[i] << " ";
    }
}

//8.  Даны два массива. Сформировать третий массив, состоящий из тех элементов, которые присутствуют в обоих массиваx.

void find_commons() {
    /*
    Функция формирует третий массив, состоящий из тех элементов, которые присутствуют в обоих массиваx
    Возврат/вывод - пусто / полученный массив (создается новый массив)
    */
    int n = 0;
    int flag = 0;

    const int length1 = 5;
    int mass1[length1] = { 1, 8, 11, 23, 5 };

    const int length2 = 7;
    int mass2[length2] = { 5, 78, 2, 1, 5, 23, 43 };

    int* mass3 = new int[min(length1, length2)];

    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            if (mass1[i] == mass2[j]) {
                for (int k = 0; k < n; k++) {
                    if (mass1[i] == mass3[k]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    mass3[n] = mass1[i];
                    n++;
                }
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << mass3[i] << " ";
    }
}

int main() {

    //create_mass();
    //create_random_mass(1, 15);
    //create_null_one_mass();

    //int result = calculate_sum();
    //cout << "Результат: " << result;  

    //find_pair();
    //replace_elements();
    //replace_max_min();
    //find_commons();




    return 0;

}