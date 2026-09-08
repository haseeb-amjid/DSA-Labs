#include "task5.h"

int** generatePascalTriangle(int n) {
    if (n <= 0) return nullptr;

    int** triangle = new int*[n];
    for (int i = 0; i < n; i++) {
        triangle[i] = new int[i + 1];
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                // Edges of the triangle are always 1.
                triangle[i][j] = 1;
            } else {
                // Each inner value is the sum of the two values above it.
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }
    return triangle;
}

void deleteTriangle(int** triangle, int n) {
    if (triangle == nullptr) return;
    for (int i = 0; i < n; i++) {
        delete[] triangle[i];
    }
    delete[] triangle;
}
