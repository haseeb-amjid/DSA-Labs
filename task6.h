#ifndef TASK6_H
#define TASK6_H

// Finds the mode(s) of 'arr' (size 'n') — the value(s) with the highest frequency.
// Fills 'modes' with every value tied for the highest frequency and sets
// 'modeCount' to how many such values were found. 'maxFrequency' is set to
// that highest frequency.
// Returns false if the array is empty (n == 0); returns true otherwise.
// Assumes at most 100 distinct values in 'arr'.
bool findMode(int arr[], int n, int modes[], int &modeCount, int &maxFrequency);

#endif
