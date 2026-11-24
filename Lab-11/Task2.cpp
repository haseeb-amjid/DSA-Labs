#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* next;
};
Node* createNode(int value)
{
    Node* n = new Node;
    n->data = value;
    n->next = NULL;
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
        if (left < size && arr[left]->data < arr[smallest]->data)
        {
            smallest = left;
        }
        if (right < size && arr[right]->data < arr[smallest]->data)
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
        while (i > 0 && arr[(i - 1) / 2]->data > arr[i]->data)
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
    bool isEmpty()
    {
        return size == 0;
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
Node* mergeLists(Node* lists[], int k)
{
    MinHeap heap;
    for (int i = 0; i < k; i++)
    {
        if (lists[i] != NULL)
        {
            heap.insert(lists[i]);
        }
    }
    Node* head = NULL;
    Node* tail = NULL;
    while (!heap.isEmpty())
    {
        Node* smallest = heap.extractMin();
        if (smallest->next != NULL)
        {
            heap.insert(smallest->next);
        }
        smallest->next = NULL;
        if (head == NULL)
        {
            head = smallest;
            tail = smallest;
        }
        else
        {
            tail->next = smallest;
            tail = smallest;
        }
    }
    return head;
}
void printList(Node* head)
{
    while (head != NULL)
    {
        cout << head->data;
        if (head->next != NULL)
        {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}
int main()
{
    int k;
    Node* lists[100];
    cout << "Enter number of linked lists: ";
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int n;
        cout << "Enter size of list " << i + 1 << ": ";
        cin >> n;
        lists[i] = NULL;
        Node* tail = NULL;
        cout << "Enter " << n << " sorted elements: ";
        for (int j = 0; j < n; j++)
        {
            int value;
            cin >> value;
            Node* newNode = createNode(value);
            if (lists[i] == NULL)
            {
                lists[i] = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }
    cout << "Input Lists:" << endl;
    for (int i = 0; i < k; i++)
    {
        printList(lists[i]);
    }
    Node* merged = mergeLists(lists, k);
    cout << "Merged List:" << endl;
    printList(merged);
    return 0;
}