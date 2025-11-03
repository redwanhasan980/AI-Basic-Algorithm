#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    vector<int> heuristic(n, 0);
    vector<vector<pair<int, int>>> adj(n);

    char u, v;
    int w;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        int ui = u - 'A';
        int vi = v - 'A';
        adj[ui].push_back({vi, w});
        adj[vi].push_back({ui, w});
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> u >> w;
        heuristic[u - 'A'] = w;
    }

    char start_c, goal_c;
    cin >> start_c >> goal_c;
    int start = start_c - 'A';
    int goal = goal_c - 'A';

    const int INF = 1e9;
    vector<int> parent(n, -1);
    vector<int> g_cost(n, INF); // g(n): actual cost from start to node
    vector<bool> visited(n, false);

    // Priority queue stores: {f(n) = g(n) + h(n), node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    g_cost[start] = 0;
    pq.push({g_cost[start] + heuristic[start], start});

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        int node = cur.second;

        if (visited[node])
            continue;
        visited[node] = true;

        if (node == goal)
            break;

        for (auto it : adj[node])
        {
            int ch = it.first;
            int wt = it.second;

            if (visited[ch])
                continue;

            // A*: Update if we found a better path (lower g-cost)
            int new_g_cost = g_cost[node] + wt;
            if (new_g_cost < g_cost[ch])
            {
                g_cost[ch] = new_g_cost;
                parent[ch] = node;
                // f(n) = g(n) + h(n)
                int f_cost = g_cost[ch] + heuristic[ch];
                pq.push({f_cost, ch});
            }
        }
    }

    if (!visited[goal])
    {
        cout << "No path found from " << start_c << " to " << goal_c << '\n';
        return 0;
    }

    vector<int> path;
    for (int cur = goal; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (auto it : path)
    {
        cout << char('A' + it) << " ";
    }
    cout << endl;
    cout << "Distance: " << g_cost[goal] << endl;
}