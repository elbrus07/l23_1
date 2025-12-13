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





int main(int argc, char** argv){
    vector<string> command;
    for (int i = 1; i < argc; i ++){
        command.push_back(string(argv[i]));
    }
    if(string(argv[1]) == "READ"){
        read(command);
    }
}
