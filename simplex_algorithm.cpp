#include <algorithm>
#include <valarray>
#include <vector>
#include <iostream>
#include <cassert>
#include <iomanip>

using namespace std;

typedef double ld;

//#define _DBG_

#ifdef _DBG_
template <typename T> inline void dbg(const T& x) { cerr << x; }
template <typename T, typename ...Args> inline void dbg(const T& x, const Args& ...y) { cerr << x; dbg(y...); }
#else
#define dbg(...)
#endif

#define all(U) begin(U), end(U)

struct simplex
{
    bool unbounded;
    int c;
    vector<int> B, N;
    vector<valarray<ld>> eq;
    valarray<ld> f;

    void init(int non_basic, int basic)
    {
        unbounded = false;

        c = non_basic + basic;

        B.clear();
        for (int i(non_basic); i < non_basic + basic; ++i)
            B.push_back(i);

        N.clear();
        for (int i(0); i < non_basic; ++i)
            N.push_back(i);

        f.resize(non_basic + basic + 1);
        f = 0;

        eq.resize(non_basic + basic);
        for (int i(0); i < non_basic; ++i)
            eq[i].resize(0);
        for (int i(non_basic); i < non_basic + basic; ++i)
        {
            eq[i].resize(non_basic + basic + 1);
            eq[i] = 0;
            eq[i][i] = -1;
        }
    }

    friend inline ostream&
    operator<<(ostream& out, const simplex& s)
    {
        out << "Non-basic:"; for (int x : s.N) out << ' ' << x; out << endl;
        for (int x : s.B)
        {
            out << x << ":";
            for (ld a : s.eq[x]) out << ' ' << a;
            out << endl;
        }
        out << "f:";
        for (ld a : s.f) out << ' ' << a;
        out << endl;
        return out;
    }

    void swap_x(int b, int nb)
    {
        dbg("Started swap basic ", b, " with non-basic ", nb, '\n');
        ld alpha = eq[b][nb];
        eq[b] /= -alpha;
        swap(eq[b], eq[nb]);
        swap(*find(all(B), b), *find(all(N), nb));
        for (int x : B)
            if (x != nb)
            {
                alpha = eq[x][nb];
                eq[x] += alpha * eq[nb];
            }
        alpha = f[nb];
        f += alpha * eq[nb];
        dbg("Finished swap\n");
    }

    bool iter()
    {
        dbg(*this);
        int nb(-1);
        {
            for (int x : N)
                if (f[x] > 0 && (nb == -1 || x < nb))
                    nb = x;
            if (nb == -1)
                return false;
        }
        sort(all(B));
        int b(-1);
        {
            unbounded = true;
            for (int x : B)
                if (eq[x][nb] <= 0)
                {
                    unbounded = false;
                    if (eq[x][nb] != 0)
                        if (b == -1 || eq[x][c] / eq[x][nb] > eq[b][c] / eq[b][nb])
                            b = x;
                }
            if (unbounded)
                return false;
        }
        swap_x(b, nb);
        dbg(*this);
        return true;
    }

    void run() {
        while (iter());
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    simplex s;
    s.init(n, m);
    for (int i(n); i < n + m; ++i)
    {
        for (int j(0); j < n; ++j)
        {
            cin >> s.eq[i][j];
            s.eq[i][j] *= -1;
        }
        cin >> s.eq[i][s.c];
    }
    for (int i(0); i < n; ++i)
        cin >> s.f[i];
    s.run();
    fixed(cout);
    cout << setprecision(10);
    if (s.unbounded) cout << "Unbounded" << endl;
    else
    {
        cout << "Bounded" << endl;
        vector<ld> ans(n, 0);
        for (int x : s.B)
            if (x < n)
                ans[x] = s.eq[x][s.c];
        for (ld x : ans) cout << x << ' ';
        cout << endl;
    }
    /*s.init(2, 3);
    s.eq[2] = { -1, 1, -1, 0, 0, 2};
    s.eq[3] = { -2, 1, 0, -1, 0, 6};
    s.eq[4] = { -3, -2, 0, 0, -1, 23};
    s.f = { 2, 1, 0, 0, 0, 0 };
//    dbg(s);
//    s.swap_x(2, 0);
//    dbg(s);
    s.run();*/
}
