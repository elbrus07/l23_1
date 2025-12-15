#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <format>
using namespace std;

struct Student {
    char surname[50];
    char name[50];
    char fathername[50];
    char birthDate[20];
    char group[20];
    char recordBook[20];
    int course;
};

const char* DATABASE_FILE = "db_stud.dat";

void writeAllStudentsToFile(const vector<Student>& students) {
    ofstream outFile(DATABASE_FILE);
    
    for (const auto& student : students) {
        outFile << student.surname << "|" 
                << student.name << "|" 
                << student.fathername << "|" 
                << student.birthDate << "|" 
                << student.group << "|" 
                << student.recordBook << "|" 
                << student.course << endl;
    }
    
    outFile.close();
}

void writeStudentToFile(const Student& student) {
    ofstream outFile(DATABASE_FILE, ios::app);
    
    
    outFile << student.surname << "|" 
            << student.name << "|" 
            << student.fathername << "|" 
            << student.birthDate << "|" 
            << student.group << "|" 
            << student.recordBook << "|" 
            << student.course << endl;
    
    outFile.close();
    cout << "Студент успешно добавлен в базу данных." << endl;
}

Student parseStudentLine(const char* line) {
    Student student;
    int fieldIndex = 0;
    int startPos = 0;
    int pos = 0;
    
    while (line[pos] != '\0') {
        if (line[pos] == '|' || line[pos] == '\n') {
            int len = pos - startPos;
            if (len > 0) {
                switch(fieldIndex) {
                    case 0: 
                        for (int i = 0; i < len && i < 49; i++) {
                            student.surname[i] = line[startPos + i];
                        }
                        student.surname[len < 49 ? len : 49] = '\0';
                        break;
                    case 1: 
                        for (int i = 0; i < len && i < 49; i++) {
                            student.name[i] = line[startPos + i];
                        }
                        student.name[len < 49 ? len : 49] = '\0';
                        break;
                    case 2: 
                        for (int i = 0; i < len && i < 49; i++) {
                            student.fathername[i] = line[startPos + i];
                        }
                        student.fathername[len < 49 ? len : 49] = '\0';
                        break;
                    case 3: 
                        for (int i = 0; i < len && i < 19; i++) {
                            student.birthDate[i] = line[startPos + i];
                        }
                        student.birthDate[len < 19 ? len : 19] = '\0';
                        break;
                    case 4: 
                        for (int i = 0; i < len && i < 19; i++) {
                            student.group[i] = line[startPos + i];
                        }
                        student.group[len < 19 ? len : 19] = '\0';
                        break;
                    case 5: 
                        for (int i = 0; i < len && i < 19; i++) {
                            student.recordBook[i] = line[startPos + i];
                        }
                        student.recordBook[len < 19 ? len : 19] = '\0';
                        break;
                }
            }
            startPos = pos + 1;
            fieldIndex++;
        }
        pos++;
    }
    
    if (fieldIndex == 6 && startPos < pos) {
        student.course = 0;
        for (int i = startPos; i < pos && line[i] >= '0' && line[i] <= '9'; i++) {
            student.course = student.course * 10 + (line[i] - '0');
        }
    }
    
    return student;
}

vector<Student> readAllStudents() {
    vector<Student> students;
    ifstream inFile(DATABASE_FILE);
    
    if (!inFile.is_open()) {
        cout << "Файл базы данных не найден или не может быть открыт." << endl;
        return students;
    }
    
    char line[256];
    while (inFile.getline(line, 256)) {
        if (line[0] != '\0') {
            students.push_back(parseStudentLine(line));
        }
    }
    
    inFile.close();
    return students;
}

bool compareBySurname(const Student& a, const Student& b) {
    int i = 0;
    while (a.surname[i] != '\0' && b.surname[i] != '\0') {
        if (a.surname[i] != b.surname[i]) {
            return a.surname[i] < b.surname[i];
        }
        i++;
    }
    return a.surname[i] < b.surname[i];
}

bool compareByCourse(const Student& a, const Student& b) {
    return a.course < b.course;
}

bool compareByGroup(const Student& a, const Student& b) {
    int i = 0;
    while (a.group[i] != '\0' && b.group[i] != '\0') {
        if (a.group[i] != b.group[i]) {
            return a.group[i] < b.group[i];
        }
        i++;
    }
    return a.group[i] < b.group[i];
}



void printColumn(const char* text, int width) {
    int textLen = 0;

    while (text[textLen] != '\0') {
        textLen++;
    }
    
    int charsToPrint = textLen < width ? textLen : width;
    for (int i = 0; i < charsToPrint; i++) {
        cout << text[i];
    }
    
    for (int i = 1; i <= width-(charsToPrint/2); i++) {
        cout << " ";
    }
}

void printStudent(const Student& student) {
    printColumn(student.surname, 20);
    printColumn(student.name, 18);
    printColumn(student.fathername, 20);
    printColumn(student.birthDate, 21);
    printColumn(student.group, 10);
    printColumn(student.recordBook, 11);
    cout << student.course;
    cout << endl;
}

void printrow(const Student& student) {
    cout << format("|{:<20}|{:<18}|{:<20}|{:<21}|{:<10}|{:<10}|{:<3}|", student.surname, student.name, student.fathername,student.birthDate,student.group,student.recordBook,student.course)<<"\n";
/*
    printColumn(student.name, 18);
    printColumn(student.fathername, 20);
    printColumn(student.birthDate, 21);
    printColumn(student.group, 10);
    printColumn(student.recordBook, 11);
    cout << student.course;
    cout << endl;
*/    
}

