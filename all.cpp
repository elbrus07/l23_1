#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void searching(int arr[], int p, int len){
    int min = 1000000;
    int raz;
    for (int i = 0; i < len; i++){
        raz = arr[i] - p;
        if (raz < min && raz > 0){
            min = raz;
        }else{
            raz = p - arr[i];
            if (raz < min && raz > 0){
                min = raz;
            }
            
        }
    }
    cout << min << " " << p - min;
}

int main() {
	int arr[11]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2};
	searching(arr, 1, 11);
	return 0;

}
