namespace MINCUT {

int mat[MX][MX];

int mincut(int n)
{
	static int w[MX];
	static bool used[MX];
	int minr = 100000000;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			w[j] = 0;
		}
		int cnt = 0;
		static bool met[MX];
		for (int u = 1; u <= n; u++)
		{
			if (!used[u])
			{
				cnt++;
			}
			met[u] = false;
		}
		vector < int > num;
		for (int j = 1; j <= cnt; j++)
		{
            pair < int, int > min_el = {0, 0};
            for (int k = 1; k <= n; k++)
            {
                if (!met[k] && !used[k] && w[k] >= min_el.first)
                {
                    min_el = {w[k], k};
                }
            }
			num.push_back(min_el.second);
			met[min_el.second] = true;
			if (j == cnt)
			{
				minr = min(minr, w[min_el.second]);
			}
			for (int k = 1; k <= n; k++)
			{
				if (!used[k] && mat[min_el.second][k] && !met[k])
				{
					w[k] += mat[min_el.second][k];
				}
			}
		}
		int s = num[num.size() - 2], t = num.back();
		mat[s][t] = mat[t][s] = 0;
		used[t] = true;
		for (int j = 1; j <= n; j++)
		{
			if (mat[t][j])
			{
				mat[s][j] += mat[t][j];
			}
			if (mat[j][t])
			{
				mat[j][s] += mat[j][t];
			}
		}
	}
	return minr;
}
}
