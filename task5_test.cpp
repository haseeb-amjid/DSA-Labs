#include <iostream>
#include "task5.h"
using namespace std;

// Prints the triangle row by row.
void printTriangle(int** triangle, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cout << triangle[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test case 1: n = 0
    cout << "Test 1 (n = 0):" << endl;
    int** t0 = generatePascalTriangle(0);
    cout << (t0 == nullptr ? "No rows generated (as expected)." : "FAIL") << endl;
    deleteTriangle(t0, 0);

    // Test case 2: n = 1
    cout << "\nTest 2 (n = 1):" << endl;
    int** t1 = generatePascalTriangle(1);
    printTriangle(t1, 1);
    deleteTriangle(t1, 1);

    // Test case 3: n = 5
    cout << "\nTest 3 (n = 5):" << endl;
    int n5 = 5;
    int** t5 = generatePascalTriangle(n5);
    printTriangle(t5, n5);

    // Verify row 5 (index 4) -> {1, 4, 6, 4, 1}
    int expected[] = {1, 4, 6, 4, 1};
    bool match = true;
    for (int j = 0; j < 5; j++) {
        if (t5[4][j] != expected[j]) match = false;
    }
    cout << "Verifying row 5 == {1, 4, 6, 4, 1}: " << (match ? "PASS" : "FAIL") << endl;

    deleteTriangle(t5, n5);
    return 0;
}
