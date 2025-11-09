#include <iostream>
#include <string>


std :: string compress(std::string str) {
  if (str.length() == 0) {
    return str;
  }
  std :: string compressed_stroke;
  std :: string letter_name = str.substr(0, 1);
  int count = 1;
  int i;

  for (i = 1; i <= str.length(); i += 1) { 
    if (i < str.length() and str[i] == letter_name[0]) {
      count += 1; }
    else {
      compressed_stroke += letter_name;
      compressed_stroke += std :: to_string(count);

      if (i < str.length()) {
        letter_name = str.substr (i, 1);
        count = 1;
      }
    }      
  }

  if (compressed_stroke.length() >= str.length()) {
    compressed_stroke = str;
  }
  return compressed_stroke;
}

//для 2-го задания

std :: string compress_all(std::string str) {
  if (str.length() == 0) {
    return str;
  }
  std :: string compressed_stroke;
  std :: string letter_name = str.substr(0, 1);
  int count;
  int i;
  int j;
  char letter;

  for (i = 1; i <= str.length(); i += 1) { 
    letter = str[i];
    count = 1;
    if (i < str.length() and str[i] == letter_name[0]) {
      count += 1; }
    else {
      compressed_stroke += letter_name;
      compressed_stroke += std :: to_string(count);

      if (i < str.length()) {
        letter_name = str.substr (i, 1);
        count = 1;
      }
    }      
  }

  return compressed_stroke;
}



int isperestanovka (std :: string str1, std :: string str2) {
  int i;
  int j;
  char letter1;
  char number1;
  int flag;
  if (str1.length() != str2.length()) {
    return 0;
  }
  
  std :: string stroke1_elements = compress_all(str1);
  std :: string stroke2_elements = compress_all(str2);

  for (i = 0; i < stroke1_elements.length(); i += 2) {
    letter1 = stroke1_elements[i];
    number1 = stroke1_elements[i + 1];
    flag = 0;
    
    
    for (j = 0; j < stroke2_elements.length(); j +=2) {
      if (stroke2_elements[j] == letter1 and stroke2_elements[j + 1] == number1) {
        flag = 1;
        break;
      }
    }
  
    if (flag == 0) {
      return 0;
    }
  }

  return 1;
}

int main() {
  /*1.	Реализуйте функцию для выполнения простейшего сжатия строк с
   использованием счетчика повторяющихся символов. Например, строка
    ааbсссссааа превращается в а2b1с5а3. Если сжатая строка не 
    становится короче исходной, то метод возвращает исходную строку.
     Предполагается, что строка состоит только из букв верхнего и 
     нижнего регистра (a-z)*/

/*

  std :: string strr;

  std :: cout << "Введите любую строку: ";
  std :: cin >> strr;

  std :: string result = compress(strr);
  std::cout << "Результат: " << result;

*/

  /*2.	Задано целое число. Выведите его значение в текстовом виде
  (например, одна тысяча двести тридцать четыре).*/



  std :: string string1;
  std :: string string2;
  std :: string result1;
  int result;
  std::cout << "Введите первую строку и через пробел вторую: ";
  std::cin >> string1 >> string2;

  result = isperestanovka(string1, string2);
  if (result == 1) {
    std :: cout << "Yes";
    }
  else {
    std :: cout << "No";
  }


  /*3.	Для двух строк напишите метод, определяющий, является ли одна строка
  перестановкой другой*/

  

    return 0;
}