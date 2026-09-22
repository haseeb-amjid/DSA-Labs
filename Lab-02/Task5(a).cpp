#include<iostream>
using namespace std;
int main()
{
    int a=5, b=10;
    int *pa=&a;
    int *pb=&b;
    int temp;
    temp=*pa;
    *pa=*pb;
    *pb=temp;
    cout<<"Value of a: "<<*pa<<endl;
    cout<<"Value of b: "<<*pb<<endl;
    return 0;
}