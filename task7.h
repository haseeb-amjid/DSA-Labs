#ifndef TASK7_H
#define TASK7_H

// Allocates an n x n matrix (dynamic 2D array) and initializes it to 0.
int** createMatrix(int n);

// Frees the memory allocated for an n x n matrix.
void deleteMatrix(int** matrix, int n);

// Standard O(n^3) matrix multiplication: returns A * B for n x n matrices.
int** standardMultiply(int** A, int** B, int n);

// Strassen's divide-and-conquer algorithm for multiplying two n x n
// matrices. 'n' must be a power of 2.
int** strassenMultiply(int** A, int** B, int n);

// Returns true if the two n x n matrices are element-wise equal.
bool matricesEqual(int** A, int** B, int n);

#endif
