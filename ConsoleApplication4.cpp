#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale> 

using namespace std;

struct Student {
    string surname;
    string name;
    string otch;
    string birth_date;
    string group;
    string number_record;
    int course;
};


bool create_file() {
    // Создание нового пустого файла
    ofstream file("db_stud_ikoeva.dat");
    if (!file.is_open()) {
        return false;
    }
    file.close();
    return true;
}


bool write_student() {
    // Добавление нового студента
    Student stud;

    cout << "\nВведите данные студента:" << endl;
    cout << "Фамилия: ";
    cin >> stud.surname;

    cout << "Имя: ";
    cin >> stud.name;

    cout << "Отчество: ";
    cin >> stud.otch;

    cout << "Дата рождения (дд.мм.гггг): ";
    cin >> stud.birth_date;

    cout << "Группа: ";
    cin >> stud.group;

    cout << "Номер зачетки: ";
    cin >> stud.number_record;

    cout << "Курс: ";
    cin >> stud.course;

    ofstream file("db_stud_ikoeva.dat", ios::app);
    if (!file.is_open()) {
        return false;
    }

    file << stud.surname << "|" << stud.name << "|" << stud.otch << "|"
        << stud.birth_date << "|" << stud.group << "|"
        << stud.number_record << "|" << stud.course << "|" << endl;

    file.close();
    return true;
}


int read_all_students(Student students[], int max_size) {
    // Чтение всех студентов из файла(используется в display_students(), display_sorted_students())
    ifstream file("db_stud_ikoeva.dat");

    if (!file.is_open()) {
        return 0;
    }

    int count = 0;
    string line;

    while (count < max_size and getline(file, line)) {
        if (line.empty()) continue;

        int field = 0;
        string inform = "";

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '|') {
                if (field == 0) {
                    students[count].surname = inform;
                }
                else if (field == 1) {
                    students[count].name = inform;
                }
                else if (field == 2) {
                    students[count].otch = inform;
                }
                else if (field == 3) {
                    students[count].birth_date = inform;
                }
                else if (field == 4) {
                    students[count].group = inform;
                }
                else if (field == 5) {
                    students[count].number_record = inform;
                }
                else if (field == 6) {
                    students[count].course = stoi(inform);
                }
                inform = "";
                field++;
            }
            else {
                inform += line[i];
            }
        }
        count++;
    }

    file.close();
    return count;
}


void print_student(const Student& stud) {
    // Вывод информации об одном студенте(используется в display_students(), display_sorted_students())
    cout << left << "| " << setw(15) << stud.surname << "| " << setw(10) << stud.name << "| " << setw(15) << stud.otch << "| " << setw(12) << stud.birth_date
        << "| " << setw(10) << stud.group << "| " << setw(15) << stud.number_record << "| " << setw(6) << stud.course << "|" << endl;
}


void print_header() {
    // Вывод шапки таблицы
    cout << "| Фамилия        | Имя       | Отчество       | Дата рожд.  | Группа    | Номер зачетки  | Курс  |" << endl;
    cout << "|----------------|-----------|----------------|-------------|-----------|----------------|-------|" << endl;
}


bool display_students() {
    // Показать всех студентов(используется в display_students())
    Student students[100];
    int count = read_all_students(students, 100);

    if (count == 0) {
        return false;
    }

    cout << "\n=== Все студенты ===" << endl;
    print_header();

    for (int i = 0; i < count; i++) {
        print_student(students[i]);
    }
    return true;
}


void sort_by_surname(Student students[], int count) {
    // Сортировка по фамилии (пузырьковая сортировка)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].surname > students[j + 1].surname) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}


void sort_by_course(Student students[], int count) {
    // Сортировка по курсу
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].course > students[j + 1].course) {
                Student value = students[j];
                students[j] = students[j + 1];
                students[j + 1] = value;
            }
        }
    }
}


void sort_by_group(Student students[], int count) {
    // Сортировка по группе
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].group > students[j + 1].group) {
                Student value = students[j];
                students[j] = students[j + 1];
                students[j + 1] = value;
            }
        }
    }
}

