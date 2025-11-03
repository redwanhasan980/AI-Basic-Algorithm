#include <bits/stdc++.h>
using namespace std;
vector<int> parent(100100);
bool dls(int v, int depth, int target, vector<vector<int>> &adj, vector<bool> &visited)
{
    if (depth < 0)
        return false;

    visited[v] = true;
    cout << char(v + 'A') << " ";
    if (v == target)
        return true;
    for (auto ch : adj[v])
    {
        if (!visited[ch])
        {
            parent[ch] = v;
            if (dls(ch, depth - 1, target, adj, visited))
                return true;
        }
    }
    cout << endl;
    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<vector<int>> adj(100100);
    vector<bool> visited(100100, false);
    int i, m, depth;
    cin >> m;
    char target;
    for (i = 0; i < m; i++)
    {
        char u, v;
        cin >> u >> v;
        adj[u - 'A'].push_back(v - 'A');
    }
    cin  >> target>>depth;
    if(dls(0, depth, target - 'A', adj, visited))
     {
        cout<<endl<<"Target Founded. Path: "<<endl;
        vector<char>path;
       
        int it=target-'A';
        while(it!=0)
        {
            path.push_back(char(it+'A'));
            it=parent[it]; 
        }
        path.push_back('A');
        reverse(path.begin(),path.end());
        for(auto ch: path)
         cout<<ch<<" ";
     }
     else
cout<<"Target not found in the Depth: "<<depth;

}