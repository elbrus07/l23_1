#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 1. Сжатие строки
void compress_string() {
    string s;
    cout << "Введите строку для сжатия: ";
    cin >> s;
    
    string compressed = "";
    int count = 1;
    
    for (int i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && s[i] == s[i + 1]) {
            count++;
        } else {
            
            compressed += s[i];
            compressed += to_string(count);
            count = 1; 
        }
    }
    
   
    if (compressed.length() < s.length()) {
        cout << "Сжатая строка: " << compressed << endl;
    } else {
        cout << "Исходная строка: " << s << " (сжатие не эффективно)" << endl;
    }
}

// 2. Число в текстовом виде
void number_to_text() {
    int n;
    cout << "Введите число: ";
    cin >> n;
    
    
    if (n == 0) {
        cout << "ноль" << endl;
        return;
    }
    
    // массивы
    string ones[] = {"", "один", "два", "три", "четыре", "пять", 
                    "шесть", "семь", "восемь", "девять"};
    string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", 
                     "четырнадцать", "пятнадцать", "шестнадцать", 
                     "семнадцать", "восемнадцать", "девятнадцать"};
    string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", 
                    "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    string hundreds[] = {"", "сто", "двести", "триста", "четыреста", 
                        "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    
    string result = "";
    
    
    if (n < 0) {
        result += "минус ";
        n = -n;
    }
    
    int original_n = n; 
    
  
    if (n >= 1000) {
        int thousands = n / 1000;
        
       
        if (thousands >= 100) {
            result += hundreds[thousands / 100] + " ";
            thousands %= 100;
        }
        
       
        if (thousands >= 20) {
            result += tens[thousands / 10] + " ";
            thousands %= 10;
        } else if (thousands >= 10) {
            result += teens[thousands - 10] + " ";
            thousands = 0;
        }
        
     
        if (thousands == 1) {
            result += "одна тысяча ";
        } else if (thousands == 2) {
            result += "две тысячи ";
        } else if (thousands == 3 || thousands == 4) {
            result += ones[thousands] + " тысячи ";
        } else if (thousands > 0) {
            result += ones[thousands] + " тысяч ";
        } else if (n >= 1000) {
            result += "тысяч ";
        }
        
        n %= 1000; 
    }
    

    if (n >= 100) {
        result += hundreds[n / 100] + " ";
        n %= 100;
    }
    

    if (n >= 20) {
        result += tens[n / 10] + " ";
        n %= 10;
    } else if (n >= 10) {
        result += teens[n - 10] + " ";
        n = 0;
    }
    

    if (n > 0) {
        result += ones[n];
    }
    

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    
    cout << original_n << " = " << result << endl;
}

// 3. Проверка перестановки строк
void is_permutation() {
    string s1, s2;
    cout << "Введите две строки для проверки: ";
    cin >> s1 >> s2;
    
    // Быстрая проверка по длине
    if (s1.length() != s2.length()) {
        cout << "Результат: false (разная длина)" << endl;
        return;
    }
    
    // создаем копии и сортируем символы
    string sorted_s1 = s1;
    string sorted_s2 = s2;
    
    sort(sorted_s1.begin(), sorted_s1.end());
    sort(sorted_s2.begin(), sorted_s2.end());
    
    // сравниваем отсортированные строки
    if (sorted_s1 == sorted_s2) {
        cout << "Результат: true (строки являются перестановками)" << endl;
    } else {
        cout << "Результат: false (строки не являются перестановками)" << endl;
    }
}

// менюшка
int main() {
    int choice;
    
    do {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Сжатие строки" << endl;
        cout << "2. Число в текстовом виде" << endl;
        cout << "3. Проверка перестановки строк" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите задание: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                compress_string();
                break;
            case 2:
                number_to_text();
                break;
            case 3:
                is_permutation();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
