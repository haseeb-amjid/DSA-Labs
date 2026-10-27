#include <iostream>
#include <vector>
using namespace std;
pair<int, int> findPeak(vector<vector<int>>& a)
{
    int rows = a.size();
    int cols = a[0].size();
    int left = 0;
    int right = cols - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int maxRow = 0;
        for (int i = 1; i < rows; i++)
        {
            if (a[i][mid] > a[maxRow][mid])
            {
                maxRow = i;
            }
        }
        int current = a[maxRow][mid];
        int leftValue = (mid > 0) ? a[maxRow][mid - 1] : -1;
        int rightValue = (mid < cols - 1) ? a[maxRow][mid + 1] : -1;
        if (current >= leftValue && current >= rightValue)
                {
            return {maxRow, mid};
        }
                if (leftValue > current)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return {-1, -1};
}
int main()
{
    int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> a(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> a[i][j];
        }    
    }
    pair<int, int> result = findPeak(a);
    if (result.first != -1)
    {
        cout << "Peak element: " << a[result.first][result.second] << endl;
        cout << "Position: (" << result.first << ", " << result.second << ")" << endl;
    }
    return 0;
}