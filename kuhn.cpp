int main() {
	... чтение графа ...
 
	mt.assign (k, -1);
	vector<char> used1 (n);
	for (int i=0; i<n; ++i)
		for (size_t j=0; j<g[i].size(); ++j)
			if (mt[g[i][j]] == -1) {
				mt[g[i][j]] = i;
				used1[i] = true;
				break;
			}
	for (int i=0; i<n; ++i) {
		if (used1[i])  continue;
		used.assign (n, false);
		try_kuhn (i);
	}
 
	for (int i=0; i<k; ++i)
		if (mt[i] != -1)
			printf ("%d %d\n", mt[i]+1, i+1);
}
