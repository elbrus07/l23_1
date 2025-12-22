#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
/**/


void stud(string name, string surname , string secondname, string age, string group, string exemnumbook ,int cours, int flag) {
	string line;
	int k = 0;
	ofstream studf("db_stud.dat", ios::app);
	if (studf.is_open()) {
		studf << "Студетнт: " << name << " " << surname << " " << secondname << " Дата рождения: " << age << " Группа: " << group << " Номер зачетной книжки: " << exemnumbook << " Номер курса: " << cours << endl;
		if (flag == 1) {
			ifstream studf("db_stud.dat");
			while (getline(studf, line, '\n')) {
				k++;
			}
			cout << k;
		}
		
	}
	
	studf.close();

}

int main() {
	stud("asdf", "asdf", "asdf", "asdf", "asdf", "asdf", 3 , 1);
	return 0;
}