bool display_sorted_students(int sort_option) {
    // Показать студентов с сортировкой
    Student students[100];
    int count = read_all_students(students, 100);

    if (count == 0) {
        return false;
    }

    if (sort_option == 1) {
        sort_by_surname(students, count);
        cout << "\nСтуденты (сортировка по фамилии)" << endl;
    }
    else if (sort_option == 2) {
        sort_by_course(students, count);
        cout << "\nСтуденты (сортировка по курсу)" << endl;
    }
    else if (sort_option == 3) {
        sort_by_group(students, count);
        cout << "\nСтуденты (сортировка по группе)" << endl;
    }

    print_header();
    for (int i = 0; i < count; i++) {
        print_student(students[i]);
    }
    return true;
}

bool find_student_by_surname() {
    // Поиск студента по фамилии
    string surname;
    cout << "\nВведите фамилию для поиска: ";
    cin >> surname;

    Student students[100];
    int count = read_all_students(students, 100);
    bool found = false;

    cout << "\nРезультаты поиска" << endl;
    print_header();

    for (int i = 0; i < count; i++) {
        if (students[i].surname == surname) {
            print_student(students[i]);
            found = true;
        }
    }

    if (!found) {
        return false;
    }
    return true;
}


int count_students() {
    // Подсчет количества студентов
    ifstream file("db_stud_ikoeva.dat");

    if (!file.is_open()) {
        return 0;
    }

    int count = 0;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }

    file.close();
    return count;
}

// Меню программы
void show_menu() {
    cout << "\n========================================" << endl;
    cout << "  Программа для работы со студентами" << endl;
    cout << "========================================" << endl;
    cout << "1. Добавить студента" << endl;
    cout << "2. Показать всех студентов" << endl;
    cout << "3. Показать студентов (по фамилии)" << endl;
    cout << "4. Показать студентов (по курсу)" << endl;
    cout << "5. Показать студентов (по группе)" << endl;
    cout << "6. Найти студента по фамилии" << endl;
    cout << "7. Показать количество студентов" << endl;
    cout << "8. Создать новый файл" << endl;
    cout << "0. Выход" << endl;
    cout << "========================================" << endl;
    cout << "Выберите действие: ";
}

int main() {
    system("chcp 1251 > nul");
    int choice;

    while (true) {
        show_menu();
        cin >> choice;

        if (choice == 1) {
            if (write_student()) {
                cout << "\nСтудент успешно добавлен!" << endl;
            }
            else {
                cout << "\nОшибка добавления студента!" << endl;
            }
        }
        else if (choice == 2) {
            if (display_students()) {
                cout << "\nВсе студенты успешно представлены!" << endl;
            }
            else {
                cout << "\nбаза данных пуста, внесите данные студентов!" << endl;
            }
        }
        else if (choice == 3) {
            if (display_sorted_students(1)) {
                cout << "\nВсе студенты успешно представлены!" << endl;
            }
            else {
                cout << "\nбаза данных пуста, внесите данные студентов!" << endl;
            }
        }
        else if (choice == 4) {
            if (display_sorted_students(2)) {
                cout << "\nВсе студенты успешно представлены!" << endl;
            }
            else {
                cout << "\nбаза данных пуста, внесите данные студентов!" << endl;
            }
        }
        else if (choice == 5) {
            if (display_sorted_students(3)) {
                cout << "\nВсе студенты успешно представлены!" << endl;
            }
            else {
                cout << "\nбаза данных пуста, внесите данные студентов!" << endl;
            }
        }
        else if (choice == 6) {
            if (!find_student_by_surname()) {
                cout << "\nСтудент с данной фамилией не найден! (проверьте регистр первой буквы)" << endl;
            }
            else {
                cout << "\nСтудент(ы) успешно найден(ы)!" << endl;
            }

            ;
        }
        else if (choice == 7) {
            if (count_students() == 0) {
                cout << "\nбаза данных пуста, внесите данные студентов!" << endl;
            }
            else {
                cout << "\nВсего студентов в базе: " << count_students() << endl;
            }
            
        }
        else if (choice == 8) {
            if (create_file()) {
                cout << "Файл создан успешно!" << endl;
            }
            else {
                cout << "Ошибка создания файла!" << endl;
            }
        }
        else if (choice == 0) {
            cout << "\nЗавершение работы программы..." << endl;
            break;
        }
        else {
            cout << "\nНеверный выбор! Попробуйте снова." << endl;
        }
    }

    return 0;
}