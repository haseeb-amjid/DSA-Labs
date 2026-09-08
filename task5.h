#ifndef TASK5_H
#define TASK5_H

// Generates Pascal's Triangle with 'n' rows using a dynamically allocated
// 2D array. Row i (0-indexed) has (i + 1) elements.
// Returns nullptr if n <= 0.
// Caller is responsible for freeing the memory with deleteTriangle().
int** generatePascalTriangle(int n);

// Frees the memory allocated by generatePascalTriangle().
void deleteTriangle(int** triangle, int n);

#endif
