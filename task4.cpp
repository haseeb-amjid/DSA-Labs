#include "task4.h"

// Naive pattern matching: try every starting position in 'text' and
// check character-by-character whether 'pattern' matches from there.
int findPattern(const string &text, const string &pattern) {
    int n = (int)text.length();
    int m = (int)pattern.length();

    // Convention: an empty pattern matches at index 0.
    if (m == 0) return 0;

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i; // full pattern matched starting at i
        }
    }
    return -1; // no match found
}
