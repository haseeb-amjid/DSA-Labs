#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int* pa = &a;
    pa = pa * 2;  
    return 0;
}