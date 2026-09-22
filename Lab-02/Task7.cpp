#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter n (1-10): ";
    cin >> n;
    while (n < 1 || n > 10) {
        cout << "Invalid. Enter n (1-10): ";
        cin >> n;
    }

    int *marks = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter mark " << (i+1) << ": ";
        cin >> marks[i];
    }

    // Step 1: allocate a new block of n+1 ints, copy old values, read the new mark
    int *newMarks = new int[n + 1];
    for (int i = 0; i < n; i++) {
        *(newMarks + i) = *(marks + i);
    }
    cout << "Enter the new mark: ";
    cin >> *(newMarks + n);

    // Step 2: release the old block, repoint marks, update size, display
    delete[] marks;
    marks = newMarks;
    n = n + 1;

    cout << "Updated marks: ";
    for (int i = 0; i < n; i++) {
        cout << marks[i] << " ";
    }
    cout << endl;

    // Step 3: release the final block exactly once
    delete[] marks;
    marks = nullptr;

    return 0;
}