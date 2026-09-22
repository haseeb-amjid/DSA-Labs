#include <iostream>
using namespace std;

int main()
{
    // Size of int in bytes
    cout << "Size of int    : " << sizeof(int) << " bytes" << endl;
    // Size of int in long
    cout << "Size of long   : " << sizeof(long) << " bytes" << endl;
    // Size of int in double
    cout << "Size of double : " << sizeof(double) << " bytes" << endl;
    // Size of int in float
    cout << "Size of float  : " << sizeof(float) << " bytes" << endl;
    // Size of int in char
    cout << "Size of char   : " << sizeof(char) << " bytes" << endl;
    return 0;
}