#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// Функция добавления студента
// studentSurname Фамилия студента
// studentName Имя студента
// studentMiddlename Отчество студента
// studentBirthDate Дата рождения (формат: ДД.ММ.ГГГГ)
// studentGroup Номер группы (например: ИВТ-101)
// studentRecordBook Номер зачетной книжки
// studentCourse Номер курса (от 1 до 5)
// Эта функция открывает файл db_stud.dat в режиме добавления (ios::app)
// и записывает данные студента в конец файла через пробелы.

void addStudent(string studentSurname, string studentName, string studentMiddlename, 
                string studentBirthDate, string studentGroup, string studentRecordBook, int studentCourse) {
    ofstream outputFile("db_stud.dat", ios::app);
    if (outputFile.is_open()) {
        outputFile << studentSurname << " " << studentName << " " << studentMiddlename << " "
                   << studentBirthDate << " " << studentGroup << " " << studentRecordBook << " " 
                   << studentCourse << endl;
        outputFile.close();
        cout << "Студент добавлен!" << endl;
    } else {
        cout << "Ошибка открытия файла!" << endl;
    }
}


// Эта функция открывает файл db_stud.dat для чтения,
// считывает данные всех студентов и выводит их на экран с порядковым номером.
// Использует оператор >> для чтения данных до пробелов.

int showAllStudents() {
    ifstream inputFile("db_stud.dat");
    if (!inputFile.is_open()){
        return -1;
    }
    string currentSurname, currentName, currentMiddlename, currentBirthDate, currentGroup, currentRecordBook;
    int currentCourse, studentCounter = 0;
    
    while (inputFile >> currentSurname >> currentName >> currentMiddlename >> currentBirthDate 
                     >> currentGroup >> currentRecordBook >> currentCourse) {
        studentCounter++;
        cout << studentCounter << ". " << currentSurname << " " << currentName << " " 
             << currentMiddlename << " - Группа: " << currentGroup 
             << ", Курс: " << currentCourse << endl;
    }
    inputFile.close();
    return studentCounter;
}


// Функция поиска студентов по курсу
// targetCourse Курс для поиска (от 1 до 5)
// Эта функция открывает файл db_stud.dat для чтения,
// считывает данные всех студентов и проверяет их курс.
// Выводит только тех студентов, чей курс совпадает с targetCourse.
void findStudentsByCourse(int targetCourse) {
    ifstream inputFile("db_stud.dat");
    if (inputFile.is_open()) {
        string currentSurname, currentName, currentMiddlename, currentBirthDate, currentGroup, currentRecordBook;
        int currentCourse, foundCount = 0;
        
        while (inputFile >> currentSurname >> currentName >> currentMiddlename >> currentBirthDate 
                         >> currentGroup >> currentRecordBook >> currentCourse) {
            if (currentCourse == targetCourse) {
                foundCount++;
                cout << foundCount << ". " << currentSurname << " " << currentName 
                     << " " << currentMiddlename << " - Группа: " << currentGroup << endl;
            }
        }
        inputFile.close();
        
        if (foundCount == 0) {
            cout << "Студентов на " << targetCourse << " курсе не найдено" << endl;
        }
    } else {
        cout << "Файл не найден" << endl;
    }
}


// Функция подсчета количества студентов
// подсчитывает все непустые строки в файле.
// Каждая непустая строка соответствует одному студенту.
// Возвращает общее количество студентов в файле.

int countStudents() {
    ifstream inputFile("db_stud.dat");
    if (inputFile.is_open()) {
        int totalCount = 0;
        string fileLine;
        
        while (getline(inputFile, fileLine)) {
            if (!fileLine.empty()) {
                totalCount++;
            }
        }
        inputFile.close();
        return totalCount;
    } else {
        cout << "Файл не найден" << endl;
        return 0;
    }
}

int main() {
    int userChoice;
    string inputSurname, inputName, inputMiddlename, inputBirthDate, inputGroup, inputRecordBook;
    int inputCourse, searchTargetCourse;
    
    while (true) {
        cout << "\n1. Добавить студента" << endl;
        cout << "2. Показать всех студентов" << endl;
        cout << "3. Найти студентов по курсу" << endl;
        cout << "4. Посчитать студентов" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите: ";
        cin >> userChoice;
        
        if (userChoice == 0) break;
        
        if (userChoice == 1) {
            cout << "Фамилия: "; cin >> inputSurname;
            cout << "Имя: "; cin >> inputName;
            cout << "Отчество: "; cin >> inputMiddlename;
            cout << "Дата рождения: "; cin >> inputBirthDate;
            cout << "Группа: "; cin >> inputGroup;
            cout << "Зачетка: "; cin >> inputRecordBook;
            cout << "Курс: "; cin >> inputCourse;
            
            addStudent(inputSurname, inputName, inputMiddlename, inputBirthDate, inputGroup, inputRecordBook, inputCourse);
        }
        else if (userChoice == 2) {
            showAllStudents();
        }
        else if (userChoice == 3) {
            cout << "Введите курс для поиска: ";
            cin >> searchTargetCourse;
            findStudentsByCourse(searchTargetCourse);
        }
        else if (userChoice == 4) {
            int totalStudents = countStudents();
            cout << "Всего студентов: " << totalStudents << endl;
        }
    }
    
    return 0;
}