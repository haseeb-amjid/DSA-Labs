#include <iostream>
using namespace std;
int main()
{
    int n = 3;
    int* values = new int[n];
    // Read three integers (input test: 4 5 6)
    for (int i = 0; i < n; i++)
    {
        cin >> values[i];
    }
    for (int i = 0; i < n; i++)
    {
        cout << values[i] << (i < n - 1 ? " " : "");
    }
    cout << endl;
    delete[] values;
    values = nullptr;
    return 0;
}