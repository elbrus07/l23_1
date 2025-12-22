#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// структура студента
struct Student {
    string surname;
    string name;
    string patronymic;
    string birth;
    string group;
    string recordBook;
    int kurs;
};

// запись нового студента в файл
void addStudent() {
    ofstream file("db_stud.dat", ios::app); // дописываем в конец файла

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    Student s;

    cout << "Фамилия: ";
    cin >> s.surname;
    cout << "Имя: ";
    cin >> s.name;
    cout << "Отчество: ";
    cin >> s.patronymic;
    cout << "Дата рождения (дд.мм.гггг): ";
    cin >> s.birth;
    cout << "Группа: ";
    cin >> s.group;
    cout << "Номер зачетки: ";
    cin >> s.recordBook;
    cout << "Курс: ";
    cin >> s.kurs;

    file << s.surname << " "
         << s.name << " "
         << s.patronymic << " "
         << s.birth << " "
         << s.group << " "
         << s.recordBook << " "
         << s.kurs << endl;

    file.close();
    cout << "Студент успешно добавлен!\n";
}

// чтение всех студентов из файла
vector<Student> readStudents() {
    ifstream file("db_stud.dat");
    vector<Student> students;
    Student s;

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return students;
    }

    while (file >> s.surname >> s.name >> s.patronymic
                >> s.birth >> s.group >> s.recordBook >> s.kurs) {
        students.push_back(s);
    }

    file.close();
    return students;
}

// вывод студентов курса = 1 (select ... where kurs = 1)
void printFirstKurs() {
    vector<Student> students = readStudents();

    cout << "\nСтуденты 1 курса:\n";
    for (auto s : students) {
        if (s.kurs == 1) {
            cout << s.surname << " " << s.name << " "
                 << s.patronymic << " "
                 << s.birth << " "
                 << s.group << " "
                 << s.recordBook << " "
                 << s.kurs << endl;
        }
    }
}

// подсчет количества студентов
void countStudents() {
    vector<Student> students = readStudents();
    cout << "Количество студентов: " << students.size() << endl;
}

// сортировка по фамилии
void sortBySurname() {
    vector<Student> students = readStudents();

    sort(students.begin(), students.end(),
         [](Student a, Student b) {
             return a.surname < b.surname;
         });

    cout << "\nСписок студентов (отсортирован по фамилии):\n";
    for (auto s : students) {
        cout << s.surname << " " << s.name << " "
             << s.patronymic << " "
             << s.birth << " "
             << s.group << " "
             << s.recordBook << " "
             << s.kurs << endl;
    }
}

// главное меню
int main() {
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1 - Добавить студента\n";
        cout << "2 - Показать студентов 1 курса\n";
        cout << "3 - Подсчитать количество студентов\n";
        cout << "4 - Показать студентов (сортировка по фамилии)\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            printFirstKurs();
            break;
        case 3:
            countStudents();
            break;
        case 4:
            sortBySurname();
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }

    } while (choice != 0);

    return 0;
}
