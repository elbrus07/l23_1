#include <iostream>
#include <fstream>
// #include <ifstream>
// #include <ofstream>
#include <string>
#include <vector>
using namespace std;

void commandListener(string command){
    cout<<command;
    string word = "";
    string commands[]{};
    int len = command.length();
    for (int i = 0; i<len; i++){
        if (command[i] != ' '){
            word += command[i];
        }else{
            cout<<word<<endl;
            word = "";
        }
    }
}

void runCommand(){
    string base[]{"ADD", "READ", "FILTERS", "REMOVE", "UPDATE"};
}

int main(int argc, char** argv){
    vector<string> commands;
    for(int i = 1; i < argc; i++){
        commands.push_back(argv[i]);
    }
    cout<<argv[1]<<endl<<commands[1]<<endl;
    commandListener(argv[1]);
    return 0;
}

