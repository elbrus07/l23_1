#include <iostream>
#include <cmath>
using namespace std;

//1. Определить периметр треугольника, заданного координатами вершин. 
//Длину стороны треугольника вычислять в функции. 
//Посчитать среднее арифметическое периметров трех треугольников, 
//координаты которых ввести с клавиатуры.
double getVector(){
  double perimetr;
  double x1; 
  double y1;
  double x2;
  double y2;
  double x3;
  double y3;
  int iterations = 0;
  
  cout<<"Введите координаты x1, y1, x2, y2, x3, y3:"<<endl;
  cin>>x1>>y1>>x2>>y2>>x3>>y3;
  double vec_a = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
  double vec_b = sqrt(pow(x3-x1, 2) + pow(y3-y1, 2));
  double vec_c = sqrt(pow(x3-x2, 2) + pow(y3-y2, 2));
  perimetr = vec_a + vec_b + vec_c;
  return perimetr;}
  
  //Написать функцию табуляции функции fx=x−1 в точках x = 1,2,3,..., 12.\
  
  void tabulation(){
  cout<<"x"<<"\t"<<"y"<<endl;
  double y;
  for (int x = 1; x <=12; x ++){
    y = sqrt(x-1);
    cout<<x<<"\t"<<y<<endl;}
    
}


//. Написать функцию, вычисляющую количество совпадений
// числа x с элементами числового массива
template <size_t len>
int coinCounter(int x, int (&arr)[len]){
  int count = 0;
  for (int i=0; i < len; i++){
    if (arr[i] == x){
      count++;
      }
  }
  return count;
}



  
  int main(){
    int arr1[]{4,7,4,5,3,5,2,5};
    //cout<<getVector();
    //cout<<endl;
    //tabulation();
   // cout<<coinCounter(5, arr1);
    
    return 0;
  }
  
  
  
