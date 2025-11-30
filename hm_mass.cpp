#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;


//1.Организовать ввод элементов массива с клавиатуры. Размер массива 
//также должен задаваться пользователем. Введённый массив вывести на экран. 

// int main(int argc, char* argv[]) {
//     int n;
    
//     if (argc > 1) {
//         n = stoi(argv[1]);
//         cout << "Размер массива из аргументов: " << n << endl;
//     } else {
//         cout << "Введите размер массива: ";
//         cin >> n;
//     }
    
//     vector<int> arr(n);
//     cout << "Введите " << n << " элементов: ";
//     for (int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }
    
//     cout << "Массив: ";
//     for (int x : arr) {
//         cout << x << " ";
//     }
//     cout << endl;
    
//     return 0;
// }

//2.Создать массив случайного размера, состоящий из случайных целых чисел в заданном диапазоне. 

// int main() {
    
//     const int Min_size = 4;
//     const int Max_size = 20;
//     const int Min_value = 1;
//     const int Max_value = 100;
    
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> size_dist(Min_size, Max_size);
//     std::uniform_int_distribution<> value_dist(Min_value, Max_value);
    
//     int size = size_dist(gen);
//     std::vector<int> arr(size);
    
//     for (int i = 0; i < size; i++) {
//         arr[i] = value_dist(gen);
//     }
    
//     std::cout << "Размер массива: " << size << std::endl;
//     std::cout << "Массив: ";
//     for (int x : arr) {
//         std::cout << x << " ";
//     }
//     std::cout << std::endl;
    
//     return 0;
// }

// //3.Заполнить массив случайным образом нулями и единицами так, чтобы количество 
// //единиц было в точности равно количеству нулей. 

// int main(int argc, char* argv[]) {
//     int n;
    
//     if (argc > 1) {
//         n = stoi(argv[1]);
//     } else {
//         cout << "Введите размер (четный): ";
//         cin >> n;
//     }
    
//     if (n % 2 != 0) {
//         cout << "Размер должен быть четным!" << endl;
//         return 1;
//     }
    
//     vector<int> arr(n);
//     int half = n / 2;
    
//     // Заполняем половину единицами, половину нулями
//     for (int i = 0; i < half; i++) {
//         arr[i] = 1;
//     }
//     for (int i = half; i < n; i++) {
//         arr[i] = 0;
//     }
    
//     // Перемешиваем
//     random_device rd;
//     mt19937 gen(rd());
//     shuffle(arr.begin(), arr.end(), gen);
    
//     cout << "Массив 0 и 1: ";
//     for (int x : arr) {
//         cout << x << " ";
//     }
//     cout << endl;
    
//     return 0;
// }

// //4.Дан массив A из 2n элементов. Вычислить A1−A2 + A3−A4 + … +A2n−1 + A2n. 

// int main(int argc, char* argv[]) {
//     vector<int> A;
    
//     if (argc > 1) {
//         for (int i = 1; i < argc; i++) {
//             A.push_back(stoi(argv[i])); //добавление в конец списка
//         }
//     } else {
//         cout << "Введите элементы массива (четное количество: ";
//         int x;
//         while (cin >> x) {
//             A.push_back(x);
//         }
//     }
    
//     if (A.size() % 2 != 0) {
//         cout << "Количество элементов должно быть четным!" << endl;
//         return 1;
//     }
    
//     int sum = 0;
//     for (int i = 0; i < A.size(); i += 2) {
//         sum += A[i] - A[i + 1];
//     }
    
//     cout << "Результат: " << sum << endl;
    
//     return 0;
// }

// //5.Дан массив и число p. Найти два различных числа в массиве, сумма которых наиболее близка к p. 


// //6.Дан массив чисел. Заменить каждый элемент с чётным индексом на соседний слева элемент. 

// int main(int argc, char* argv[]) {
//     vector<int> arr;
    
//     if (argc > 1) {
//         for (int i = 1; i < argc; i++) {
//             arr.push_back(stoi(argv[i]));
//         }
//     } else {
//         cout << "Введите элементы массива: ";
//         int x;
//         while (cin >> x) {
//             arr.push_back(x);
//         }
//     }
    
//     cout << "Исходный массив: ";
//     for (int x : arr) cout << x << " ";
//     cout << endl;
    
//     for (int i = 2; i < arr.size(); i += 2) {
//         arr[i] = arr[i - 1];
//     }
    
//     cout << "После замены: ";
//     for (int x : arr) cout << x << " ";
//     cout << endl;
    
//     return 0;
// }

// //7.Дан массив. Поменять местами наибольший и наименьший элементы массива. 

// int main(int argc, char* argv[]) {
//     vector<int> arr;
    
//     if (argc > 1) {
//         for (int i = 1; i < argc; i++) {
//             arr.push_back(stoi(argv[i]));
//         }
//     } else {
//         cout << "Введите элементы массива: ";
//         int x;
//         while (cin >> x) {
//             arr.push_back(x);
//         }
//     }
    
//     cout << "Исходный массив: ";
//     for (int x : arr) cout << x << " ";
//     cout << endl;
    
//     auto min_it = min_element(arr.begin(), arr.end());
//     auto max_it = max_element(arr.begin(), arr.end());
    
//     swap(*min_it, *max_it); // смена мест
    
//     cout << "После обмена: ";
//     for (int x : arr) cout << x << " ";
//     cout << endl;
    
//     return 0;
// }

// //8.Даны два массива. Сформировать третий массив, состоящий из тех элементов, которые присутствуют в обоих массивах 

// int main() {
    
//     vector<int> arr1 = {1, 2, 3, 4, 5, 2};
//     vector<int> arr2 = {3, 4, 5, 6, 7, 4};
//     vector<int> common;

//     for (int i = 0; i < arr1.size(); i++) {
//         bool found = false;
//         for (int j = 0; j < arr2.size(); j++) {
//             if (arr1[i] == arr2[j]) {
//                 found = true;
//                 break;
//             }
//         }
        
//         if (found) {
//             bool added = false;
//             for (int k = 0; k < common.size(); k++) {
//                 if (common[k] == arr1[i]) {
//                     added = true;
//                     break;
//                 }
//             }
//             if (!added) {
//                 common.push_back(arr1[i]);
//             }
//         }
//     }

//     cout << "Первый массив: ";
//     for (int x : arr1) cout << x << " ";
//     cout << endl;
    
//     cout << "Второй массив: ";
//     for (int x : arr2) cout << x << " ";
//     cout << endl;
    
//     cout << "Общие элементы: ";
//     for (int x : common) cout << x << " ";
//     cout << endl;
    
//     return 0;
// }