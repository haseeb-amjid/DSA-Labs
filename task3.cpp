#include "task3.h"

// Linear scan of the array, recording every index where arr[i] == key.
void findIndices(int arr[], int n, int key, int result[], int &count) {
    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            result[count] = i;
            count++;
        }
    }
}
