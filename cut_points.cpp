void dfs(int pr, int v)
{
	t++;
	used[v] = true;
	up[v] = tin[v] = t;
	int cnt = 0;
	for (int u : graph[v])
	{
		if (u == pr)
		{
			continue;
		}
		if (used[u])
		{
			up[v] = min(up[v], tin[u]);
		}
		else
		{
			dfs(u, v);
			cnt++;
			up[v] = min(up[v], up[u]);
			if (pr != -1 && up[u] >= tin[v])
			{
				cut_p[v] = true;
			}
		}
	}
	if (pr == -1 && cnt >= 2)
	{
		cut_p[v] = true;
	}
}

int maxcol = 0;

void paint(int v, int col, int pr)
{
	used[v] = true;
	for (int u : graph[v])
	{
		if (u == pr)
		{
			continue;
		}
		if (!used[u])
		{
			if (up[u] >= tin[v])
			{
				maxcol++;
				col[vu] = maxcol;
				paint(u, maxcol, v);
			}
			else
			{
				col[vu] = col;
				paint(u, col, v);
			}
		}
		else
		{
			if (tin[u] < tin[v])
			{
				col[vu] = col;
			}
		}
	}
}
