#include <iostream>
#include <string>
/*
Реализуйте функцию для выполнения простейшего сжатия строк с использованием счетчика повторяющихся символов.
Например, строка ааbсссссааа превращается в а2b1с5а3. Если сжатая строка не становится короче исходной,
то метод возвращает исходную строку. Предполагается, что строка состоит только из букв верхнего и нижнего регистра (a-z)
*/
/*
int main() {
    int k = 0;
    int dig = 1;
    std::string s;
    std::cout << "Введите строку ";
    std::cin >> s;
    std::string news("");

    for (char c : s) {
        k++;
    }
    for (int counter{ 0 }; k-1 >= counter; counter++) {
        if (s[counter] == s[counter + 1]) {
            dig++;
        }
        else if (s[counter] != s[counter + 1]) {
            news += s[counter] + std::to_string(dig);
            dig = 1;
        }
    }
    news.pop_back();
    std::cout << news;
    return 0;
}
*/

//int main() {
//    int a = 1234;
//    int k = 0;
//    std::string s(std::to_string(1234));
//    std::string news("");
//    for (char c: s) {
//        k++;
//    }
//    for (int i{ 1 }; k >= i; i++) {
//        switch (k) {
//        case 1:
//            news = news
//        }
//    }
//    return 0;
//}

/*
Для двух строк напишите метод, определяющий,
является ли одна строка перестановкой другой
*/
int main() {
    setlocale(LC_ALL, "RU");
    std::string s1, s2;
    std::cout << "Введите первую строку ";
    std::cin >> s1;
    std::cout << "Введите вторую строку ";
    std::cin >> s2;

    int ks1 = 0;
    int ks2 = 0;


    for (char a : s1) {
        ks1++;
    }


    for (char a : s2) {
        ks2++;
    }


    if (ks1 != ks2) {
        std::cout << "Строки не являются перестановками ";
        return 0;
    }

    for (int i = 0; i < ks1; i++) {
        bool k = false;
        for (int j = 0; j < (int)s2.size(); j++) {
            if (s1[i] == s2[j]) {
                s2.erase(j, 1); 
                k = true;
                break;
            }
        }
        if (k==false) {
            std::cout << "Строки не являются перестановками ";
            return 0;
        }
    }

    
    if (s2.empty()) {
        std::cout << "Строки являются перестановками";
    }
    else {
        std::cout << "Строки не являются перестановками";
    }

    return 0;
}
