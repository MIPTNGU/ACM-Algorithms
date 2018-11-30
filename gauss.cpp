template <size_t m>
void gauss(vector<bitset<m>>& a) {
    int n(a.size());
    for (int i(0), j(0); i < m; ++i)
    {
        int best(j);
        while (best < n and not a[best][i])
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

void gauss(vector<valarray<long double>>& a) {
    int n(a.size()), m(a[0].size());
    for (int i(0), j(0); i < m; ++i) {
        int best(j);
        for (int k(j + 1); k < n; ++k)
            if (fabsl(a[best][i]) < fabsl(a[k][i]))
                best = k;
        if (a[best][i] == 0)
            continue;
        swap(a[best], a[j]);
        a[j] /= a[j][i];
        for (int k(0); k < n; ++k)
            if (k != j)
                a[k] -= a[k][i] * a[j];
        ++j;
    }
}
