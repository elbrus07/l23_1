#include <iostream>
#include <sstream>
#include <fstream>
// #include <ifstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


vector<string> strToArray(string str){
  int len = str.size();
  string val = "";
  vector<string> result;
  for (int i = 0; i < len; i ++){
    if (str[i] != '|'){
      val += str[i];}
    else {
      result.push_back(val);
      val = "";
    }} 
    if (!val.empty()){
      result.push_back(val);}
 return result;
 }



void read(vector<string> &com){
    int len = com.size();
    
    vector<string> header;
    vector<string> stroke;
    vector<int> index;
    string str;
    ifstream file(com[1]);
    getline(file, str);
    header = strToArray(str);
    for(int i = 0; i < header.size(); i++){
        cout<<header[i]<<"\t";}
        cout<<endl;

    if (len == 2){
        
            while(getline(file, str)){
                stroke = strToArray(str);
                for(int i = 0; i < stroke.size(); i++){
                    cout<<stroke[i]<<"\t";

                }
                cout<<endl;
                stroke.clear();
            }

        }else if(len > 2 && com[2] == "FILTER"){
            for (int i = 3; i < len; i ++){
                for (int j = 0; j < header.size(); j ++){
                    if(com[i] == header[j]){
                        index.push_back(j);
                    }
            }}

            while(getline(file, str)){
                stroke = strToArray(str);
                for(int i = 0; i < index.size(); i++){
                    cout<<stroke[index[i]]<<"\t";
                    

                }
                cout<<endl;
                stroke.clear();

        }
    }
    

}



void add(vector<string> &com){
    string filename = com[1];
    int comLen = com.size();
    int toPos = 2;
    int valPos = -1;


    vector<string> cols;
    vector<string> vals;

    


    if(comLen < 6 || com[2] != "TO"){
        cout<<"SyntaxError:"<<endl<<"USE: ADD db_file TO [columns] VAL [values]";
        return;
    }

    for (int i = 0; i < comLen; i ++){
        if (com[i] == "VAL"){
            valPos = i;
            break;
        }
    }

    for(int i = toPos + 1; i < valPos; i ++){
        cols.push_back(com[i]);
    }

    for (int i = valPos + 1; i < comLen; i++){
        vals.push_back(com[i]);
    }

    if(cols.size() != vals.size()){
        cout<<"SyntaxError:"<<endl<<"the number of columns does not match the number of values";
        return;
    }

    ifstream inFile(filename);
    string str;
    getline(inFile, str);
    vector<string> header = strToArray(str);
    inFile.close();



    ofstream outFile(filename, ios::app);
    outFile<<"\n";
    if(!outFile.is_open()){
        cout<<"OpenError:"<<endl<<"File opening error";
        return;
    }

    for(int i = 0; i < header.size(); i++){
        if(i > 0){
            outFile<<"|";
        }
        bool mark = false;

        for(int j = 0; j < cols.size(); j++){
            if(header[i] == cols[j]){
                outFile<<vals[j];
                mark = true;
                break;
            }
        }

        if(!mark){
            outFile<<" ";
        }
    }
    

    outFile.close();

}



// void sort(vector<string> $com){
//     fileName = com[1];
//     ifstream inFile(fileName);
//     if (com[3] == "upper"){
//         while(){}
//     }
    
// }





int main(int argc, char** argv){
    vector<string> command;
    for (int i = 1; i < argc; i ++){
        command.push_back(string(argv[i]));
    }
    if(string(argv[1]) == "READ"){
        read(command);
    }else if (string(argv[1]) == "ADD"){
        add(command);}
    // }else if(string(argv[1] == "SORT")){
    //     sort(command);
    // }
}
