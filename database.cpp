#include <iostream>
#include <fstream>
// #include <ifstream>
// #include <ofstream>
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


void read(vector<string> &com){
    int len = com.size();
    vector<string> sec = {"FILTER", "VAL", "TO", "EQ", "WHERE"};
    if (len == 1){
        cout<<111<<endl;
    }


}




int main(int argc, char** argv){
    vector<string> commands;
    if (argc == 2 && string(argv[1]) == "help"){
        help();
        
    }

    if(argc >= 3 && string(argv[1]) == "READ"){
        for(int i = 2; i < argc; i++){
            commands.push_back(argv[i]);
        }
        read(commands);
        cout<<commands.at(0);
    }
    
    // for(int i = 1; i < argc; i++){
    //     commands.push_back(argv[i]);
    // }
    // cout<<argv[1]<<endl<<commands[1]<<endl;
    // commandListener(argv[1]);
    return 0;
}

