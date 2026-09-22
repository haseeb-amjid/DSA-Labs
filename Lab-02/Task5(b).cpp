#include<iostream>
using namespace std;
int main()
{
    int a=5, b=10;
    int *pa=&a;
    int *pb=&b;
    int **ppa=&pa;
    int **ppb=&pb;
    int temp;
    temp=**ppa;
    **ppa=**ppb;
    **ppb=temp;
    cout<<"Value of a: "<<**ppa<<endl;
    cout<<"Value of b: "<<**ppb<<endl;
    return 0;
}