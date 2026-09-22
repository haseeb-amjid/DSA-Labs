#include <iostream>
#include <string>
#include <cctype>
using namespace std;


bool isPalindrome(const string& s)
{
    string clean = "";
    for (char ch : s)
    {
        if (isalnum(ch))
        {
            clean += tolower(ch);
        }
    }
    int left = 0;
    int right = clean.length() - 1;

    while (left < right)
    {
        if (clean[left] != clean[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
        if (isPalindrome(s))
        {
        cout << s << " is a palindrome." << endl;
    } else
    {
        cout << s << " is NOT a palindrome." << endl;
    }
    return 0;
}
