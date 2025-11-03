// Greedy Best-First Search Implementation in C++
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

    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
    vector<int> cost(n, 0); // Track actual cost for reporting

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({heuristic[start], start});

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

            // Greedy BFS: only set parent on first encounter
            if (parent[ch] == -1 && ch != start)
            {
                parent[ch] = node;
                cost[ch] = cost[node] + wt;
            }

            pq.push({heuristic[ch], ch});
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
    cout << "Distance: " << cost[goal] << endl;
}