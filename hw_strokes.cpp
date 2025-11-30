#include <iostream>
#include <string>
using namespace std;

void strokeCompress(string in_str) {
    int len = in_str.size();
    string out_str = "";

    for (int i = 0; i < len; ) {
        char curr = in_str[i];
        int count = 0;

        int j = i;
        while (j < len && in_str[j] == curr) {
            count++;
            j++;
        }

        out_str += curr;
        out_str += to_string(count);

        i = j; 
    }
    
    if (len <= out_str.size()){
      cout << in_str << endl;}else{
      cout << out_str << endl;}   
    
}

bool transposDetect(string a, string b) {
    if (a.size() != b.size()) return false;

    int i = 0;
    while (!a.empty()) {
        bool found = false;

        for (int j = 0; j < b.size(); j++) {
            if (a[i] == b[j]) {
                
                a.erase(i, 1);
                b.erase(j, 1);
                found = true;
                break;
            }
        }

        
        if (!found) return false;
    }

    return true;
}

        
    
  
int main() {
    strokeCompress("eeeello");
    cout << transposDetect("sarmat","asrmta");
    return 0;
}