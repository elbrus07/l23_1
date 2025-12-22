#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Функция добавления студента
// surname Фамилия студента
// name Имя студента
// patronymic Отчество студента
// birthDate Дата рождения (формат: ДД.ММ.ГГГГ)
// group Номер группы (например: ИВТ-101)
// recordBook Номер зачетной книжки
// course Номер курса (от 1 до 5)
// Эта функция открывает файл db_stud.dat в режиме добавления (ios::app)
// и записывает данные студента в конец файла через пробелы.
// Каждая строка файла содержит данные одного студента.
void addStudent(string surname, string name, string patronymic, 
                string birthDate, string group, string recordBook, int course) {
    ofstream file("db_stud.dat", ios::app);
    if (file.is_open()) {
        file << surname << " " << name << " " << patronymic << " "
             << birthDate << " " << group << " " << recordBook << " " 
             << course << endl;
        file.close();
        cout << "Студент добавлен!" << endl;
    } else {
        cout << "Ошибка открытия файла!" << endl;
    }
}


// Функция показа всех студентов
// Эта функция открывает файл db_stud.dat для чтения,
// считывает данные всех студентов и выводит их на экран.
// Использует оператор >> для чтения данных до пробелов.
// Выводит порядковый номер каждого студента.
void showAllStudents() {
    ifstream file("db_stud.dat");
    if (file.is_open()) {
        string surname, name, patronymic, birthDate, group, recordBook;
        int course, count = 0;
        
        while (file >> surname >> name >> patronymic >> birthDate 
                   >> group >> recordBook >> course) {
            count++;
            cout << count << ". " << surname << " " << name << " " 
                 << patronymic << " - Группа: " << group 
                 << ", Курс: " << course << endl;
        }
        file.close();
        
        if (count == 0) {
            cout << "Нет студентов в базе" << endl;
        }
    } else {
        cout << "Файл не найден" << endl;
    }
}


// Функция поиска студентов по курсу
// searchCourse Курс для поиска (от 1 до 5)
// Эта функция открывает файл db_stud.dat для чтения,
// считывает данные всех студентов и проверяет их курс.
// Выводит только тех студентов, чей курс совпадает с searchCourse.
void findStudentsByCourse(int searchCourse) {
    ifstream file("db_stud.dat");
    if (file.is_open()) {
        string surname, name, patronymic, birthDate, group, recordBook;
        int course, count = 0;
        
        while (file >> surname >> name >> patronymic >> birthDate 
                   >> group >> recordBook >> course) {
            if (course == searchCourse) {
                count++;
                cout << count << ". " << surname << " " << name 
                     << " " << patronymic << " - Группа: " << group << endl;
            }
        }
        file.close();
        
        if (count == 0) {
            cout << "Студентов на " << searchCourse << " курсе не найдено" << endl;
        }
    } else {
        cout << "Файл не найден" << endl;
    }
}


// Функция подсчета количества студентов
// Эта функция открывает файл db_stud.dat для чтения,
// подсчитывает все непустые строки в файле.
// Каждая непустая строка соответствует одному студенту.
// Возвращает общее количество студентов в файле.
int countStudents() {
    ifstream file("db_stud.dat");
    if (file.is_open()) {
        int count = 0;
        string line;
        
        while (getline(file, line)) {
            if (!line.empty()) {
                count++;
            }
        }
        file.close();
        return count;
    } else {
        cout << "Файл не найден" << endl;
        return 0;
    }
}

int main() {
    int choice;
    string surname, name, patronymic, birthDate, group, recordBook;
    int course, searchCourse;
    
    while (true) {
        cout << "\n1. Добавить студента" << endl;
        cout << "2. Показать всех студентов" << endl;
        cout << "3. Найти студентов по курсу" << endl;
        cout << "4. Посчитать студентов" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        if (choice == 1) {
            cout << "Фамилия: "; cin >> surname;
            cout << "Имя: "; cin >> name;
            cout << "Отчество: "; cin >> patronymic;
            cout << "Дата рождения: "; cin >> birthDate;
            cout << "Группа: "; cin >> group;
            cout << "Зачетка: "; cin >> recordBook;
            cout << "Курс: "; cin >> course;
            
            addStudent(surname, name, patronymic, birthDate, group, recordBook, course);
        }
        else if (choice == 2) {
            showAllStudents();
        }
        else if (choice == 3) {
            cout << "Введите курс для поиска: ";
            cin >> searchCourse;
            findStudentsByCourse(searchCourse);
        }
        else if (choice == 4) {
            int total = countStudents();
            cout << "Всего студентов: " << total << endl;
        }
    }
    
    return 0;
}