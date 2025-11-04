#include <bits/stdc++.h>
using namespace std;

// Function to check if it's safe to assign a color to a node
bool isSafe(int node, int color, vector<int> &colors, vector<vector<int>> &adj)
{
    // Check all neighbors of the current node
    for (int neighbor : adj[node])
    {
        // If any neighbor has the same color, it's not safe
        if (colors[neighbor] == color)
        {
            return false;
        }
    }
    return true; // Safe to assign this color
}

// Backtracking function to color the map
bool backtrack(int node, int n, int numColors, vector<int> &colors, vector<vector<int>> &adj)
{
    // Base case: If all nodes are colored, we found a solution
    if (node > n)
    {
        return true;
    }

    // Try assigning each color (1 to numColors) to the current node
    for (int color = 1; color <= numColors; color++)
    {
        // Check if it's safe to assign this color
        if (isSafe(node, color, colors, adj))
        {
            // Assign the color to the current node
            colors[node] = color;

            // Recursively try to color the next node
            if (backtrack(node + 1, n, numColors, colors, adj))
            {
                return true; // Solution found
            }

            // Backtrack: Remove the color if it didn't lead to a solution
            colors[node] = 0;
        }
    }

    // No color worked for this node, backtrack
    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    vector<vector<int>> adj(100100);
    int n, m, numColors;

    // Read number of nodes, edges, and colors
    cin >> n >> m >> numColors;

    // Read the edges and build the adjacency list
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Array to store the color assigned to each node (0 means no color)
    vector<int> colors(n + 5, 0);

    // Try to color the map using backtracking
    if (backtrack(1, n, numColors, colors, adj))
    {
        cout << "Solution found! Color assignment:" << endl;
        for (int i = 1; i <= n; i++)
        {
            cout << "Node " << i << " -> Color " << colors[i] << endl;
        }
    }
    else
    {
        cout << "No solution exists with " << numColors << " colors." << endl;
    }

    return 0;
}