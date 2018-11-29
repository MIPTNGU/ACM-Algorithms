#include <bits/stdc++.h>
using namespace std;

const int size1 = 4e5;
vector < vector < int > > graph(size1), graph1(size1);
static bool used[size1];
static int col[size1];
vector < int > top;
int n;

void dfs(int v)
{
    used[v] = true;
    for (int u : graph[v])
    {
        if (!used[u])
        {
            dfs(u);
        }
    }
    top.push_back(v);
}

void dfs1(int v, int cur)
{
    col[v] = cur;
    for (int u : graph1[v])
    {
        if (!col[u])
        {
            dfs1(u, cur);
        }
    }
}

int kss()
{
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            dfs(i);
        }
    }
    int cur = 0;
    for (int i = top.size() - 1; i >= 0; i--)
    {
        if (!col[top[i]])
        {
            cur++;
            dfs1(top[i], cur);
        }
    }
    return cur;
}

int main()
{
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int v, u;
        cin >> v >> u;
        graph[v].push_back(u);
        graph1[u].push_back(v);
    }
    int cnt = kss();
    vector < vector < int > > ans(cnt + 1);
    for (int i = 1; i <= n; i++)
    {
        ans[col[i]].push_back(i);
    }
    cout << cnt << "\n";
    for (int i = 1; i <= cnt; i++)
    {
        cout << ans[i].size() << ' ';
        for (int el : ans[i])
        {
            cout << el << ' ';
        }
        cout << endl;
    }
}
