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

    if (!getline(file, str)) {
        cout << "fileError: file "<<com[1] <<" is empty" << endl;
        file.close();
        return;
    }
    getline(file, str);
    header = strToArray(str);
    for(int i = 0; i < header.size(); i++){
        cout<<header[i]<<" | ";}
        cout<<endl;

    if (len == 2){
        
            while(getline(file, str)){
                stroke = strToArray(str);
                for(int i = 0; i < stroke.size(); i++){
                    cout<<stroke[i]<<" | ";

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
                    cout<<stroke[index[i]]<<" | ";
                    

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



void sort(vector<string> &com) {
    
    if (com.size() < 6) {  
        cout << "SyntaxError:" << endl << "USE: SORT file_name TO [columns] VAL [values]" << endl;
        return;
    }
    
    string filename = com[1];
    int toPos = 2;
    
    
    if (com[toPos] != "TO") {
        cout << "SyntaxError:" << endl << "Please, write 'TO' after file_name" << endl;
        return;
    }
    
    
    int valPos = -1;
    for (int i = toPos + 1; i < com.size(); i++) {
        if (com[i] == "VAL") {
            valPos = i;
            break;
        }
    }
    
    if (valPos == -1) {
        cout << "SyntaxError:" << endl << "Please, write 'VAL' after [columns]" << endl;
        return;
    }
    
    if (valPos - toPos < 2) {
        cout << "SearchError: columns is undefened in command" << endl;
        return;
    }
    
    if (com.size() - valPos < 2) {
        cout << "SearchError: values is undefened in command" << endl;
        return;
    }
    
    
    vector<string> cols;
    for (int i = toPos + 1; i < valPos; i++) {
        cols.push_back(com[i]);
    }
    
    vector<string> vals;
    for (int i = valPos + 1; i < com.size(); i++) {
        vals.push_back(com[i]);
    }
    
    
    if (vals.size() != cols.size()) {
        cout << "SyntaxError: count of values and columns is different" << endl;
        return;
    }
    
    
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "OpenError: Could not open file {" << filename << "}" << endl;
        return;
    }
    
    
    string line;
    if (!getline(inFile, line)) {
        cout << "fileError: file "<<filename <<" is empty" << endl;
        inFile.close();
        return;
    }
    
    vector<string> header = strToArray(line);
    
    
    vector<int> colIndices;
    for (int i = 0; i < cols.size(); i++) {
        bool found = false;
        for (int j = 0; j < header.size(); j++) {
            if (header[j] == cols[i]) {
                colIndices.push_back(j);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Not found {" << cols[i] << "} in file" << endl;
            inFile.close();
            return;
        }
    }
    
    
    for (size_t i = 0; i < header.size(); i++) {
        cout << header[i];
        if (i < header.size() - 1) cout << " | ";
    }
    cout << endl;
    
    
    int foundCount = 0;
    while (getline(inFile, line)) {
        vector<string> row = strToArray(line);
        
        
        if (row.size() != header.size()) continue;
        
        
        bool match = true;
        for (size_t i = 0; i < colIndices.size(); i++) {
            int colIndex = colIndices[i];
            if (colIndex >= row.size() || row[colIndex] != vals[i]) {
                match = false;
                break;
            }
        }
        
        
        if (match) {
            for (size_t i = 0; i < row.size(); i++) {
                cout << row[i];
                if (i < row.size() - 1) cout << " | ";
            }
            cout << endl;
            foundCount++;
        }
    }
    
    inFile.close();
    
    
    
}




int main(int argc, char** argv){
    vector<string> command;
    for (int i = 1; i < argc; i ++){
        command.push_back(string(argv[i]));
    }
    if(string(argv[1]) == "READ"){
        read(command);
    }else if (string(argv[1]) == "ADD"){
        add(command);}
    else if(string(argv[1]) == "SORT"){
        sort(command);
    
}
}
