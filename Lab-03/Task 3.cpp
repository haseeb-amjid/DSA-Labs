#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* head = NULL;
void insertAtHead(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    cout << "Inserted " << value << " at head." << endl;
}
void insertAtThird(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    if (head == NULL) {
        head = newNode;
        newNode->next = NULL;
        cout << "List was empty, inserted as first node." << endl;
        return;
    }
    if (head->next == NULL) {
        cout << "Less than 2 nodes in list. Inserting at the end." << endl;
        head->next = newNode;
        newNode->next = NULL;
        return;
    }
    Node* temp = head;
    temp = temp->next; // Move to 2nd node
    newNode->next = temp->next;
    temp->next = newNode;
    cout << "Inserted " << value << " at 3rd position." << endl;
}
void displayList() {
    if (head == NULL) {
        cout << "List is empty. NULL" << endl;
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
void deleteLast() {
    if (head == NULL) {
        cout << "List is empty. Nothing to delete." << endl;
        return;
    }
    if (head->next == NULL) {
        delete head;
        head = NULL;
        cout << "Deleted the only node." << endl;
        return;
    }
    Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    cout << "Deleted last node: " << temp->next->data << endl;
    delete temp->next;
    temp->next = NULL;
}
int countNodes() {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void reverseList() {
    Node* prev = NULL;
    Node* current = head;
    Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    head = prev;
    cout << "List reversed." << endl;
}
int searchValue(int value) {
    Node* temp = head;
    int position = 0;

    while (temp != NULL) {
        if (temp->data == value) {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1; // Not found
}
int main() {
    int choice, value;
    do {
        cout << "\n----- MENU -----" << endl;
        cout << "1. Insert at Head" << endl;
        cout << "2. Insert at 3rd Position" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Delete Last Node" << endl;
        cout << "5. Count Nodes" << endl;
        cout << "6. Reverse List" << endl;
        cout << "7. Search Value" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                insertAtHead(value);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> value;
                insertAtThird(value);
                break;
            case 3:
                displayList();
                break;
            case 4:
                deleteLast();
                displayList();
                break;
            case 5:
                cout << "Number of nodes: " << countNodes() << endl;
                break;
            case 6:
                reverseList();
                displayList();
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> value;
                {
                    int pos = searchValue(value);
                    if (pos == -1) {
                        cout << "Value not found." << endl;
                    } else {
                        cout << "Value found at position: " << pos << endl;
                    }
                }
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    return 0;
}
