#include <iostream>
#include <string>
#include <vector>
using namespace std;

//1. Реализуйте функцию для выполнения простейшего сжатия строк с использованием счетчика 
//повторяющихся символов. Например, строка ааbсссссааа превращается в а2b1с5а3. Если сжатая
// строка не становится короче исходной, то метод возвращает исходную строку. Предполагается, 
//что строка состоит только из букв верхнего и нижнего регистра (a-z) 

// string compress(string str) {
//     if (str.length() == 0) {
//         return str;
//     }
    
//     string compress_str;
//     char current = str[0];
//     int count = 1;
//     int n = str.length();
    
//     for (int i = 1; i < n; i++) {
//         if (str[i] == current) {
//             count++;
//         } else {
//             compress_str += current;
//             compress_str += to_string(count);
            
//             current = str[i];
//             count = 1;
//         }
//     }
    
//     compress_str += current;
//     compress_str += to_string(count);
    
//     if (compress_str.length() >= str.length()) {
//         compress_str = str;
//     }
    
//     return compress_str
//     ;
// }

// int main() {
//     string input;
//     cout << "Введите строку: ";
//     cin >> input;
    
//     string result = compress(input);
//     cout << "Результат: " << result << endl;
    
//     return 0;
// }


//2. Задано целое число. Выведите его значение в текстовом виде
// (например, одна тысяча двести тридцать четыре). 

// string numbertotext(int num) {
//     if (num == 0) return "ноль";
//     if (num < 0) return "минус " + numbertotext(-num);
    
//     vector<string> units = {"", "один", "два", "три", "четыре", "пять", 
//                            "шесть", "семь", "восемь", "девять"};
//     vector<string> teens = {"десять", "одиннадцать", "двенадцать", "тринадцать",
//                            "четырнадцать", "пятнадцать", "шестнадцать",
//                            "семнадцать", "восемнадцать", "девятнадцать"};
//     vector<string> tens = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят",
//                           "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
//     vector<string> hundreds = {"", "сто", "двести", "триста", "четыреста",
//                               "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    
//     string result;
    
//     if (num >= 1000) {
//         int thousands = num / 1000;
//         if (thousands == 1) result += "одна тысяча ";
//         else if (thousands == 2) result += "две тысячи ";
//         else if (thousands >= 3 && thousands <= 4) result += units[thousands] + " тысячи ";
//         else result += units[thousands] + " тысяч ";
//         num %= 1000;
//     }
    
//     if (num >= 100) {
//         result += hundreds[num / 100] + " ";
//         num %= 100;
//     }
    
//     if (num >= 20) {
//         result += tens[num / 10] + " ";
//         num %= 10;
//         if (num > 0) result += units[num] + " ";
//     } else if (num >= 10) {
//         result += teens[num - 10] + " ";
//     } else if (num > 0) {
//         result += units[num] + " ";
//     }
    
//     return result;
// }

// int main(int argc, char* argv[]) {
//     int number;
    
//     if (argc > 1) {
//         number = stoi(argv[1]); // преобразует строку в число
//         cout << "Число из аргументов: " << number << endl;
//     } else {
//         cout << "Введите число: ";
//         cin >> number;
//     }
    
//     string result = numbertotext(number);
//     cout << "Текстовая форма: " << result << endl;
    
//     return 0;
// }

//3. Для двух строк напишите метод, определяющий, является ли одна строка перестановкой другой 

// bool isPermutationSimple(string str1, string str2) {

//     if (str1.length() != str2.length()) {
//         return false;
//     }
    
//     int count[256] = {0};  // для всех ASCII символов
    
//     for (int i = 0; i < str1.length(); i++) {
//         count[str1[i]]++;
//     }
    
//     for (int i = 0; i < str2.length(); i++) {
//         count[str2[i]]--;
//         if (count[str2[i]] < 0) {
//             return false;
//         }
//     }
    
//     return true;
// }

// int main() {
//     string s1, s2;
//     cout << "Введите две строки: ";
//     cin >> s1 >> s2;
    
//     if (isPermutationSimple(s1, s2)) {
//         cout << "Это перестановка" << endl;
//     } else {
//         cout << "Это не перестановка" << endl;
//     }
    
//     return 0;
// }