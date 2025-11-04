#include <bits/stdc++.h>
using namespace std;

int domainReductions = 0;
int earlyPruning = 0;
int backtrackCount = 0;

// Forward checking: Remove assigned color from uncolored neighbors' domains
// Returns false if any neighbor's domain becomes empty (dead-end detected)
bool forwardCheck(int node, int color, vector<int> &colors, vector<vector<int>> &adj,
                  vector<set<int>> &domains)
{
    // Track which colors we removed from which nodes for potential restoration
    vector<pair<int, int>> removed;

    // Check all neighbors of the current node
    for (int neighbor : adj[node])
    {
        // Only process uncolored neighbors
        if (colors[neighbor] == 0)
        {
            // If neighbor has this color in its domain, remove it
            if (domains[neighbor].count(color))
            {
                domains[neighbor].erase(color);
                removed.push_back({neighbor, color});
                domainReductions++;

                // If neighbor's domain becomes empty, we have a dead-end
                if (domains[neighbor].empty())
                {
                    earlyPruning++;
                    cout << "  [FORWARD CHECK] Dead-end detected! Node " << neighbor
                         << " has no valid colors left after assigning Node " << node
                         << " = Color " << color << endl;
                    // Restore all removed colors before returning
                    for (auto p : removed)
                    {
                        domains[p.first].insert(p.second);
                    }
                    return false; // Pruning: this path won't lead to a solution
                }
            }
        }
    }
    return true; // All neighbors still have valid colors available
}

void restoreDomains(int node, int color, vector<vector<int>> &adj,
                    vector<set<int>> &domains, vector<int> &colors)
{
    for (int neighbor : adj[node])
    {
        if (colors[neighbor] == 0) // only restore for uncolored neighbors
        {
            domains[neighbor].insert(color);
        }
    }
}

bool backtrackWithFC(int node, int n, int numColors, vector<int> &colors,
                     vector<vector<int>> &adj, vector<set<int>> &domains)
{
    if (node > n)
    {
        return true;
    }

    for (int color : domains[node])
    {
        cout << "Trying Node " << node << " with Color " << color << endl;
        colors[node] = color;

        if (forwardCheck(node, color, colors, adj, domains))
        {
            cout << "  [FORWARD CHECK PASSED] All neighbors have valid domains" << endl;
            if (backtrackWithFC(node + 1, n, numColors, colors, adj, domains))
            {
                return true;
            }
        }
        else
        {
            cout << "  [FORWARD CHECK FAILED] Pruning this branch early!" << endl;
        }
        // the restoreDomains function is called to undo the forward checking

        backtrackCount++;
        cout << "  Backtracking from Node " << node << ", Color " << color << endl;
        restoreDomains(node, color, adj, domains, colors);
        colors[node] = 0;
    }

    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    vector<vector<int>> adj(100100);
    int n, m, numColors;

    cin >> n >> m >> numColors;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> colors(n + 5, 0);
    vector<set<int>> domains(n + 5);
    // Initialize domains with all colors for each node
    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= numColors; c++)
        {
            domains[i].insert(c);
        }
    }

    if (backtrackWithFC(1, n, numColors, colors, adj, domains))
    {
        cout << "\n========================================" << endl;
        cout << "Solution found! Color assignment:" << endl;
        for (int i = 1; i <= n; i++)
        {
            cout << "Node " << i << " -> Color " << colors[i] << endl;
        }
        cout << "\n=== FORWARD CHECKING STATISTICS ===" << endl;
        cout << "Total domain reductions: " << domainReductions << endl;
        cout << "Early pruning (dead-ends detected): " << earlyPruning << endl;
        cout << "Total backtracks: " << backtrackCount << endl;
        cout << "=====================================" << endl;
    }
    else
    {
        cout << "No solution exists with " << numColors << " colors." << endl;
        cout << "\n=== FORWARD CHECKING STATISTICS ===" << endl;
        cout << "Total domain reductions: " << domainReductions << endl;
        cout << "Early pruning (dead-ends detected): " << earlyPruning << endl;
        cout << "Total backtracks: " << backtrackCount << endl;
        cout << "=====================================" << endl;
    }

    return 0;
}