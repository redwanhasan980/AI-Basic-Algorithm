#include <bits/stdc++.h>
using namespace std;

// Function to shuffle the puzzle randomly
void randomShuffle(vector<vector<int>> &state)
{
    vector<int> flat;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            flat.push_back(state[i][j]);
        }
    }
    random_shuffle(flat.begin(), flat.end());
    int idx = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            state[i][j] = flat[idx++];
        }
    }
}

int calculateHeuristic(vector<vector<int>> &state, vector<vector<int>> &goal)
{
    int heuristic = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] != 0)
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        if (state[i][j] == goal[x][y])
                        {
                            heuristic += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return heuristic;
}
int main()
{
    srand(time(0)); // Seed for random shuffle
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<vector<int>> State(3, vector<int>(3));
    vector<vector<int>> InitialState(3, vector<int>(3));
    vector<vector<int>> GoalState(3, vector<int>(3));
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cin >> State[i][j];
            InitialState[i][j] = State[i][j];
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cin >> GoalState[i][j];
        }
    }

    int restartCount = 0;
    int maxRestarts = 100; // Maximum number of restarts
    int it = 1;
    while (true)
    {
        int h = calculateHeuristic(State, GoalState);
        cout << "-----------------------" << endl;
        cout << "Iteration: " << it++ << endl;
        cout << "Current Heuristic: " << h << endl;
        cout << "Current State: " << endl;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                cout << State[i][j] << " ";
            }
            cout << endl;
        }
        if (h == 0)
        {
            cout << "Goal Found" << endl;
            break;
        }
        vector<vector<int>> neibours[5];

        int blankX, blankY;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (State[i][j] == 0)
                {
                    blankX = i;
                    blankY = j;
                }
            }
        }
        // Blank Space move up if possible
        if (blankX - 1 >= 0)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX - 1][blankY]);
            neibours[0] = newState;
        }
        else
        {
            neibours[0] = State;
        }
        // Blank Space move down if possible
        if (blankX + 1 < 3)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX + 1][blankY]);
            neibours[1] = newState;
        }
        else
        {
            neibours[1] = State;
        }
        // Blank Space move left if possible
        if (blankY - 1 >= 0)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX][blankY - 1]);
            neibours[2] = newState;
        }
        else
            neibours[2] = State;
        // Blank Space move right if possible
        if (blankY + 1 < 3)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX][blankY + 1]);
            neibours[3] = newState;
        }
        else
            neibours[3] = State;

        int minHeuristic = INT_MAX;
        int index = -1;
        for (i = 0; i < 4; i++)
        {
            int h1 = calculateHeuristic(neibours[i], GoalState);
            if (h1 < minHeuristic)
            {
                minHeuristic = h1;
                index = i;
            }
        }
        if (minHeuristic >= h)
        {
            cout << "No better neighbour. Local Minima reached." << endl;
            restartCount++;
            if (restartCount > maxRestarts)
            {
                cout << "Maximum restarts reached. Failed to find goal." << endl;
                break;
            }
            cout << "\n=== RANDOM RESTART #" << restartCount << " ===" << endl;
            // Shuffle to get a new random state
            State = InitialState;
            randomShuffle(State);
            continue; // Continue with the new random state
        }
        else
            State = neibours[index];
    }
}