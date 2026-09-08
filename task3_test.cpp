#include <iostream>
#include "task3.h"
using namespace std;

// Helper to print the contents of the result array in [a, b, c] form.
void printResult(int result[], int count) {
    cout << "[";
    for (int i = 0; i < count; i++) {
        cout << result[i];
        if (i != count - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    // Test case 1: multiple occurrences of the key
    int arr1[] = {1, 2, 3, 2, 4, 2};
    int n1 = 6;
    int result1[6];
    int count1;
    findIndices(arr1, n1, 2, result1, count1);
    cout << "Test 1 (multiple occurrences of 2): ";
    printResult(result1, count1);

    // Test case 2: key not present in the array
    int arr2[] = {5, 6, 7};
    int n2 = 3;
    int result2[3];
    int count2;
    findIndices(arr2, n2, 100, result2, count2);
    cout << "Test 2 (key not present): ";
    printResult(result2, count2);

    // Test case 3: empty array
    int n3 = 0;
    int result3[1];
    int count3;
    findIndices(nullptr, n3, 5, result3, count3);
    cout << "Test 3 (empty array): ";
    printResult(result3, count3);

    return 0;
}
