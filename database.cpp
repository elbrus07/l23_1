#include <iostream>
#include <fstream>
// #include <ifstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

void help(){
    cout<<"[] - Обязательный параметр"<<"\t"<<"<> - Необязательный параметр"<<endl;
    cout<<"COMMAND"<<"\t"<<"ARGS"<<"\t"<<"DESCRIPTION"<<endl;
    cout<<"ADD"<<"\t"<<"[db-file] [VAL [val1], <val2> ...] [TO [col1] <col2> ...]"<<"\t"<<"Добавить значение в столбец"<<endl;
    cout<<"READ"<<"\t"<<"[db-file] <SECOND-COMMANDS>"<<"\t"<<"Прочитать все строки из db-file"<<endl;
    cout<<"REMOVE"<<"\t"<<"[db-file] [WHERE [col1] <col2> ...] [EQ [val1], <val2> ...] "<<"\t"<<"Удалить строки где в колонне есть значение val"<<endl;
    cout<<"SORT"<<"\t"<<"[db-file] [col1] [option] "<<"\t"<<"Сортировать по колонне option-образом"<<endl;
}


void read(vector<string>& com) {
    // Проверяем минимальное количество аргументов
    if (com.size() < 2) {
        cout << "Error: specify filename!" << endl;
        cout << "Usage: READ <filename> [FILTER <column> <value>]" << endl;
        return;
    }
    
    string filename = com[1];
    ifstream inFile(filename);
    
    if (!inFile.is_open()) {
        cout << "Error: cannot open file " << filename << endl;
        return;
    }
    
    // Читаем заголовок
    string header;
    if (!getline(inFile, header)) {
        cout << "Error: file is empty or cannot read header" << endl;
        inFile.close();
        return;
    }
    
    // Разбираем заголовок на колонки
    vector<string> columns;
    string current = "";
    for (char c : header) {
        if (c == '|') {
            columns.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        columns.push_back(current);
    }
    
    // Простой вывод без фильтра
    if (com.size() == 2) {
        // Выводим заголовок с табуляцией
        string header_out = header;
        replace(header_out.begin(), header_out.end(), '|', '\t');
        cout << header_out << endl;
        
        // Выводим данные
        string line;
        while (getline(inFile, line)) {
            if (!line.empty()) {
                string out = line;
                replace(out.begin(), out.end(), '|', '\t');
                cout << out << endl;
            }
        }
    }
    // Фильтрация по значению
    else if (com.size() >= 4 && com[2] == "FILTER") {
        // Получаем имя колонки и значение для фильтрации
        string filter_column = com[3];
        string filter_value = (com.size() >= 5) ? com[4] : "";
        
        // Находим индекс колонки
        int column_index = -1;
        for (size_t i = 0; i < columns.size(); i++) {
            if (columns[i] == filter_column) {
                column_index = i;
                break;
            }
        }
        
        if (column_index == -1) {
            cout << "Error: column '" << filter_column << "' not found" << endl;
            cout << "Available columns: ";
            for (size_t i = 0; i < columns.size(); i++) {
                cout << columns[i];
                if (i < columns.size() - 1) cout << ", ";
            }
            cout << endl;
            inFile.close();
            return;
        }
        
        // Выводим заголовок
        string header_out = header;
        replace(header_out.begin(), header_out.end(), '|', '\t');
        cout << header_out << endl;
        
        // Фильтруем и выводим данные
        string line;
        int matched_count = 0;
        int total_count = 0;
        
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            
            total_count++;
            
            // Разбиваем строку на поля
            vector<string> fields;
            string field = "";
            for (char c : line) {
                if (c == '|') {
                    fields.push_back(field);
                    field = "";
                } else {
                    field += c;
                }
            }
            if (!field.empty()) {
                fields.push_back(field);
            }
            
            // Проверяем условие фильтрации
            if (column_index < fields.size() && fields[column_index] == filter_value) {
                matched_count++;
                string out = line;
                replace(out.begin(), out.end(), '|', '\t');
                cout << out << endl;
            }
        }
        
        cout << "\nFilter results:" << endl;
        cout << "  Total rows: " << total_count << endl;
        cout << "  Matched rows: " << matched_count << endl;
        cout << "  Filter: " << filter_column << " = " << filter_value << endl;
    }
    else {
        cout << "Error: invalid syntax for READ command" << endl;
        cout << "Usage: READ <filename>" << endl;
        cout << "   or: READ <filename> FILTER <column> <value>" << endl;
    }
    
    inFile.close();
}


void add(vector<string> &com){
    int len = com.size();
    ofstream outFile;
    outFile.open(com[0], std::ios::app);
    
    if (outFile.is_open()){
        outFile<<"\n"<<com[1];
        
        
    }

    
}




int main(int argc, char** argv){

    vector<string> commands;
    if (argc == 2 && string(argv[1]) == "help"){
        help();
        
    }

    if(argc >= 3 && string(argv[1]) == "READ"){
        for(int i = 1; i < argc; i++){
            commands.push_back(argv[i]);
        }
        read(commands);
        cout<<commands.at(0);
    }else if(argc >= 4 && string(argv[1]) == "ADD"){
        for(int i = 2; i < argc; i++){
            commands.push_back(argv[i]);
        }
        add(commands);
        cout<<commands.at(0);
    }
    
    // for(int i = 1; i < argc; i++){
    //     commands.push_back(argv[i]);
    // }
    // cout<<argv[1]<<endl<<commands[1]<<endl;
    // commandListener(argv[1]);
    return 0;
}

