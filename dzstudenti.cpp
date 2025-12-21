#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
/*хранения данных одного студента */
struct Student
{
    string fam;
    string name;
    string otch;
    string birth;
    string group;
    string book;
    int kurs;
};

/*добывление нового студента в файл */
void addStudent(string filename)
{
    ofstream file(filename, ios::app);
    Student s;
    cout << "Фамилия: ";
    cin >> s.fam;
    cout << "Имя: ";
    cin >> s.name;
    cout << "Отчество: ";
    cin >> s.otch;
    cout << "Дата рождения: ";
    cin >> s.birth;
    cout << "Группа: ";
    cin >> s.group;
    cout << "Номер зачетки: ";
    cin >> s.book;
    cout << "Курс: ";
    cin >> s.kurs;
    // запись в файл с разделителем ;
    file << s.fam << ";"
         << s.name << ";"
         << s.otch << ";"
         << s.birth << ";"
         << s.group << ";"
         << s.book << ";"
         << s.kurs << endl;
    file.close();
}
/* сортировка по курсу */
void showByKurs(string filename, int needKurs)
{
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        Student s;
        string kursStr;
        stringstream ss(line);
        // разбивка по ращделителю
        getline(ss, s.fam, ';');
        getline(ss, s.name, ';');
        getline(ss, s.otch, ';');
        getline(ss, s.birth, ';');
        getline(ss, s.group, ';');
        getline(ss, s.book, ';');
        getline(ss, kursStr, ';');
        s.kurs = stoi(kursStr);
        if (s.kurs >= needKurs)
        {
            cout << s.fam << " "
                 << s.name << " "
                 << s.otch
                 << ", курс " << s.kurs << endl;
        }
    }
    file.close();
}
/* кол-во студентов в файле */
void countStudents(string filename)
{
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line))
    {
        count++;
    }
    file.close();
    cout << "Количество студентов: " << count + 1 << endl;
}
/* Главная функция с меню */
int main()
{
    string filename = "db_stud.dat";
    int choice;
    do
    {
        cout << "\n1 - Добавить студента";
        cout << "\n2 - Показать студентов по курсу";
        cout << "\n3 - Подсчитать студентов";
        cout << "\n0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        if (choice == 1)
            addStudent(filename);
        if (choice == 2)
        {
            int kurs;
            cout << "Введите курс: ";
            cin >> kurs;
            showByKurs(filename, kurs);
        }
        if (choice == 3)
            countStudents(filename);
    } while (choice != 0);
    return 0;
}
