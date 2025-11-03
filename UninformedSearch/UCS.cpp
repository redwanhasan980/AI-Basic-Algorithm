#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("inputUCS.txt", "r", stdin);
    freopen("outputUCS.txt", "w", stdout);
    vector<vector<pair<int, int>>> adj(100100);
    int m, i;
    cin >> m;
    for (i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    int target;
    cin >> target;

    // Priority queue: {cost, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(100100, INT_MAX);
    vector<int> parent(100100, -1);
    vector<bool> visited(100100, false);

    pq.push({0, 1}); // Start from node 1 with cost 0
    dist[1] = 0;

    bool found = false;

    while (!pq.empty())
    {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (visited[node])
            continue;

        visited[node] = true;

        if (node == target)
        {
            found = true;
            break;
        }

        for (auto it : adj[node])
        {
            int wt = it.second;
            int ch = it.first;
            if (dist[node] + wt < dist[ch])
            {
                dist[ch] = dist[node] + wt;
                parent[ch] = node;
                pq.push({dist[ch], ch});
            }
        }
    }

    if (found)
    {
        cout << "Target Found. Total Cost: " << dist[target] << endl;
        cout << "Path: " << endl;

        vector<int> path;
        int it = target;

        while (it != -1)
        {
            path.push_back(it);
            it = parent[it];
        }

        reverse(path.begin(), path.end());

        for (auto node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Target not found!" << endl;
    }
}