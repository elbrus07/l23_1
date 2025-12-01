#include <iostream>
#include <cstdlib>
#include <cmath>
#include <climits>
using namespace std;
void arrayCreate(){
  /*
  :param len - Длина создаваемого массива
  Функция создает массив заданной длины из элементов
  вводимых с клавиатуры.
  */
  cout<<"Введите размер массива"<<endl;
  int len; 
  cin>>len;
  cout<<"Вводите элементы массива"<<endl;
  int element = 0;
  int arr[len];
  for(int i = 0; i < len; i++){
    cin>>element;
    arr[i] = element;
  }
  for(int i = 0; i < len; i++){
    cout<<arr[i]<<"\t";}
}
void randomArray(int start, int end){
  /*
  :param start - начало диапазона
  :param end - конец диапазона
  Функция создает массив случайного размера из 
  диапазона start - end и заполнят случайными
  значениями из того же диапазона.
  Выводит массив в консоль
  
  */
  int len = rand() % (end - start + 1) + start;
  int arr[len];
  int element = 0;
  for (int i = 0; i < len; i++){
    element = rand() % (end - start + 1) + start;
    arr[i] = element;
    cout<<arr[i]<<"\t";
    }
}

void randomBin(int len){
  /*
  :param len - Длина массива.
  Функция принимает длину массива и генерирует
  случайный массив из 0 и 1 с их равным количеством.
  Длина массива должна быть четной.
  */
    if (len % 2 != 0){
        cout << "Длина массива должна быть четная!";
        return;
    }

    int arr[len];
    int zero = 0;
    int one = 0;

    // Генерация массива
    for (int i = 0; i < len; i++) {
        arr[i] = rand() % 2;
        if (arr[i] == 0) zero++;
        else one++;
    }

    
    int target = len / 2;


    if (zero > one) {
        int need = zero - target; 
        for (int i = 0; i < len && need > 0; i++) {
            if (arr[i] == 0) {
                arr[i] = 1;
                need--;
            }
        }
    }
 
    else if (one > zero) {
        int need = one - target;
        for (int i = 0; i < len && need > 0; i++) {
            if (arr[i] == 1) {
                arr[i] = 0;
                need--;
            }
        }
    }

    // Вывод результата
    for (int i = 0; i < len; i++){
        cout << arr[i];
    }
    cout << endl;
}
    
    
template <size_t N> //Определиние длины массива, передаваемого в функцию
void summander(int (&arr)[N]){
  /* 
  :param arr - массив
  Возвращает значение выражения A1 - A2 + A3 -A4 +...+An-1-An
  */
  int size = N/2;
  int sum = 0;
  
  for (int i = 0; i < size; i++){
    sum += (arr[i] - arr[i+1]);
    }
  if (N%2 != 0){ sum += arr[size*2];}
  cout<<sum<<endl;}
  
  
template <size_t N>
void minMaxReplace(int (&arr)[N]){
  int min = 10000;
  int max = 0;
  for (int i = 0; i < N; i++){
    if (arr[i] > max){
      max = arr[i];}
    if (arr[i] < min){
      min = arr[i];}}
  for (int i = 0; i < N; i++){
    if (arr[i] == max){
      arr[i] = min;
      i++;}
    if (arr[i] == min){
      arr[i] = max;
      i++;}
   
  }
  for (int i = 0; i < N; i++){
    cout<<arr[i]<<"\t";}
  
  cout<<endl;
} 

template <size_t len>
void neighborReplace(int(&arr)[len]){
  for (int i = 1; i < len; i++){
    if (i%2 == 0){
      arr[i] = arr[i - 1];}}
  for (int i = 0; i < len; i++){
    cout<<arr[i]<<"\t";}
  cout<<endl;
    
 }
template <size_t len> 
void minSum(int (&arr)[len], int p) {
    int bestDiff = INT_MAX;   // минимальная разница
    int bestSum = 0;          // лучшая найденная сумма

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {  // j = i+1, чтобы не сравнивать элемент сам с собой
            int sum = arr[i] + arr[j];
            int diff = abs(sum - p);

            if (diff < bestDiff) {
                bestDiff = diff;
                bestSum = sum;
            }
        }
    }

    cout << bestSum << endl;
}
template <size_t f_len, size_t s_len>
void arrayUnify(int (&f_arr)[f_len], int (&s_arr)[s_len]){
  
  
  for (int i = 0; i < f_len; i++){
    for (int j = 0; j < s_len; j++){
      if (f_arr[i] == s_arr[j]){
        cout << f_arr[i] <<"\t";
      }
 }

 } 
  cout << endl;}
          
 
int main(){
  int arr[]{1,2,3,58,6,7,9,};
  int arr1[]{0,1,5,6,3,4};
  summander(arr);
  arrayCreate();
  randomArray(5, 10);
  randomBin(8);
  minMaxReplace(arr);
  neighborReplace(arr);
  minSum(arr, 61);
  arrayUnify(arr, arr1);
  return 0;}
  
