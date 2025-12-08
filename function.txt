#include <iostream>
#include <cmath>
using namespace std;

// 1. Определить периметр треугольника, заданного координатами вершин.
// Длину стороны треугольника вычислять в функции. Посчитать среднее
// арифметическое периметров трех треугольников, координаты которых ввести с клавиатуры.
double storona(double x1,double y1,double x2,double y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

double perimetr(double x1,double y1,double x2,double y2,double x3,double y3)
{
    return storona(x1,y1,x2,y2)+storona(x2,y2,x3,y3)+storona(x1,y1,x3,y3);
}

// 4. Написать функцию, вычисляющую количество совпадений числа x с элементами числового массива
int sov(int a[],int n,int x) 
{
    int cnt=0;
    for(int i=0;i<n;i++)
        if(a[i]==x) cnt++;
    return cnt;
}

// 3. Написать функцию табуляции функции  в точках x = 1,2,3,..., 12.
double f(double x)
{
    return x*x; 
}

int main()
// {   //задание 1
//     double x1,y1,x2,y2,x3,y3;
//     double sr=0;
//     for(int i=0;i<3;i++)
//     {
//         cin>>x1>>y1>>x2>>y2>>x3>>y3;
//         sr=sr+perimetr(x1,y1,x2,y2,x3,y3);   
//     }
//     cout<<sr/3;
//     //задание 4
//     int a[]={1,2,2,3,4,2};
//     int n=6;
//     int x=2;
//     cout<<sov(a,n,x);
//     //задание 3
//     for(int x=1;x<=12;x++)
//     {
//         cout<<x<<" "<<f(x)<<endl;
//     }
}