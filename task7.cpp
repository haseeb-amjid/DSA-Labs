#include "task7.h"

int** createMatrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    if (matrix == nullptr) return;
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** standardMultiply(int** A, int** B, int n) {
    int** result = createMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// ---- Helpers used only inside this file ----

static int** addMatrix(int** A, int** B, int n) {
    int** result = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

static int** subMatrix(int** A, int** B, int n) {
    int** result = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

// Extracts the (n/2) x (n/2) quadrant of 'src' starting at (rowOffset, colOffset).
static int** getQuadrant(int** src, int n, int rowOffset, int colOffset) {
    int half = n / 2;
    int** quadrant = createMatrix(half);
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++)
            quadrant[i][j] = src[i + rowOffset][j + colOffset];
    return quadrant;
}

// Writes an (n/2) x (n/2) quadrant into 'dest' starting at (rowOffset, colOffset).
static void setQuadrant(int** dest, int** quadrant, int n, int rowOffset, int colOffset) {
    int half = n / 2;
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++)
            dest[i + rowOffset][j + colOffset] = quadrant[i][j];
}

int** strassenMultiply(int** A, int** B, int n) {
    // Base case: small matrices are multiplied directly.
    if (n <= 2) {
        return standardMultiply(A, B, n);
    }

    int half = n / 2;

    // Split A and B into four quadrants each.
    int** A11 = getQuadrant(A, n, 0, 0);
    int** A12 = getQuadrant(A, n, 0, half);
    int** A21 = getQuadrant(A, n, half, 0);
    int** A22 = getQuadrant(A, n, half, half);

    int** B11 = getQuadrant(B, n, 0, 0);
    int** B12 = getQuadrant(B, n, 0, half);
    int** B21 = getQuadrant(B, n, half, 0);
    int** B22 = getQuadrant(B, n, half, half);

    // The 7 Strassen products (each computed with a recursive call).
    int** t1 = addMatrix(A11, A22, half);
    int** t2 = addMatrix(B11, B22, half);
    int** M1 = strassenMultiply(t1, t2, half);

    int** t3 = addMatrix(A21, A22, half);
    int** M2 = strassenMultiply(t3, B11, half);

    int** t4 = subMatrix(B12, B22, half);
    int** M3 = strassenMultiply(A11, t4, half);

    int** t5 = subMatrix(B21, B11, half);
    int** M4 = strassenMultiply(A22, t5, half);

    int** t6 = addMatrix(A11, A12, half);
    int** M5 = strassenMultiply(t6, B22, half);

    int** t7 = subMatrix(A21, A11, half);
    int** t8 = addMatrix(B11, B12, half);
    int** M6 = strassenMultiply(t7, t8, half);

    int** t9 = subMatrix(A12, A22, half);
    int** t10 = addMatrix(B21, B22, half);
    int** M7 = strassenMultiply(t9, t10, half);

    // Combine the seven products into the four result quadrants.
    int** t11 = addMatrix(M1, M4, half);
    int** t12 = subMatrix(t11, M5, half);
    int** C11 = addMatrix(t12, M7, half);

    int** C12 = addMatrix(M3, M5, half);

    int** C21 = addMatrix(M2, M4, half);

    int** t13 = subMatrix(M1, M2, half);
    int** t14 = addMatrix(t13, M3, half);
    int** C22 = addMatrix(t14, M6, half);

    // Assemble the final n x n result.
    int** result = createMatrix(n);
    setQuadrant(result, C11, n, 0, 0);
    setQuadrant(result, C12, n, 0, half);
    setQuadrant(result, C21, n, half, 0);
    setQuadrant(result, C22, n, half, half);

    // Free every temporary matrix used along the way.
    deleteMatrix(A11, half); deleteMatrix(A12, half);
    deleteMatrix(A21, half); deleteMatrix(A22, half);
    deleteMatrix(B11, half); deleteMatrix(B12, half);
    deleteMatrix(B21, half); deleteMatrix(B22, half);
    deleteMatrix(t1, half);  deleteMatrix(t2, half);
    deleteMatrix(t3, half);  deleteMatrix(t4, half);
    deleteMatrix(t5, half);  deleteMatrix(t6, half);
    deleteMatrix(t7, half);  deleteMatrix(t8, half);
    deleteMatrix(t9, half);  deleteMatrix(t10, half);
    deleteMatrix(t11, half); deleteMatrix(t12, half);
    deleteMatrix(t13, half); deleteMatrix(t14, half);
    deleteMatrix(M1, half);  deleteMatrix(M2, half);
    deleteMatrix(M3, half);  deleteMatrix(M4, half);
    deleteMatrix(M5, half);  deleteMatrix(M6, half);
    deleteMatrix(M7, half);
    deleteMatrix(C11, half); deleteMatrix(C12, half);
    deleteMatrix(C21, half); deleteMatrix(C22, half);

    return result;
}

bool matricesEqual(int** A, int** B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != B[i][j]) return false;
    return true;
}
