#include <iostream>
using namespace std;
int main()
{
    int rows, cols;
    do
    {
        cout << "Enter number of students: ";
        cin >> rows;
        if (rows <= 0) cout << "Invalid" << endl;
    }
    while (rows <= 0);
    do
    {
        cout << "Enter number of subjects: ";
        cin >> cols;
        if (cols <= 0) cout << "Invalid" << endl;
    }
    while (cols <= 0);
    // Allocate array of row pointers, then allocate each row
    int **marks = new int*[rows];
    for (int r = 0; r < rows; r++)
    {
        marks[r] = new int[cols];
    }
    // Read marks (0-100 assumed valid)
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << "Student " << (r+1) << ", Subject " << (c+1) << " mark: ";
            cin >> *(*(marks + r) + c);
        }
    }
    // Display the matrix
    cout << "\nMarks Matrix:" << endl;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << *(*(marks + r) + c) << "\t";
        }
        cout << endl;
    }
    // Totals and highest scorer (first student's total sets the initial best)
    int bestTotal = 0, bestStudent = 1;
    for (int r = 0; r < rows; r++)
    {
        int total = 0;
        for (int c = 0; c < cols; c++)
        {
            total += marks[r][c];
        }
        if (r == 0 || total > bestTotal)
        {
            bestTotal = total;
            bestStudent = r + 1;
        }
    }
    cout << "\nStudent " << bestStudent << " has the highest total: " << bestTotal << endl;
    for (int r = 0; r < rows; r++)
    {
        delete[] marks[r];
    }
    delete[] marks;
    marks = nullptr;
    return 0;
}