#include "task6.h"

bool findMode(int arr[], int n, int modes[], int &modeCount, int &maxFrequency) {
    modeCount = 0;
    maxFrequency = 0;

    if (n == 0) return false;

    const int MAX_DISTINCT = 100;
    int distinctValues[MAX_DISTINCT];
    int frequencies[MAX_DISTINCT];
    int distinctCount = 0;

    // Count the frequency of every distinct value in the array.
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < distinctCount; j++) {
            if (distinctValues[j] == arr[i]) {
                frequencies[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            distinctValues[distinctCount] = arr[i];
            frequencies[distinctCount] = 1;
            distinctCount++;
        }
    }

    // Find the highest frequency.
    for (int j = 0; j < distinctCount; j++) {
        if (frequencies[j] > maxFrequency) {
            maxFrequency = frequencies[j];
        }
    }

    // Collect every value that has the highest frequency (handles ties).
    for (int j = 0; j < distinctCount; j++) {
        if (frequencies[j] == maxFrequency) {
            modes[modeCount] = distinctValues[j];
            modeCount++;
        }
    }

    return true;
}
