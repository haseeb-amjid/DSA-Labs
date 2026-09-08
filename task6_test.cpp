#include <iostream>
#include "task6.h"
using namespace std;

void printModes(int modes[], int modeCount) {
    cout << "{";
    for (int i = 0; i < modeCount; i++) {
        cout << modes[i];
        if (i != modeCount - 1) cout << ", ";
    }
    cout << "}";
}

int main() {
    // Test case 1: array with a unique mode
    int arr1[] = {1, 2, 2, 3, 2, 4};
    int n1 = 6;
    int modes1[100], modeCount1, maxFreq1;
    findMode(arr1, n1, modes1, modeCount1, maxFreq1);
    cout << "Test 1 (unique mode): modes = ";
    printModes(modes1, modeCount1);
    cout << ", frequency = " << maxFreq1 << endl;

    // Test case 2: array with multiple modes (tie)
    int arr2[] = {1, 1, 2, 2, 3};
    int n2 = 5;
    int modes2[100], modeCount2, maxFreq2;
    findMode(arr2, n2, modes2, modeCount2, maxFreq2);
    cout << "Test 2 (multiple modes): modes = ";
    printModes(modes2, modeCount2);
    cout << ", frequency = " << maxFreq2 << endl;

    // Test case 3: empty array
    int n3 = 0;
    int modes3[100], modeCount3, maxFreq3;
    bool ok3 = findMode(nullptr, n3, modes3, modeCount3, maxFreq3);
    cout << "Test 3 (empty array): "
         << (ok3 ? "FAIL (should return false)" : "PASS (returned false)") << endl;

    return 0;
}
