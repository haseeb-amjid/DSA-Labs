#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
bool isSafe(int x, int y, int n, vector<vector<int>>& board)
{
    return x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1;
}
int countMoves(int x, int y, int n, vector<vector<int>>& board)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isSafe(nx, ny, n, board))
        {
            count++;
        }
    }
    return count;
}
bool solve(int x, int y, int moveNo, int n, vector<vector<int>>& board)
{
    if (moveNo == n * n)
    {
        return true;
    }
    vector<pair<int, pair<int, int>>> candidates;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isSafe(nx, ny, n, board))
        {
            int degree = countMoves(nx, ny, n, board);
            candidates.push_back({degree, {nx, ny}});
        }
    }
    sort(candidates.begin(), candidates.end());
    for (auto candidate : candidates)
    {
        int nx = candidate.second.first;
        int ny = candidate.second.second;
        board[nx][ny] = moveNo;
        if (solve(nx, ny, moveNo + 1, n, board))
        {
            return true;
        }
        board[nx][ny] = -1;
    }
    return false;
}
int main()
{
    int n, x, y;
    cin >> n >> x >> y;
    if (n <= 0 || x < 0 || x >= n || y < 0 || y >= n)
    {
        cout << "Invalid input" << endl;
        return 0;
    }
    vector<vector<int>> board(n, vector<int>(n, -1));
    board[x][y] = 0;
    if (solve(x, y, 1, n, board))
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << board[i][j] << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No tour found" << endl;
    }
    return 0;
}