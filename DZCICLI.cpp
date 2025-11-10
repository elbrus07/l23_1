#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 1. Максимальная и минимальная цифра числа и их произведение
void max_min_digit() {
    int n;
    cout << "Введите число: ";
    cin >> n;
    
    if (n == 0) {
        cout << "Max: 0, Min: 0, Product: 0" << endl;
        return;
    }
    
    int temp = abs(n);
    int max_digit = temp % 10;
    int min_digit = temp % 10;
    
    while (temp > 0) {
        int digit = temp % 10;
        if (digit > max_digit) max_digit = digit;
        if (digit < min_digit) min_digit = digit;
        temp /= 10;
    }
    
    cout << "Max: " << max_digit << ", Min: " << min_digit 
         << ", Product: " << max_digit * min_digit << endl;
}

// 2. Сумма последовательности до 0
void sum_sequence() {
    int sum = 0, num;
    cout << "Введите последовательность чисел (0 для окончания): ";
    
    cin >> num;
    while (num != 0) {
        sum += num;
        cin >> num;
    }
    
    cout << "Sum: " << sum << endl;
}

// 3. Удалить заданную цифру из числа
void remove_digit() {
    int n, digit;
    cout << "Введите число и цифру для удаления: ";
    cin >> n >> digit;
    
    if (n == 0) {
        cout << "Result: " << (digit == 0 ? 0 : n) << endl;
        return;
    }
    
    int result = 0, multiplier = 1;
    int temp = abs(n);
    
    while (temp > 0) {
        int d = temp % 10;
        if (d != digit) {
            result += d * multiplier;
            multiplier *= 10;
        }
        temp /= 10;
    }
    
    if (n < 0) result = -result;
    cout << "Result: " << result << endl;
}

// 4. Делители чисел от N до M
void find_divisors() {
    int N, M;
    cout << "Введите N и M: ";
    cin >> N >> M;
    
    for (int i = N; i <= M; i++) {
        cout << i << ": ";
        bool found = false;
        
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                if (found) cout << ", ";
                cout << j;
                found = true;
            }
        }
        
        if (!found) cout << "none";
        cout << endl;
    }
}

// 5. Таблица умножения
void mult_table() {
    cout << "Таблица умножения:" << endl;
    
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            cout << i * j << "\t";
        }
        cout << endl;
    }
}

// 6. Сжатие строки (дополнительная функция)
void compress_string() {
    string s;
    cout << "Введите строку для сжатия: ";
    cin >> s;
    
    string result = "";
    
    for (int i = 0; i < s.length(); ) {
        char current = s[i];
        int count = 0;
        
        while (i < s.length() && s[i] == current) {
            count++;
            i++;
        }
        
        result += current;
        result += to_string(count);
    }
    
    cout << "Result: " << (result.length() < s.length() ? result : s) << endl;
}

// 7. Число в текстовом виде (дополнительная функция)
void number_to_text() {
    int n;
    cout << "Введите число: ";
    cin >> n;
    
    if (n == 0) {
        cout << "ноль" << endl;
        return;
    }
    
    string ones[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", 
                     "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", 
                    "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    string hundreds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот", 
                        "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    
    if (n < 0) {
        cout << "минус ";
        n = -n;
    }
    
    // Тысячи
    if (n >= 1000) {
        int th = n / 1000;
        
        if (th >= 100) {
            cout << hundreds[th / 100] << " ";
            th %= 100;
        }
        if (th >= 20) {
            cout << tens[th / 10] << " ";
            th %= 10;
        } else if (th >= 10) {
            cout << teens[th - 10] << " ";
            th = 0;
        }
        
        if (th == 1) cout << "одна тысяча ";
        else if (th == 2) cout << "две тысячи ";
        else if (th == 3 || th == 4) cout << ones[th] << " тысячи ";
        else if (th > 0) cout << ones[th] << " тысяч ";
        else cout << "тысяч ";
        
        n %= 1000;
    }
    
    // Сотни
    if (n >= 100) {
        cout << hundreds[n / 100] << " ";
        n %= 100;
    }
    
    // Десятки и единицы
    if (n >= 20) {
        cout << tens[n / 10] << " ";
        n %= 10;
    } else if (n >= 10) {
        cout << teens[n - 10] << " ";
        n = 0;
    }
    
    if (n > 0) {
        cout << ones[n];
    }
    
    cout << endl;
}

// 8. Проверка перестановки строк (дополнительная функция)
void is_permutation() {
    string s1, s2;
    cout << "Введите две строки: ";
    cin >> s1 >> s2;
    
    if (s1.length() != s2.length()) {
        cout << "false" << endl;
        return;
    }
    
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    
    cout << (s1 == s2 ? "true" : "false") << endl;
}

// Главное меню
void show_menu() {
    cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
    cout << "1. Максимальная и минимальная цифра числа" << endl;
    cout << "2. Сумма последовательности до 0" << endl;
    cout << "3. Удалить цифру из числа" << endl;
    cout << "4. Делители чисел от N до M" << endl;
    cout << "5. Таблица умножения" << endl;
    cout << "6. Сжатие строки" << endl;
    cout << "7. Число в текстовом виде" << endl;
    cout << "8. Проверка перестановки строк" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите задание: ";
}

int main() {
    int choice;
    
    do {
        show_menu();
        cin >> choice;
        
        switch (choice) {
            case 1: max_min_digit(); break;
            case 2: sum_sequence(); break;
            case 3: remove_digit(); break;
            case 4: find_divisors(); break;
            case 5: mult_table(); break;
            case 0: cout << "До свидания!" << endl; break;
            default: cout << "Неверный выбор!" << endl;
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
