#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool letterOrDigit(char c)
{
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}
struct Node
{
    char data;
    Node *left, *right;

    // Time Complexity: O(1)
    // Space Complexity: O(1)
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
};
// Time Complexity: O(n)
// Space Complexity: O(h)
Node* parse(const string& s, int& i)
{
    if (i >= (int)s.size() || !letterOrDigit(s[i]))
        return nullptr;

    Node* r = new Node(s[i++]);
    if (i < (int)s.size() && s[i] == '(')
    {
        i++;
        r->left = parse(s, i);
        if (i >= (int)s.size() || s[i++] != ',')
            return r;
        r->right = parse(s, i);
        if (i < (int)s.size() && s[i] == ')')
            i++;
    }
    return r;
}
// Time Complexity: O(n)
// Space Complexity: O(h)
bool checkNode(const string& s, int& i)
{
    if (i >= (int)s.size() || !letterOrDigit(s[i]))
        return false;

    i++;
    if (i < (int)s.size() && s[i] == '(')
    {
        i++;
        bool leftChild = false, rightChild = false;
        if (i < (int)s.size() && s[i] != ',')
        {
            if (!checkNode(s, i))
                return false;
            leftChild = true;
        }
        if (i >= (int)s.size() || s[i++] != ',')
            return false;
        if (i < (int)s.size() && s[i] != ')')
        {
            if (!checkNode(s, i))
                return false;
            rightChild = true;
        }
        if (i >= (int)s.size() || s[i++] != ')')
            return false;
        if (!leftChild && !rightChild)
            return false;
    }
    return true;
}
// Time Complexity: O(n)
// Space Complexity: O(h)
bool valid(const string& s)
{
    int i = 0;
    return checkNode(s, i) && i == (int)s.size();
}
// Time Complexity: O(n)
// Space Complexity: O(h)
void preorder(Node* r)
{
    if (!r)
        return;

    cout << r->data << ' ';
    preorder(r->left);
    preorder(r->right);
}
// Time Complexity: O(n)
// Space Complexity: O(h)
void preorderForm(Node* r)
{
    if (!r)
        return;

    cout << r->data;
    if (r->left || r->right)
    {
        cout << '(';
        preorderForm(r->left);
        cout << ',';
        preorderForm(r->right);
        cout << ')';
    }
}
// Time Complexity: O(n)
// Space Complexity: O(h)
void inorder(Node* r)
{
    stack<Node*> s;
    while (r || !s.empty())
    {
        while (r)
        {
            s.push(r);
            r = r->left;
        }
        r = s.top();
        s.pop();
        cout << r->data << ' ';
        r = r->right;
    }
}
// Time Complexity: O(n)
// Space Complexity: O(h)
void postorder(Node* r)
{
    stack<Node*> s;
    Node *cur = r, *last = nullptr;
    while (cur || !s.empty())
    {
        while (cur)
        {
            s.push(cur);
            cur = cur->left;
        }
        Node* top = s.top();
        if (top->right && last != top->right)
        {
            cur = top->right;
        }
        else
        {
            cout << top->data << ' ';
            last = top;
            s.pop();
        }
    }
}
// Time Complexity: O(n)
// Space Complexity: O(h)
int height(Node* r)
{
    if (!r)
        return -1;

    int l = height(r->left);
    int rr = height(r->right);
    return 1 + (l > rr ? l : rr);
}
// Time Complexity: O(n)
// Space Complexity: O(h)
void depths(Node* r, int d)
{
    if (!r)
        return;
    cout << "Node " << r->data << " -> depth " << d << '\n';
    depths(r->left, d + 1);
    depths(r->right, d + 1);
}
// Time Complexity: O(n)
// Space Complexity: O(h)
void freeTree(Node* r)
{
    if (!r)
        return;
    freeTree(r->left);
    freeTree(r->right);
    delete r;
}
int main()
{
    string s = "a(b(d,e),c(,f(g,)))";
    cout << "Tree string: " << s << "\n\n";
    cout << "Validation: "
         << (valid(s) ? "Valid" : "Invalid") << '\n';
    string tests[] = {
        "a(b(d,e),c(,f(g,))",
        "a(b,c))",
        "a(b c)",
        "a(,)",
        "a(b(d,e),c(,f(g,)))x"
    };
    cout << "\nValidation tests:\n";
    for (int j = 0; j < 5; j++)
    {
        cout << tests[j] << " -> "
             << (valid(tests[j]) ? "Valid" : "Invalid") << '\n';
    }
    int i = 0;
    Node* root = parse(s, i);
    cout << "\nPreorder traversal: ";
    preorder(root);
    cout << "\nPreorder string form: ";
    preorderForm(root);
    cout << "\nInorder traversal (stack): ";
    inorder(root);
    cout << "\nPostorder traversal (stack): ";
    postorder(root);
    cout << "\n\nHeight (edges): " << height(root) << '\n';
    cout << "\nNode depths:\n";
    depths(root, 0);
    freeTree(root);
}