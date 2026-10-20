#include <iostream>
#include <stack>
#include <string>
using namespace std;
struct Student 
{
    int id;
    string name;
    float gpa;
    Student *left, *right;
    Student(int i, string n, float g) : id(i), name(n), gpa(g), left(nullptr), right(nullptr) {}
};
//Time complexity O(h), worst case O(n)
//Space complexity O(h)
Student* Insert(Student* r, int id, string name, float gpa) 
{
    if (!r) return new Student(id, name, gpa);
    if (id < r->id) r->left = Insert(r->left, id, name, gpa);
    else if (id > r->id) r->right = Insert(r->right, id, name, gpa);
    else cout << "Student with ID " << id << " already exists.\n";
    return r;
}
//Time complexity O(h), worst case O(n)
//Space complexity O(h)
Student* Search(Student* r, int id) 
{
    if (!r || r->id == id) return r;
    return id < r->id ? Search(r->left, id) : Search(r->right, id);
}
//Time complexity O(h)
//Space complexity O(1)
Student* minNode(Student* r) 
{
    while (r->left) r = r->left;
    return r;
}
//Time complexity O(h), worst case O(n)
//Space complexity O(h)
Student* Delete(Student* r, int id, bool& done) 
{
    if (!r) return nullptr;
    if (id < r->id) r->left = Delete(r->left, id, done);
    else if (id > r->id) r->right = Delete(r->right, id, done);
    else {
        done = true;
        if (!r->left || !r->right) {
            Student* next = r->left ? r->left : r->right;
            delete r;
            return next;
        }
        Student* next = minNode(r->right);
        r->id = next->id;
        r->name = next->name;
        r->gpa = next->gpa;
        bool unused = false;
        r->right = Delete(r->right, next->id, unused);
    }
    return r;
}
//Time complexity O(L), where L is the name length
//Space complexity O(1) extra
void display(Student* r) 
{
    if (r) cout << r->id << "  " << r->name << "  GPA: " << r->gpa << '\n';
}
//Time complexity O(n)
//Space complexity O(h)
void inorder(Student* r) 
{
    if (!r) return;
    inorder(r->left); display(r); inorder(r->right);
}
//Time coplexity O(n)
//Space complexity O(h)
int count(Student* r) 
{
    return r ? 1 + count(r->left) + count(r->right) : 0;
}
//Time coplexity O(n)
//Space complexity O(h)
void extremes(Student* r, Student*& high, Student*& low) {
    if (!r) return;
    if (!high || r->gpa > high->gpa) high = r;
    if (!low || r->gpa < low->gpa) low = r;
    extremes(r->left, high, low);
    extremes(r->right, high, low);
}
//Time coplexity O(n)
//Space complexity O(h)
int above(Student* r, float g) {
    if (!r) return 0;
    int n = above(r->left, g);
    if (r->gpa > g) { display(r); n++; }
    return n + above(r->right, g);
}
//Time coplexity O(n)
//Space complexity O(h)
void freeTree(Student* r) {
    if (!r) return;
    freeTree(r->left); freeTree(r->right); delete r;
}
int main() 
{
    Student* root = nullptr;
    root = Insert(root, 1005, "Ali Khan", 3.45f);
    root = Insert(root, 1002, "Sara Ahmed", 3.80f);
    root = Insert(root, 1008, "Usman Tariq", 2.75f);
    root = Insert(root, 1001, "Ayesha Noor", 3.20f);
    root = Insert(root, 1004, "Hamza Raza", 2.40f);
    root = Insert(root, 1007, "Fatima Zahra", 3.95f);
    root = Insert(root, 1010, "Bilal Hussain", 2.90f);
    int choice;
    do {
        cout << "\n===== Student Record Management System =====\n"
             << "1. Insert student\n2. Search student by ID\n3. Delete student by ID\n"
             << "4. Display all students (sorted by ID)\n5. Count total students\n"
             << "6. Show highest and lowest GPA\n7. Show students above a GPA threshold\n0. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            int id; string name; float gpa;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter name: "; cin.ignore(1000, '\n'); getline(cin, name);
            cout << "Enter GPA: "; cin >> gpa;
            root = Insert(root, id, name, gpa);
        } else if (choice == 2) {
            int id; cout << "Enter ID to search: "; cin >> id;
            Student* s = Search(root, id);
            if (s) display(s); else cout << "No student found with ID " << id << ".\n";
        } else if (choice == 3) {
            int id; bool done = false;
            cout << "Enter ID to delete: "; cin >> id;
            root = Delete(root, id, done);
            cout << (done ? "Student deleted.\n" : "No student found with that ID.\n");
        } else if (choice == 4) {
            if (!root) cout << "No records to display.\n";
            else inorder(root);
        } else if (choice == 5) cout << "Total students: " << count(root) << '\n';
        else if (choice == 6) {
            Student *high = nullptr, *low = nullptr;
            extremes(root, high, low);
            if (!high) cout << "No records available.\n";
            else {
                cout << "Highest GPA:\n"; display(high);
                cout << "Lowest GPA:\n"; display(low);
            }
        } else if (choice == 7) {
            float g; cout << "Enter GPA threshold: "; cin >> g;
            cout << "Students with GPA above " << g << ":\n";
            if (!above(root, g)) cout << "No students found.\n";
        } else if (choice != 0) cout << "Invalid choice. Try again.\n";
    } while (choice != 0);
    freeTree(root);
    return 0;
}
