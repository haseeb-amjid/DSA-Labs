#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void moveDisk(vector<int>& a, vector<int>& b, char nameA, char nameB)
{
    if (a.empty())
    {
        int disk = b.back();
        b.pop_back();
        a.push_back(disk);
        cout << "Move disk " << disk << " from "
             << nameB << " to " << nameA << endl;
    }
    else if (b.empty())
    {
        int disk = a.back();
        a.pop_back();
        b.push_back(disk);

        cout << "Move disk " << disk << " from "
             << nameA << " to " << nameB << endl;
    }
    else if (a.back() < b.back())
    {
        int disk = a.back();
        a.pop_back();
        b.push_back(disk);

        cout << "Move disk " << disk << " from "
             << nameA << " to " << nameB << endl;
    }
    else
    {
        int disk = b.back();
        b.pop_back();
        a.push_back(disk);

        cout << "Move disk " << disk << " from "
             << nameB << " to " << nameA << endl;
    }
}
void towerOfHanoi(int n)
{
    if (n <= 0)
    {
        cout << "Invalid number of disks" << endl;
        return;
    }
    vector<int> pegs[3];
    for (int i = n; i >= 1; i--)
    {
        pegs[0].push_back(i);
    }
    int source = 0;
    int auxiliary = 1;
    int destination = 2;
    if (n % 2 == 0)
    {
        swap(auxiliary, destination);
    }
    long long totalMoves = (1LL << n) - 1;
    cout << "Total moves: " << totalMoves << endl;
    for (long long i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 1)
        {
            moveDisk(pegs[source], pegs[destination], 'A', 'C');
        }
        else if (i % 3 == 2)
        {
            moveDisk(pegs[source], pegs[auxiliary], 'A', 'B');
        }
        else
        {
            moveDisk(pegs[auxiliary], pegs[destination], 'B', 'C');
        }
    }
}
int main()
{
    int n;
    cin >> n;
    towerOfHanoi(n);\
    return 0;
}