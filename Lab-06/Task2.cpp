#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
template <typename T>
class Stack
{
private:
    T *data;
    int capacity;
    int topIndex;
    void grow()
    {
        T *temp = new T[capacity * 2];
        for (int i = 0; i <= topIndex; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity = capacity * 2;
    }
public:
    Stack()
    {
        capacity = 10;
        data = new T[capacity];
        topIndex = -1;
    }
    ~Stack()
    {
        delete[] data;
    }
    bool isEmpty()
    {
        return topIndex == -1;
    }
    void push(T x)
    {
        if (topIndex == capacity - 1)
        {
            grow();
        }
        topIndex++;
        data[topIndex] = x;
    }
    T pop()
    {
        if (isEmpty())
        {
            return T();
        }
        T x = data[topIndex];
        topIndex--;
        return x;
    }
    T peek()
    {
        if (isEmpty())
        {
            return T();
        }
        return data[topIndex];
    }
};
bool isMatchingPair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}
bool isValidBrackets(string s)
{
    Stack<char> st;
    for (int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[')
        {
            st.push(c);
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            if (st.isEmpty())
            {
                return false;
            }
            char top = st.pop();
            if (!isMatchingPair(top, c))
            {
                return false;
            }
        }
    }
    return st.isEmpty();
}
string getTagName(string text)
{
    string name = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ' || text[i] == '/' || text[i] == '\t')
        {
            break;
        }
        name += text[i];
    }
    return name;
}
pair<bool, vector<string> > validate_markup(string s)
{
    vector<string> errors;
    Stack<string> st;
    int i = 0;
    int n = s.length();
    while (i < n)
    {
        if (s[i] == '<')
        {
            int end = s.find('>', i);
            if (end == string::npos)
            {
                errors.push_back("Tag at position " + to_string(i) + " is missing '>'");
                break;
            }
            string inside = s.substr(i + 1, end - i - 1);
            if (inside.empty())
            {
                errors.push_back("Empty tag at position " + to_string(i));
            }
            else if (inside[0] == '/')
            {
                string name = getTagName(inside.substr(1));
                if (st.isEmpty())
                {
                    errors.push_back("Closing tag </" + name + "> at position " + to_string(i) + " has no opening tag");
                }
                else
                {
                    string top = st.pop();
                    if (top != name)
                    {
                        errors.push_back("Expected </" + top + "> but found </" + name + "> at position " + to_string(i));
                    }
                }
            }
            else if (inside[0] == '!' || inside[0] == '?')
            {
                i = end + 1;
                continue;
            }
            else if (inside[inside.length() - 1] == '/')
            {
                i = end + 1;
                continue;
            }
            else
            {
                st.push(getTagName(inside));
            }

            i = end + 1;
        }
        else
        {
            i++;
        }
    }
    while (!st.isEmpty())
    {
        errors.push_back("Unclosed tag <" + st.pop() + ">");
    }
    return make_pair(errors.empty(), errors);
}
void showMarkupResult(string s)
{
    pair<bool, vector<string> > result = validate_markup(s);
    cout << "Input: " << s << endl;
    if (result.first)
    {
        cout << "Result: Valid" << endl;
    }
    else
    {
        cout << "Result: Invalid" << endl;
        for (int i = 0; i < result.second.size(); i++)
        {
            cout << "  Error " << i + 1 << ": " << result.second[i] << endl;
        }
    }
}
void runSampleTests()
{
    string bracketTests[] = {"{[()]}", "([)]", "((()", "a(b)c[d]{e}", "", "}{"};
    cout << "\n--- Bracket Validator Tests ---" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "\"" << bracketTests[i] << "\" -> " << (isValidBrackets(bracketTests[i]) ? "Valid" : "Invalid") << endl;
    }
    string markupTests[] = {
        "<html><body><p>Hello</p></body></html>",
        "<div><p>Text</div></p>",
        "<div><br/><img src=\"a.png\"/></div>",
        "<a><b>text</b>",
        "</div>",
        "<div><p>Hello</p>",
        "<div class=\"box\"><span>Hi</span></div>"};
    cout << "\n--- Markup Validator Tests ---" << endl;
    for (int i = 0; i < 7; i++)
    {
        showMarkupResult(markupTests[i]);
        cout << endl;
    }
}
int main()
{
    int choice;
    string input;
    do
    {
        cout << "\n===== Expression Validators =====" << endl;
        cout << "1. Validate brackets" << endl;
        cout << "2. Validate HTML/XML tags" << endl;
        cout << "3. Run sample tests" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        if (!(cin >> choice))
        {
            break;
        }
        cin.ignore();
        switch (choice)
        {
        case 1:
            cout << "Enter string: ";
            getline(cin, input);
            if (isValidBrackets(input))
            {
                cout << "Brackets are balanced" << endl;
            }
            else
            {
                cout << "Brackets are NOT balanced" << endl;
            }
            break;
        case 2:
            cout << "Enter markup: ";
            getline(cin, input);
            showMarkupResult(input);
            break;
        case 3:
            runSampleTests();
            break;
        case 0:
            cout << "Exiting program" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);
    return 0;
}