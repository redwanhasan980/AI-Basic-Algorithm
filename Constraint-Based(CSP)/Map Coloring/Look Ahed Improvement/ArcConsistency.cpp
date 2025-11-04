#include <bits/stdc++.h>
using namespace std;

int arcRevisions = 0;
int domainReductions = 0;

bool revise(int xi, int xj, vector<set<int>> &domains, vector<int> &colors)
{
    bool revised = false;
    set<int> toRemove;

    for (int vi : domains[xi])
    {
        bool hasSupport = false;

        if (colors[xj] != 0)
        {
            if (colors[xj] != vi)
            {
                hasSupport = true;
            }
        }
        else
        {
            for (int vj : domains[xj])
            {
                if (vi != vj)
                {
                    hasSupport = true;
                    break;
                }
            }
        }

        if (!hasSupport)
        {
            toRemove.insert(vi);
            revised = true;
        }
    }

    for (int val : toRemove)
    {
        domains[xi].erase(val);
        domainReductions++;
    }

    return revised;
}

bool AC3(int node, vector<vector<int>> &adj, vector<set<int>> &domains, vector<int> &colors, int n)
{
    queue<pair<int, int>> Q;

    for (int i = 1; i <= n; i++)
    {
        if (colors[i] == 0)
        {
            for (int j : adj[i])
            {
                Q.push(make_pair(i, j));
            }
        }
    }

    while (!Q.empty())
    {
        pair<int, int> arc = Q.front();
        Q.pop();
        int xi = arc.first;
        int xj = arc.second;
        arcRevisions++;

        if (revise(xi, xj, domains, colors))
        {
            if (domains[xi].empty())
            {
                return false;
            }

            for (int xk : adj[xi])
            {
                if (xk != xj && colors[xk] == 0)
                {
                    Q.push(make_pair(xk, xi));
                }
            }
        }
    }

    return true;
}

bool backtrackWithAC3(int node, int n, int numColors, vector<int> &colors,
                      vector<vector<int>> &adj, vector<set<int>> &domains)
{
    if (node > n)
    {
        return true;
    }

    for (int color : domains[node])
    {
        cout << "Trying Node " << node << " with Color " << color << endl;

        vector<set<int>> oldDomains = domains;
        colors[node] = color;

        if (AC3(node, adj, domains, colors, n))
        {
            cout << "  [AC-3 PASSED] Arc consistency maintained" << endl;

            if (backtrackWithAC3(node + 1, n, numColors, colors, adj, domains))
            {
                return true;
            }
        }
        else
        {
            cout << "  [AC-3 FAILED] Inconsistency detected, pruning branch" << endl;
        }

        cout << "  Backtracking from Node " << node << ", Color " << color << endl;
        domains = oldDomains;
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

    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= numColors; c++)
        {
            domains[i].insert(c);
        }
    }

    if (backtrackWithAC3(1, n, numColors, colors, adj, domains))
    {
        cout << "\n========================================" << endl;
        cout << "Solution found! Color assignment:" << endl;
        for (int i = 1; i <= n; i++)
        {
            cout << "Node " << i << " -> Color " << colors[i] << endl;
        }
        cout << "\n=== ARC CONSISTENCY (AC-3) STATISTICS ===" << endl;
        cout << "Total arc revisions: " << arcRevisions << endl;
        cout << "Total domain reductions: " << domainReductions << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "No solution exists with " << numColors << " colors." << endl;
        cout << "\n=== ARC CONSISTENCY (AC-3) STATISTICS ===" << endl;
        cout << "Total arc revisions: " << arcRevisions << endl;
        cout << "Total domain reductions: " << domainReductions << endl;
        cout << "=========================================" << endl;
    }

    return 0;
}