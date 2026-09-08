#include <iostream>
#include <cstdlib>
#include "task7.h"
using namespace std;

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test case 1: 2x2 matrix multiplication
    cout << "Test 1: 2x2 matrix multiplication" << endl;
    int n1 = 2;
    int** A1 = createMatrix(n1);
    int** B1 = createMatrix(n1);
    int valsA1[2][2] = {{1, 2}, {3, 4}};
    int valsB1[2][2] = {{5, 6}, {7, 8}};
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n1; j++) {
            A1[i][j] = valsA1[i][j];
            B1[i][j] = valsB1[i][j];
        }

    int** strassenResult1 = strassenMultiply(A1, B1, n1);
    int** standardResult1 = standardMultiply(A1, B1, n1);
    cout << "Strassen result:" << endl;
    printMatrix(strassenResult1, n1);
    cout << "Matches standard multiplication: "
         << (matricesEqual(strassenResult1, standardResult1, n1) ? "PASS" : "FAIL") << endl;

    deleteMatrix(A1, n1); deleteMatrix(B1, n1);
    deleteMatrix(strassenResult1, n1); deleteMatrix(standardResult1, n1);

    // Test case 2: 4x4 matrix multiplication
    cout << "\nTest 2: 4x4 matrix multiplication" << endl;
    int n2 = 4;
    int** A2 = createMatrix(n2);
    int** B2 = createMatrix(n2);
    for (int i = 0; i < n2; i++)
        for (int j = 0; j < n2; j++) {
            A2[i][j] = i + j;
            B2[i][j] = i - j;
        }

    int** strassenResult2 = strassenMultiply(A2, B2, n2);
    int** standardResult2 = standardMultiply(A2, B2, n2);
    cout << "Strassen result:" << endl;
    printMatrix(strassenResult2, n2);
    cout << "Matches standard multiplication: "
         << (matricesEqual(strassenResult2, standardResult2, n2) ? "PASS" : "FAIL") << endl;

    deleteMatrix(A2, n2); deleteMatrix(B2, n2);
    deleteMatrix(strassenResult2, n2); deleteMatrix(standardResult2, n2);

    // Test case 3: random 8x8 matrices compared against naive multiplication
    cout << "\nTest 3: random 8x8 matrices vs. naive multiplication" << endl;
    int n3 = 8;
    int** A3 = createMatrix(n3);
    int** B3 = createMatrix(n3);
    srand(42); // fixed seed so the test is reproducible
    for (int i = 0; i < n3; i++)
        for (int j = 0; j < n3; j++) {
            A3[i][j] = rand() % 10;
            B3[i][j] = rand() % 10;
        }

    int** strassenResult3 = strassenMultiply(A3, B3, n3);
    int** standardResult3 = standardMultiply(A3, B3, n3);
    cout << "Matches standard multiplication: "
         << (matricesEqual(strassenResult3, standardResult3, n3) ? "PASS" : "FAIL") << endl;

    deleteMatrix(A3, n3); deleteMatrix(B3, n3);
    deleteMatrix(strassenResult3, n3); deleteMatrix(standardResult3, n3);

    return 0;
}
