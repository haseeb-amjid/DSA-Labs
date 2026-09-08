#include <iostream>
#include "task4.h"
using namespace std;

int main() {
    // Test case 1: pattern at the beginning
    string text1 = "hello world";
    string pattern1 = "hello";
    cout << "Test 1 (pattern at beginning): index = "
         << findPattern(text1, pattern1) << " (expected 0)" << endl;

    // Test case 2: pattern at the end
    string text2 = "hello world";
    string pattern2 = "world";
    cout << "Test 2 (pattern at end): index = "
         << findPattern(text2, pattern2) << " (expected 6)" << endl;

    // Test case 3: pattern not present
    string text3 = "hello world";
    string pattern3 = "xyz";
    cout << "Test 3 (pattern not present): index = "
         << findPattern(text3, pattern3) << " (expected -1)" << endl;

    // Test case 4: empty pattern
    string text4 = "hello world";
    string pattern4 = "";
    cout << "Test 4 (empty pattern): index = "
         << findPattern(text4, pattern4) << " (expected 0)" << endl;

    return 0;
}
