
#include <iostream>
#include <cmath>

int main() {

  /*1.	Для введённого пользователем целого числа
  выдать максимальную цифру, минимальную цифру и их произведение*/

  /* 
    int num;
    int max = -1;
    int min = 10;
    int digit;
    int i;

    std::cout << "Введите число: ";
    std::cin >> num;
    
    for (i = abs(num); i > 0; i /= 10) {
      digit = i % 10;
        
      if (digit > max) max = digit;
      if (digit < min) min = digit;
    }
    std::cout << "(цикл for)Наибольшая цифра в числе: " << max << ", наименьшая цифра в числе: " << min << ", Произведение: " << max * min << "\n";

    max = -1;
    min = 10;
    i = abs(num);
    while (i > 0) {
      digit = i % 10;

      if (digit > max) max = digit;
      if (digit < min) min = digit;
      i /= 10;
    }
    std::cout << "(цикл while)Наибольшая цифра в числе: " << max << ", наименьшая цифра в числе: " << min << ", Произведение: " << max * min << "\n";
    max = -1;
    min = 10;
    i = abs(num);
    do {
      digit = i % 10;

      if (digit > max) max = digit;
      if (digit < min) min = digit;
      i /= 10;
    } while (i > 0);
    std::cout << "(цикл while do)Наибольшая цифра в числе: " << max << ", наименьшая цифра в числе: " << min << ", Произведение: " << max * min;
  */

  /*2.	Последовательность содержит некоторое количество натуральных чисел
  и заканчивается числом 0 (0 не является элементом последовательности).
  Найти сумму вех элементов последовательности*/



  /*3.	Дано целое число. Удалить из него заданную цифру.
  Например, если задано 1464235 и цифра 4, то должно получиться 16235.*/

  /*

  int num;
  int del;
  int i;
  int j = 1;
  int dig;
  int result = 0;

  std:: cout << "Введите число и цифру, которую нужно удалить: ";
  std:: cin >> num >> del;

  for (i = abs(num); i > 0; i /= 10) {
    dig = i % 10;
    if (dig != del) {
      result += dig * j;
      j *= 10;
    }
  }

  std:: cout << "Результат (цикл for): " << result << "\n";


  j = 1;
  result = 0;
  i = abs(num);

  while(i > 0) {
    dig = i % 10;

    if (dig != del) {
      result += dig * j;
      j *= 10;
    }

    i /= 10;
  }

  std:: cout << "Результат (цикл while): " << result << "\n";


  j = 1;
  result = 0;
  i = abs(num);

  do {
    dig = i % 10;      

    if (dig != del) {  
      result += dig * j;
      j *= 10;
    }

    i /= 10;
  }
  while (i > 0);

  std:: cout << "Результат (цикл while do): " << result << "\n";

  */

  /*4.	Для каждого натурального числа в промежутке от N до M вывести все делители,
  кроме единицы и самого числа. Значения N и M вводятся с клавиатуры.*/

  /*

  int N;
  int M;
  int i;
  int j;

  std:: cout << ": ";
  std:: cin >> N >> M;

  for (i = N; i <= M; i += 1) {
    std:: cout << "Делители числа " << i << " :\n";
    for (j = 2; j < i; j += 1) {
      if (i % j == 0) {
        std:: cout << j << " ";
      }
    }
    std:: cout << "\n";
  }

  i = N;

  std:: cout << "цикл while" << "\n";

  while (i <= M) {
    j = 2;
    std:: cout << "Делители числа " << i << " :\n";
    while (j < i) {
      if (i % j == 0) {
        std:: cout << j << " ";
      }
      j += 1;
    }
    i += 1;
    std:: cout << "\n";
  }

  i = N;

  std::cout << "цикл do while\n";

  do {
      j = 2;
      std::cout << "Делители числа " << i << " : ";
      
      if (i >= 2) {
          do {
              if (i % j == 0) {
                  std::cout << j << " ";
              }
              j += 1;
          }
          while (j < i);
      }
      
      std::cout << "\n";
      i += 1;
  } while (i <= M);

*/

  /*5.	Вывести на экран двумерную таблицу умножения.*/

/*

  int number;
  int result;
  int i;
  int j;

  std:: cout << "Введите число, до которого нужно составить таблицу (таблица квадратная): ";
  std:: cin >> number;

  for (i = 1; i <= number; i += 1) {
    for (j = 1; j <= number; j += 1) {
      result = i * j;

      if (result < 10) {
        std:: cout << "   " << result;
      }
      else if (result < 100) {
        std:: cout << "  " << result;
      }
      else if (result < 1000) {
        std:: cout << " " << result;
      }
      else {
        std:: cout <<  result;
      }
      std :: cout << " ";
    }
    std :: cout << "\n";
  }

  std :: cout << "while" << "\n";

  i = 1;
  j = 1;

  while (i <= number) {
    while (j <= number) {
      result = i * j;
      if (result < 10) {
        std:: cout << "   " << result;
      }
      else if (result < 100) {
        std:: cout << "  " << result;
      }
      else if (result < 1000) {
        std:: cout << " " << result;
      }
      else {
        std:: cout <<  result;
      }
      std :: cout << " ";
      j += 1;
    }
    j = 1;
    i += 1;
    std :: cout << "\n";
  }

  std :: cout << "while do" << "\n";

  i = 1;
  j = 1;

  do {
      do {
          result = i * j;
          if (result < 10) std::cout << "   " << result;
          else if (result < 100) std::cout << "  " << result;
          else if (result < 1000) std::cout << " " << result;
          else std::cout << result;
          std::cout << " ";
          j += 1;
      } while (j <= number);
      std :: cout << "\n"; 
      i += 1;
      j = 1;
  }
  while (i <= number);

*/

  return 0;
}