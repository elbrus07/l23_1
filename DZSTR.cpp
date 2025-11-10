#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Сжатие строки
void compress_string() {
    string s;
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
    
    cout << (result.length() < s.length() ? result : s) << endl;
}

// Число в текст
void number_to_text() {
    int n;
    cin >> n;
    
    if (n == 0) {
        cout << "ноль" << endl;
        return;
    }
    
    string ones[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", 
                     "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    string hundreds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    
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

// Проверка перестановки
void is_permutation() {
    string s1, s2;
    cin >> s1 >> s2;
    
    if (s1.length() != s2.length()) {
        cout << "false" << endl;
        return;
    }
    
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    
    cout << (s1 == s2 ? "true" : "false") << endl;
}

int main() {
    return 0;
}
