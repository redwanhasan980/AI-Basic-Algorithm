#include <bits/stdc++.h>
using namespace std;

char board[3][3];
const char HUMAN = 'O';
const char AI = 'X';

void initBoard()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard()
{
    cout << "\n";
    for (int i = 0; i < 3; i++)
    {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << endl;
        if (i < 2)
            cout << "---|---|---" << endl;
    }
    cout << endl;
}

char checkWinner()
{
    // Check rows and columns
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    // Check for draw
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return ' '; // Game continues

    return 'D'; // Draw
}

int minimax(bool isMaximizing)
{
    char winner = checkWinner();

    if (winner == AI)
        return 1;
    if (winner == HUMAN)
        return -1;
    if (winner == 'D')
        return 0;

    if (isMaximizing)
    {
        int bestScore = -INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = AI;
                    int score = minimax(false);
                    board[i][j] = ' ';
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = HUMAN;
                    int score = minimax(true);
                    board[i][j] = ' ';
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

void aiMove()
{
    int bestScore = -INT_MAX;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = AI;
                int score = minimax(false);
                board[i][j] = ' ';

                if (score > bestScore)
                {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    board[moveRow][moveCol] = AI;
    cout << "AI plays at (" << moveRow << ", " << moveCol << ")" << endl;
}

void humanMove()
{
    int row, col;
    while (true)
    {
        cout << "Your move (row col): ";
        cin >> row >> col;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = HUMAN;
            break;
        }
        cout << "Invalid move! Try again." << endl;
    }
}

int main()
{
    initBoard();

    cout << "=== TIC-TAC-TOE with MINIMAX ===" << endl;
    cout << "You are O, AI is X" << endl;
    cout << "Enter position as: row col (0-2)" << endl;

    printBoard();

    while (true)
    {
        humanMove();
        printBoard();

        char result = checkWinner();
        if (result != ' ')
        {
            if (result == HUMAN)
                cout << "You win!" << endl;
            else if (result == AI)
                cout << "AI wins!" << endl;
            else
                cout << "It's a draw!" << endl;
            break;
        }

        cout << "AI is thinking..." << endl;
        aiMove();
        printBoard();

        result = checkWinner();
        if (result != ' ')
        {
            if (result == HUMAN)
                cout << "You win!" << endl;
            else if (result == AI)
                cout << "AI wins!" << endl;
            else
                cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}