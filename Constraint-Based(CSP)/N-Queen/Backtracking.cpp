#include <bits/stdc++.h>
using namespace std;
vector<int> rows(100);
vector<int> rightDiagonal(200);
vector<int> leftDiagonal(200);
bool placeQueen(int col, vector<vector<int>> &board, int n)
{
    if (col >= n)
    {
        return true;
    }
    for (int row = 0; row < n; row++)
    {
        if (rows[row] || rightDiagonal[row + col] || leftDiagonal[n - 1 + row - col])
        {
            continue;
        }
        board[row][col] = 1;
        rows[row] = 1;
        rightDiagonal[row + col] = 1;
        leftDiagonal[n - 1 + row - col] = 1;
        if (placeQueen(col + 1, board, n))
        {
            return true;
        }
        board[row][col] = 0;
        rows[row] = 0;
        rightDiagonal[row + col] = 0;
        leftDiagonal[n - 1 + row - col] = 0;
    }
    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (placeQueen(0, board, n))
    {
        cout << "Solution found:" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution exists." << endl;
    }
    return 0;
}