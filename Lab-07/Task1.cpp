#include <iostream>
#include <stack>
#include <string>
using namespace std;
//Time coplexity O(1)
//Space complexity O(1)
bool letterOrDigit(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}
struct Node 
{
    char data;
    Node *left, *right;
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
};

struct BNode 
{
    int data;
    BNode *left, *right;
    BNode(int n) : data(n), left(nullptr), right(nullptr) {}
};
//Time coplexity O(n)
//Space complexity O(h)
Node* parse(const string& s, int& i) 
{
    if (i >= (int)s.size() || !letterOrDigit(s[i])) return nullptr;
    Node* r = new Node(s[i++]);
    if (i < (int)s.size() && s[i] == '(') {
        i++;
        r->left = parse(s, i);
        if (i >= (int)s.size() || s[i++] != ',') return r;
        r->right = parse(s, i);
        if (i < (int)s.size() && s[i] == ')') i++;
    }
    return r;
}
//Time coplexity O(n)
//Space complexity O(h)
bool checkNode(const string& s, int& i) 
{
    if (i >= (int)s.size() || !letterOrDigit(s[i])) return false;
    i++;
    if (i < (int)s.size() && s[i] == '(') {
        i++;
        bool leftChild = false, rightChild = false;
        if (i < (int)s.size() && s[i] != ',') {
            if (!checkNode(s, i)) return false;
            leftChild = true;
        }
        if (i >= (int)s.size() || s[i++] != ',') return false;
        if (i < (int)s.size() && s[i] != ')') {
            if (!checkNode(s, i)) return false;
            rightChild = true;
        }
        if (i >= (int)s.size() || s[i++] != ')') return false;
        if (!leftChild && !rightChild) return false;
    }
    return true;
}
//Time coplexity O(n)
//Space complexity O(h)
bool valid(const string& s) 
{
    int i = 0;
    return checkNode(s, i) && i == (int)s.size();
}
//Time coplexity O(n)
//Space complexity O(h)
void preorder(Node* r) 
{
    if (!r) return;
    cout << r->data << ' ';
    preorder(r->left);
    preorder(r->right);
}
//Time coplexity O(n)
//Space complexity O(h)
void preorderForm(Node* r) 
{
    if (!r) return;
    cout << r->data;
    if (r->left || r->right) {
        cout << '(';
        preorderForm(r->left);
        cout << ',';
        preorderForm(r->right);
        cout << ')';
    }
}
//Time coplexity O(n)
//Space complexity O(h)
void inorder(Node* r) 
{
    stack<Node*> s;
    while (r || !s.empty()) {
        while (r) { s.push(r); r = r->left; }
        r = s.top(); s.pop();
        cout << r->data << ' ';
        r = r->right;
    }
}
//Time coplexity O(n)
//Space complexity O(h)
void postorder(Node* r) 
{
    stack<Node*> s;
    Node *cur = r, *last = nullptr;
    while (cur || !s.empty()) {
        while (cur) { s.push(cur); cur = cur->left; }
        Node* top = s.top();
        if (top->right && last != top->right) cur = top->right;
        else { cout << top->data << ' '; last = top; s.pop(); }
    }
}
//Time coplexity O(n)
//Space complexity O(h)
int height(Node* r) 
{
    if (!r) return -1;
    int l = height(r->left), rr = height(r->right);
    return 1 + (l > rr ? l : rr);
}
//Time coplexity O(n)
//Space complexity O(h)
void depths(Node* r, int d) 
{
    if (!r) return;
    cout << "Node " << r->data << " -> depth " << d << '\n';
    depths(r->left, d + 1);
    depths(r->right, d + 1);
}
//Time coplexity O(h), worst case O(n)
//Space complexity O(h)
BNode* add(BNode* r, int n) 
{
    if (!r) return new BNode(n);
    if (n < r->data) r->left = add(r->left, n);
    else if (n > r->data) r->right = add(r->right, n);
    return r;
}
//Time coplexity O(n)
//Space complexity O(h)
void showBST(BNode* r) 
{
    if (!r) return;
    showBST(r->left);
    cout << r->data << ' ';
    showBST(r->right);
}
//Time coplexity O(n)
//Space complexity O(h)
void freeTree(Node* r) 
{
    if (!r) return;
    freeTree(r->left); freeTree(r->right); delete r;
}
//Time coplexity O(n)
//Space complexity O(h)
void freeBST(BNode* r) 
{
    if (!r) return;
    freeBST(r->left); freeBST(r->right); delete r;
}
int main() 
{
    string s = "a(b(d,e),c(,f(g,)))";
    cout << "Tree string: " << s << "\n\n";
    cout << "Validation: " << (valid(s) ? "Valid" : "Invalid") << '\n';
    string tests[] = {"a(b(d,e),c(,f(g,))", "a(b,c))", "a(b c)", "a(,)", "a(b(d,e),c(,f(g,)))x"};
    for (int j = 0; j < 5; j++)
        cout << tests[j] << " -> " << (valid(tests[j]) ? "Valid" : "Invalid") << '\n';

    int i = 0;
    Node* root = parse(s, i);
    cout << "\nPreorder (recursive): "; preorder(root);
    cout << "\nPreorder string form: "; preorderForm(root);
    cout << "\nInorder (stack): "; inorder(root);
    cout << "\nPostorder (stack): "; postorder(root);
    cout << "\n\nHeight (edges): " << height(root) << '\n';
    depths(root, 0);
    int nums[] = {50, 30, 70, 20, 40, 60, 80};
    BNode* bst = nullptr;
    for (int j = 0; j < 7; j++) bst = add(bst, nums[j]);
    cout << "\nBST inorder: "; showBST(bst); cout << '\n';
    freeTree(root); freeBST(bst);
    return 0;
}