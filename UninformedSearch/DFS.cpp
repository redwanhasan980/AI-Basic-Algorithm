#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<int>parent(100100);
vector<bool> visited(100100, false);
bool isFound=false;
void dfs(int v, vector<vector<int>> &adj,char target)
{  if(isFound) return;
    visited[v] = true;
    cout << char(v + 'A') << " ";
    if(v==target-'A')
    {
        isFound=true;
        return;
    }
    for (auto ch : adj[v])
    {
        if (!visited[ch])
        {  parent[ch]=v;
            dfs(ch, adj,target);
        }
    }
    cout << endl;
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int i, j, m;
    cin >> m;
    vector<vector<int>> adj(100100);
    for (i = 0; i < m; i++)
    {
        char u, v;
        cin >> u >> v;
        adj[u - 'A'].push_back(v - 'A');
    }
    char target;
    cin>>target;
    dfs(0, adj,target);
    cout << endl;
    vector<char>path;
    int it=target-'A';
    while (it!=0)
    {
        path.push_back(char(it+'A'));
        it=parent[it];
    }
    path.push_back('A');
    reverse(path.begin(),path.end());
    for(i=0;i<path.size();i++)
    {
        cout<<path[i]<<" ";
    }
}