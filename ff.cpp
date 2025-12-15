#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
/**/


int stud(string name, string surname , string secondname, string age, string group, string exemnumbook ,int cours, int flag) {
	string line;
	int k = 0;
	ofstream studf("db_stud.dat", ios::app);
	if (studf.is_open()) {
		studf << "ФИО: " << name << " " << surname << " " << secondname << " Возраст: " << age << " Группа: " << group << " Зачетка: " << exemnumbook << " Курс: " << cours << endl;
		if (flag == 1) {
			ifstream studf("db_stud.dat");
			while (getline(studf, line, '\n')) {
				k++;
			}

		}
		
	}
	studf.close();
	return k;
}

int main() {
	int k = stud("Иванов", "Иван", "Иванович", "19", "12", "Ш12121", 3 , 1);
	cout << k<<"\n";
	return 0;
}
