#include <iostream>
#include <string>
using namespace std;

// Сжатие строк с использованием счетчика повторяющихся символов
void compress_string() {
    string s;
    cin >> s;
    string result = "";
    int n = s.length();
    
    for (int i = 0; i < n; i++) {
        char current = s[i];
        int count = 1;
        while (i + 1 < n && s[i + 1] == current) {
            count++;
            i++;
        }
        result += current;
        result += to_string(count);
    }
    if (result.length() >= n) {
        cout << s << endl;
    } else {
        cout << result << endl;
    }
}

// Вывести число в текстовом виде
void number_to_text() {
    int n;
    cin >> n;
    
    string ones[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    string hundreds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    
    if (n == 0) {
        cout << "ноль" << endl;
        return;
    }
    
    if (n < 0) {
        cout << "минус ";
        n = -n;
    }
    
    if (n >= 1000) {
        int thousands = n / 1000;
        
        if (thousands >= 100) {
            cout << hundreds[thousands / 100] << " ";
            thousands = thousands % 100;
        }
        if (thousands >= 20) {
            cout << tens[thousands / 10] << " ";
            thousands = thousands % 10;
        } else if (thousands >= 10) {
            cout << teens[thousands - 10] << " ";
            thousands = 0;
        }
        
        if (thousands == 1) {
        	cout << "одна тысяча ";
        }else if (thousands == 2) {
        	cout << "две тысячи ";
        }else if (thousands >= 3 && thousands <= 4){
        	cout << ones[thousands] << " тысячи ";
        }else if (thousands > 0){
        	cout << ones[thousands] << " тысяч ";
        }else {
        	cout << "тысяч ";
        }
        n = n % 1000;
    }
    
    if (n >= 100) {
        cout << hundreds[n / 100] << " ";
        n = n % 100;
    }
    
    if (n >= 20) {
        cout << tens[n / 10] << " ";
        n = n % 10;
    } else if (n >= 10) {
        cout << teens[n - 10] << " ";
        n = 0;
    }
    
    if (n > 0) {
        cout << ones[n] << " ";
    }
    
    cout << endl;
}

//  Проверить, является ли одна строка перестановкой другой
void is_permutation() {
    string s1, s2;
    cin >> s1 >> s2;
    
    if (s1.length() != s2.length()) {
        cout << "false" << endl;
        return;
    }
    
    string s2_copy = s2;
    for (int i = 0; i < s1.length(); i++) {
        bool found = false;
        for (int j = 0; j < s2_copy.length(); j++) {
            if (s1[i] == s2_copy[j]) {
                s2_copy.erase(j, 1);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "false" << endl;
            return;
        }
    }
    cout << "true" << endl;
}

int main() {
	//	is_permutation();
	//compress_string();
	//number_to_text();
}
