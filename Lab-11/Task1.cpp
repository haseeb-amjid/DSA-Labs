#include<iostream>
#include<string>
using namespace std;
struct Node
{
    char ch;
    int freq;
    Node* left;
    Node* right;
};
Node* createNode(char c, int f)
{
    Node* n = new Node;
    n->ch = c;
    n->freq = f;
    n->left = NULL;
    n->right = NULL;
    return n;
}
class MinHeap
{
private:
    Node* arr[100];
    int size;
    void heapifyDown(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && arr[left]->freq < arr[smallest]->freq)
        {
            smallest = left;
        }
        if (right < size && arr[right]->freq < arr[smallest]->freq)
        {
            smallest = right;
        }
        if (smallest != i)
        {
            Node* temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            heapifyDown(smallest);
        }
    }
    void heapifyUp(int i)
    {
        while (i > 0 && arr[(i - 1) / 2]->freq > arr[i]->freq)
        {
            Node* temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }
public:
    MinHeap()
    {
        size = 0;
    }
    int getSize()
    {
        return size;
    }
    void insert(Node* n)
    {
        arr[size] = n;
        heapifyUp(size);
        size++;
    }
    Node* extractMin()
    {
        Node* top = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return top;
    }
};
Node* buildHuffmanTree(string s, int f[], int n)
{
    MinHeap heap;
    for (int i = 0; i < n; i++)
    {
        heap.insert(createNode(s[i], f[i]));
    }
    while (heap.getSize() > 1)
    {
        Node* first = heap.extractMin();
        Node* second = heap.extractMin();
        Node* parent = createNode('$', first->freq + second->freq);
        parent->left = first;
        parent->right = second;
        heap.insert(parent);
    }
    return heap.extractMin();
}
void printCodes(Node* root, string code)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        cout << root->ch << " : " << code << endl;
        return;
    }
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}
int main()
{
    int n;
    string s;
    int f[100];
    cout << "Enter number of characters: ";
    cin >> n;
    cout << "Enter the characters: ";
    cin >> s;
    cout << "Enter the frequencies: ";
    for (int i = 0; i < n; i++)
    {
        cin >> f[i];
    }
    Node* root = buildHuffmanTree(s, f, n);
    cout << "Huffman Codes (Preorder):" << endl;
    printCodes(root, "");
    return 0;
}