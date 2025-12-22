#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const string FILE_NAME = "db_stud.dat";

struct Student {
    string fam;
    string name;
    string otch;
    string birth;
    string group;
    string recordBook;
    int kurs;
};

/* Разбор строки из файла */
Student parseStudent(const string& line) {
    Student s;
    string temp;
    stringstream ss(line);

    getline(ss, s.fam, '#');
    getline(ss, s.name, '#');
    getline(ss, s.otch, '#');
    getline(ss, s.birth, '#');
    getline(ss, s.group, '#');
    getline(ss, s.recordBook, '#');
    getline(ss, temp);
    s.kurs = stoi(temp);

    return s;
}

/* Запись нового студента */
void addStudent() {
    ofstream file(FILE_NAME, ios::app);
    if (!file) {
        cout << "Ошибка открытия файла\n";
        return;
    }

    Student s;
    cout << "Фамилия: "; cin >> s.fam;
    cout << "Имя: "; cin >> s.name;
    cout << "Отчество: "; cin >> s.otch;
    cout << "Дата рождения (YYYY-MM-DD): "; cin >> s.birth;
    cout << "Группа: "; cin >> s.group;
    cout << "№ зачетки: "; cin >> s.recordBook;
    cout << "Курс: "; cin >> s.kurs;

    file << s.fam << "#"
         << s.name << "#"
         << s.otch << "#"
         << s.birth << "#"
         << s.group << "#"
         << s.recordBook << "#"
         << s.kurs << endl;

    file.close();
    cout << "Студент добавлен\n";
}

/* Чтение всех студентов */
vector<Student> readStudents() {
    ifstream file(FILE_NAME);
    vector<Student> students;
    string line;

    while (getline(file, line)) {
        if (!line.empty())
            students.push_back(parseStudent(line));
    }
    return students;
}

/* Подсчет количества студентов */
void countStudents() {
    ifstream file(FILE_NAME);
    int count = 0;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) count++;
    }
    cout << "Количество студентов: " << count << endl;
}

/* Вывод студентов по курсу с сортировкой */
void selectByKurs(int kurs) {
    vector<Student> students = readStudents();

    /* фильтр */
    vector<Student> result;
    for (auto& s : students) {
        if (s.kurs == kurs)
            result.push_back(s);
    }

    /* сортировка по имени */
    sort(result.begin(), result.end(),[](const Student& a, const Student& b) {
             return a.name < b.name;
         });

    /* вывод */
    for (auto& s : result) {
        cout << s.fam << " "
             << s.name << " "
             << s.otch << " "
             << s.birth << " "
             << s.group << " "
             << s.recordBook << " "
             << s.kurs << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1 - Добавить студента";
        cout << "\n2 - Показать студентов по курсу";
        cout << "\n3 - Подсчитать студентов";
        cout << "\n0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2: {
            int k;
            cout << "Введите курс: ";
            cin >> k;
            selectByKurs(k);
            break;
        }
        case 3:
            countStudents();
            break;
        }
    } while (choice != 0);

    return 0;
}
