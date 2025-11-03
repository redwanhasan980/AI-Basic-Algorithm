#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<vector<int>> adj(100100);
    vector<int> parent(100100);
    int i, m;
    cin >> m;
    for (i = 0; i < m; i++)
    {
        char u, v;
        cin >> u >> v;
        adj[u - 'A'].push_back(v - 'A');
    }
    char target;
    cin >> target;
    queue<int> qu;
    vector<bool> visited(100100, false);
    qu.push(0);
    visited[0] = true;
    bool isFound = false;
    while (!qu.empty())
    {
        if (isFound)
            break;
        int l = qu.size();
        for (i = 0; i < l; i++)
        {

            int node = qu.front();
            qu.pop();
            cout << char(node + 'A') << " ";

            if (node == target - 'A')
            {
                isFound = true;
                break;
            }

            for (auto ch : adj[node])
            {
                if (visited[ch])
                    continue;
                visited[ch] = true;
                parent[ch] = node;
                qu.push(ch);
            }
        }
        cout << endl;
    }
    vector<char> path;
    int it = target - 'A';

    while (it != 0)
    {
        path.push_back(char(it + 'A'));
        it = parent[it];
    }
    path.push_back('A');
    reverse(path.begin(), path.end());
    cout << endl;
    for (auto ch : path)
    {
        cout << ch << " ";
    }
}