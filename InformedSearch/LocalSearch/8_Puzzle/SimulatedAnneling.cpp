#include <bits/stdc++.h>
using namespace std;

// Calculate Manhattan Distance (heuristic function)
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

// STEP 2e: Calculate acceptance probability using Boltzmann distribution
// Formula: P(accept) = e^(-ΔE/T)
double acceptanceProbability(int currentH, int nextH, double temperature)
{
    // If neighbor is better, always accept (ΔE < 0)
    if (nextH < currentH)
    {
        return 1.0;
    }
    // If neighbor is worse, accept with probability e^(-ΔE/T)
    int deltaE = nextH - currentH;
    return exp(-deltaE / temperature);
}

int main()
{
    srand(time(0)); // Seed for random number generation
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Read initial state and goal state
    vector<vector<int>> State(3, vector<int>(3));
    vector<vector<int>> GoalState(3, vector<int>(3));
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cin >> State[i][j];
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cin >> GoalState[i][j];
        }
    }

    // ============================================================================
    // STEP 1: INITIALIZE SIMULATED ANNEALING PARAMETERS
    // ============================================================================
    double temperature = 100.0;   // Initial temperature (high value for exploration)
    double coolingRate = 0.995;   // Cooling rate (geometric cooling schedule)
    double minTemperature = 0.01; // Minimum temperature threshold (stopping condition)
    int maxIterations = 10000;    // Maximum iterations (safety limit)

    int it = 1; // Iteration counter

    // ============================================================================
    // STEP 2: MAIN LOOP - Continue until temperature drops below threshold
    // ============================================================================
    while (temperature > minTemperature && it <= maxIterations)
    {

        // ========================================================================
        // STEP 2a: EVALUATE CURRENT STATE
        // ========================================================================
        int h = calculateHeuristic(State, GoalState);

        // Display current iteration information
        cout << "-----------------------" << endl;
        cout << "Iteration: " << it++ << endl;
        cout << "Temperature: " << fixed << setprecision(4) << temperature << endl;
        cout << "Current Heuristic (h): " << h << endl;
        cout << "Current State: " << endl;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                cout << State[i][j] << " ";
            }
            cout << endl;
        }

        // ========================================================================
        // STEP 2b: CHECK GOAL - If goal reached, terminate successfully
        // ========================================================================
        if (h == 0)
        {
            cout << "\n*** GOAL FOUND! ***" << endl;
            cout << "Solution found at iteration " << (it - 1) << endl;
            break;
        }

        // ========================================================================
        // STEP 2c: GENERATE NEIGHBORS
        // ========================================================================
        // Find blank space (0) position
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

        // Generate only valid neighbors (no invalid moves stored)
        vector<vector<vector<int>>> neighbours;

        // Move blank UP (swap with tile above)
        if (blankX - 1 >= 0)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX - 1][blankY]);
            neighbours.push_back(newState);
        }

        // Move blank DOWN (swap with tile below)
        if (blankX + 1 < 3)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX + 1][blankY]);
            neighbours.push_back(newState);
        }

        // Move blank LEFT (swap with tile on left)
        if (blankY - 1 >= 0)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX][blankY - 1]);
            neighbours.push_back(newState);
        }

        // Move blank RIGHT (swap with tile on right)
        if (blankY + 1 < 3)
        {
            vector<vector<int>> newState = State;
            swap(newState[blankX][blankY], newState[blankX][blankY + 1]);
            neighbours.push_back(newState);
        }

        // ========================================================================
        // STEP 2c: SELECT A RANDOM NEIGHBOR
        // ========================================================================
        int randomIdx = rand() % neighbours.size();
        vector<vector<int>> nextState = neighbours[randomIdx];

        // ========================================================================
        // STEP 2d: CALCULATE ENERGY DIFFERENCE (ΔE)
        // ========================================================================
        int nextH = calculateHeuristic(nextState, GoalState);
        int deltaE = nextH - h;

        cout << "Random neighbor selected: h(next) = " << nextH << ", ΔE = " << deltaE << endl;

        // ========================================================================
        // STEP 2e: ACCEPTANCE DECISION
        // ========================================================================
        double prob = acceptanceProbability(h, nextH, temperature);
        double randomProb = (double)rand() / RAND_MAX;

        // Accept or reject based on probability
        if (prob > randomProb)
        {
            State = nextState; // Accept the neighbor
            if (deltaE < 0)
            {
                cout << "✓ ACCEPTED (Better solution)" << endl;
            }
            else if (deltaE == 0)
            {
                cout << "✓ ACCEPTED (Sideways move)" << endl;
            }
            else
            {
                cout << "✓ ACCEPTED (Worse solution, P=" << fixed << setprecision(4) << prob << ")" << endl;
            }
        }
        else
        {
            cout << "✗ REJECTED (P=" << fixed << setprecision(4) << prob << ")" << endl;
        }

        // ========================================================================
        // STEP 2f: COOL DOWN (Update temperature using cooling schedule)
        // ========================================================================
        temperature *= coolingRate; // Geometric cooling schedule

    } // End of main loop

    // ============================================================================
    // STEP 3: TERMINATION - Check final state
    // ============================================================================
    int finalH = calculateHeuristic(State, GoalState);

    cout << "\n============================================================================" << endl;
    cout << "SIMULATED ANNEALING TERMINATED" << endl;
    cout << "============================================================================" << endl;
    cout << "Total Iterations: " << (it - 1) << endl;
    cout << "Final Temperature: " << fixed << setprecision(4) << temperature << endl;
    cout << "Final Heuristic: " << finalH << endl;

    if (finalH == 0)
    {
        cout << "Status: SUCCESS - Goal state reached!" << endl;
    }
    else if (temperature <= minTemperature)
    {
        cout << "Status: FAILED - Temperature dropped below threshold" << endl;
    }
    else if (it > maxIterations)
    {
        cout << "Status: FAILED - Maximum iterations exceeded" << endl;
    }

    cout << "Final State:" << endl;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cout << State[i][j] << " ";
        }
        cout << endl;
    }
    cout << "============================================================================" << endl;
}