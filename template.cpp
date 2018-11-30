#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <cassert>
#include <cmath>
#include <ctime>
#include <queue>
#include <memory.h>
#include <stack>

#define pb push_back
#define mp make_pair
typedef long long ll;
typedef double ld;

using namespace std;

const int size1 = 4e5 + 50;
const long long mod = 1e9 + 7;
const long long INF = 1e9;
const double eps = 1e-6;

namespace fi
{
	const int bsize = 6000000;
	char buff[bsize];
	int sz;
	void start()
	{
		sz = fread(buff, 1, bsize, stdin);
	}
	int i = 0;
	typedef double ld;
	inline double get_d()
	{
		while (!isdigit(buff[i])) ++i;
		i += 4;
		return buff[i - 4] - '0' + ld(buff[i - 2] - '0') / 10 + ld(buff[i - 1] - '0') / 100;
	}
	inline int get_i()
	{
		while (!isdigit(buff[i])) ++i;
		int ans(0);
		while (isdigit(buff[i])) ans = ans * 10 + buff[i++] - '0';
		return ans;
	}
}

template <typename T1, typename T2>
inline ostream& operator<<(ostream& out, const pair<T1, T2>& v) { return out << v.first << ' ' << v.second; }
template <typename T>
inline ostream& operator<<(ostream& out, const vector<T>& v) { for (const T& x : v) out << x << ' '; return out; }
template <typename T1, typename T2>
inline istream& operator>>(istream& in, pair<T1, T2>& v) { return in >> v.first >> v.second; }
template <typename T>
inline istream& operator>>(istream& in, vector<T>& v) { for (T& x : v) in >> x; return in; };

void solve()
{

}

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}
