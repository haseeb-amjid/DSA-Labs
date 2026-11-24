#include <iostream>
#include <algorithm>
using namespace std;
struct Node
{
    int data;
    int height;
    Node* left;
    Node* right;
};
Node* createNode(int value)
{
    Node* n = new Node;
    n->data = value;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}
int getHeight(Node* n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->height;
}
void updateHeight(Node* n)
{
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}
Node* rotateRight(Node* y)
{
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}
Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}
Node* rebalance(Node* n)
{
    updateHeight(n);
    int balance = getHeight(n->left) - getHeight(n->right);
    if (balance > 1)
    {
        if (getHeight(n->left->left) < getHeight(n->left->right))
        {
            n->left = rotateLeft(n->left);
        }
        return rotateRight(n);
    }
    if (balance < -1)
    {
        if (getHeight(n->right->right) < getHeight(n->right->left))
        {
            n->right = rotateRight(n->right);
        }
        return rotateLeft(n);
    }
    return n;
}
Node* insertNode(Node* root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }
    if (value < root->data)
    {
        root->left = insertNode(root->left, value);
    }
    else
    {
        root->right = insertNode(root->right, value);
    }
    return rebalance(root);
}
Node* deleteNode(Node* root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            Node* child = root->left;
            if (child == NULL)
            {
                child = root->right;
            }
            delete root;
            return child;
        }
        Node* next = root->right;
        while (next->left != NULL)
        {
            next = next->left;
        }
        root->data = next->data;
        root->right = deleteNode(root->right, next->data);
    }
    return rebalance(root);
}
void printTree(Node* root, int level)
{
    if (root == NULL)
    {
        return;
    }
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        cout << "     ";
    }
    cout << root->data << endl;
    printTree(root->left, level + 1);
}
void fillSorted(Node* root, int arr[], int& count)
{
    if (root == NULL)
    {
        return;
    }
    fillSorted(root->left, arr, count);
    arr[count] = root->data;
    count++;
    fillSorted(root->right, arr, count);
}
int main(){
    Node* root = NULL;
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)    {
        int value;
        cin >> value;
        root = insertNode(root, value);
        cout << "Tree after inserting " << value << ":" << endl;
        printTree(root, 0);
    }
    int criteria;
    int k;
    cout << "Criteria (1 = Maximum, 2 = Minimum, 3 = Sum of k largest): ";
    cin >> criteria;
    cout << "Enter k: ";
    cin >> k;
    if (k > n)    {
        k = n;
    }
    int sorted[100];
    int count = 0;
    fillSorted(root, sorted, count);
    int top[100];
    int sum = 0;
    for (int i = 0; i < k; i++)    {
        if (criteria == 2)        {
            top[i] = sorted[i];
        }
        else        {
            top[i] = sorted[count - 1 - i];
        }
        sum = sum + top[i];
    }
    cout << "Top " << k << " elements: ";
    for (int i = 0; i < k; i++)    {
        cout << top[i] << " ";
    }
    cout << endl;
    if (criteria == 3)    {
        cout << "Sum = " << sum << endl;
    }
    for (int i = 0; i < k; i++)    {
        root = deleteNode(root, top[i]);
        cout << "Tree after deleting " << top[i] << ":" << endl;
        printTree(root, 0);
    }
    return 0;
}