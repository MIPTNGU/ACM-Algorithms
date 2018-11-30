template <size_t m>
void gauss(vector<bitset<m>>& a) {
    int n(a.size());
    for (int i(0), j(0); i < m; ++i)
    {
        int best(j);
        while (best < n and !a[best][i])
            ++best;
        if (best == n)
            continue;
        swap(a[j], a[best]);
        for (int k(0); k < n; ++k)
            if (k != j and a[k][i])
                a[k] ^= a[j];
        ++j;
    }
}