void printHeader() {
    printColumn("Фамилия", 20);
    printColumn("Имя", 18);
    printColumn("Отчество", 20);
    printColumn("Дата рождения", 25);
    printColumn("Группа", 12);
    printColumn("Зачетка", 14);
    printColumn("Курс", 8);
    cout << endl;
    for (int i = 0; i < 114; i++) {
        cout << "-";
    }
    cout << endl;
}

// Запись в файл нового студента

void task1() {
    Student newStudent;
    
    cout << "Введите данные о новом студенте:" << endl;
    cout << "Фамилия: ";
    cin >> newStudent.surname;
    cout << "Имя: ";
    cin >> newStudent.name;
    cout << "Отчество: ";
    cin >> newStudent.fathername;
    cout << "Дата рождения (ДД.ММ.ГГГГ): ";
    cin >> newStudent.birthDate;
    cout << "Группа: ";
    cin >> newStudent.group;
    cout << "Номер зачетки: ";
    cin >> newStudent.recordBook;
    cout << "Курс: ";
    cin >> newStudent.course;
    
    writeStudentToFile(newStudent);
}

// Чтение данных об указанных студентах, 
// в указанном порядке сортировки

void task2() {
    vector<Student> students = readAllStudents();
    
    if (students.empty()) {
        cout << "База данных пуста." << endl;
        return;
    }
    
    int sortOption;
    cout << "Выберите способ сортировки:" << endl;
    cout << "1 - по фамилии" << endl;
    cout << "2 - по курсу" << endl;
    cout << "3 - по группе" << endl;
    cout << "Ваш выбор: ";
    cin >> sortOption;
    
    switch(sortOption) {
        case 1:
            sort(students.begin(), students.end(), compareBySurname);
            break;
        case 2:
            sort(students.begin(), students.end(), compareByCourse);
            break;
        case 3:
            sort(students.begin(), students.end(), compareByGroup);
            break;
        default:
            cout << "Неверный выбор, сортировка по фамилии." << endl;
            sort(students.begin(), students.end(), compareBySurname);
    }
    
    int count;
    cout << "Сколько студентов вывести? (0 - всех): ";
    cin >> count;
    
    if (count <= 0 || count > students.size()) {
        count = students.size();
    }
    
    printHeader();
    for (int i = 0; i < count; i++) {
//        printStudent(students[i]);
        printrow(students[i]);
    }
}

// Подсчет количества студентов

int countStudents() {
    vector<Student> students = readAllStudents();
    return students.size();
}

void task3() {
    int totalCount = countStudents();
    cout << "Общее количество студентов в базе данных: " << totalCount << endl;
}

// Выборка студентов по курсу (select ... where kurs = 1)

vector<Student> selectStudentsByCourse(int course) {
    vector<Student> allStudents = readAllStudents();
    vector<Student> filteredStudents;
    
    for (const auto& student : allStudents) {
        if (student.course == course) {
            filteredStudents.push_back(student);
        }
    }
    
    return filteredStudents;
}

void task4() {
    int targetCourse;
    cout << "Введите курс для выборки: ";
    cin >> targetCourse;
    
    vector<Student> filteredStudents = selectStudentsByCourse(targetCourse);
    
    if (filteredStudents.empty()) {
        cout << "Студенты " << targetCourse << " курса не найдены." << endl;
        return;
    }
    
    cout << "\nСтуденты " << targetCourse << " курса:" << endl;
    printHeader();
    for (const auto& student : filteredStudents) {
        printStudent(student);
    }
    cout << "\nВсего найдено: " << filteredStudents.size() << " студент(ов)" << endl;
}

// Удаление студента по номеру зачетки

bool compareRecordBook(const Student& student, const char* recordBook) {
    int i = 0;
    while (student.recordBook[i] != '\0' && recordBook[i] != '\0') {
        if (student.recordBook[i] != recordBook[i]) {
            return false;
        }
        i++;
    }
    return student.recordBook[i] == recordBook[i];
}

void task5() {
    vector<Student> students = readAllStudents();
    
    if (students.empty()) {
        cout << "База данных пуста." << endl;
        return;
    }
    
    cout << "\nТекущий список студентов:" << endl;
    printHeader();
    for (int i = 0; i < students.size(); i++) {
        cout << (i + 1) << ". ";
        printStudent(students[i]);
    }
    
    char recordBook[20];
    cout << "\nВведите номер зачетки студента для удаления: ";
    cin >> recordBook;
    
    bool found = false;
    vector<Student> updatedStudents;
    
    for (const auto& student : students) {
        if (!compareRecordBook(student, recordBook)) {
            updatedStudents.push_back(student);
        } else {
            found = true;
        }
    }
    
    if (!found) {
        cout << "Студент с номером зачетки " << recordBook << " не найден." << endl;
        return;
    }
    
    writeAllStudentsToFile(updatedStudents);
    cout << "Студент с номером зачетки " << recordBook << " успешно удален." << endl;
    cout << "Осталось студентов: " << updatedStudents.size() << endl;
}

void displayMenu() {
    cout << "\n=== Работа с базой данных студентов ===" << endl;
    cout << "1. Просмотр студентов (с сортировкой)" << endl;
    cout << "2. Добавить нового студента" << endl;
    cout << "3. Удаление студента" << endl;
    cout << "4. Выборка студентов по курсу" << endl;
    cout << "5. Подсчет количества студентов" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                task2();
                break;
            case 2:
                task1();
                break;
            case 3:
                task5();
                break;
            case 4:
                task4();
                break;
            case 5:
                task3();
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while(choice != 0);
    
    return 0;
}

