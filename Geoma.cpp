#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <memory.h>
#include <algorithm>
#include <stack>
#include <cassert>
using namespace std;

typedef long double TCoord;
typedef long double ld;
const ld eps = 1e-9;
const TCoord pi = acos(-1);

struct Point
{
	TCoord x, y;
};


bool isZero(ld x)
{
	return fabsl(x) < eps;
}

bool isNonNegative(ld x)
{
	return isZero(x) || (x > 0);
}

bool isNonPositive(ld x)
{
	return isZero(x) || (x < 0);
}

bool areEqual(ld x, ld y)
{
	return isZero(x - y);
}

bool isLessThan(ld x, ld y)
{
	return x - y < -eps;
}

bool isMoreThan(ld x, ld y)
{
	return x - y > eps;
}

bool isNotMoreThan(ld x, ld y)
{
	return isLessThan(x, y) || areEqual(x, y);
}

bool isNotLessThan(ld x, ld y)
{
	return isMoreThan(x, y) || areEqual(x, y);
}

Point operator+(Point p1, Point p2)
{
	return Point{ p1.x + p2.x, p1.y + p2.y };
}

Point operator-(Point p1, Point p2)
{
	return Point{ p1.x - p2.x, p1.y - p2.y };
}

Point operator*(Point p, TCoord d)
{
	return Point{ p.x * d, p.y * d };
}

Point operator*(TCoord d, Point P)
{
	return P * d;
}

TCoord operator*(Point p1, Point p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

TCoord operator^(Point p1, Point p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

bool operator<(Point p1, Point p2)
{
	return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

bool areEqual(Point p1, Point p2)
{
	return areEqual(p1.x, p2.x) && areEqual(p1.y, p2.y);
}

bool areCollinear(Point p1, Point p2)
{
	return isZero(p1 ^ p2);
}

bool areCodirected(Point p1, Point p2)
{
	return areCollinear(p1, p2) && isNonNegative(p1 * p2);
}

bool isOnLine(Point p, Point A, Point B)
{
	return isZero((p - A) ^ (B - A));
}

bool isOnSegment(Point p, Point A, Point B)
{
	return areCodirected(A - p, p - B);
}

Point findLinesIntersection(Point A, Point B, Point C, Point D)
{
	TCoord t = ((C - A) ^ (D - C)) / ((B - A) ^ (D - C));
	// [a + t(B - A) - C, D - C] = 0;
	return A + t * (B - A);
}

TCoord radiansToDegree(TCoord A)
{
	return A * 180 / pi;
}

TCoord degreeToRadians(TCoord A)
{
	return A * pi / 180;
}

TCoord norm(Point A)
{
	return sqrt(A * A);
}

TCoord len(Point A, Point B)
{
	return norm(A - B);
}

void normalize(Point& A)
{
	TCoord len = norm(A);
	A.x /= len;
	A.y /= len;
}

TCoord findAngle1(Point A)
{
	return atan2(A.y, A.x);
}

TCoord findAngle2(Point A, Point B)
{
	TCoord res = abs(findAngle1(B) - findAngle1(A));
	if (res > pi)
	{
		res = 2 * pi - res;
	}
	return res;
}

TCoord findSquare(Point A, Point B)
{
	return abs(A ^ B);
}

TCoord findSquare1(Point A, Point B, Point C)
{
	return findSquare(A - C, B - C);
}

bool sign(ld a)
{
	return a >= 0;
}

bool isIntersectSegments(Point A, Point B, Point C, Point D)
{
	if (isOnSegment(C, A, B) || isOnSegment(D, A, B) ||
		isOnSegment(A, C, D) || isOnSegment(B, C, D))
	{
		return true;
	}
	if (isOnLine(A, B, C) && isOnLine(A, B, D))
	{
		return false;
	}
	if (sign((B - A) ^ (C - A)) != sign((B - A) ^ (D - A)) && sign((D - C) ^ (A - C)) != sign((D - C) ^ (B - C)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

const int size1 = 4e5;
const long long INF = 8e18;

typedef long long ll;
vector < pair < ll, ll > > v;

ll ras(pair < ll, ll > p1, pair < ll, ll > p2)
{
	ll pok1 = p1.first - p2.first;
	ll pok2 = p1.second - p2.second;
	return pok1 * pok1 + pok2 * pok2;
}

bool cmp(pair < ll, ll > p1, pair < ll, ll > p2)
{
	return p1.second < p2.second;
}

ll rec(int l, int r)
{
	if (r == l)
	{
		return INF;
	}
	else
	{
		int m = (l + r) / 2;
		ll line = v[m].first;
		ll minr = min(rec(l, m), rec(m + 1, r));
		vector < pair < ll, ll > > v1, v2;
		for (int i = l; i <= m; i++)
		{
			if ((v[i].first - line) * (v[i].first - line) <= minr)
			{
				v1.push_back(v[i]);
			}
		}
		for (int i = m + 1; i <= r; i++)
		{
			if ((v[i].first - line) * (v[i].first - line) <= minr)
			{
				v2.push_back(v[i]);
			}
		}
		int uk = 0;
		for (int i = 0; i < v1.size(); i++)
		{
			while (uk < (int)v2.size() && v1[i].second - v2[uk].second >= 0 && (v1[i].second - v2[uk].second) * (v1[i].second - v2[uk].second) > minr)
			{
				uk++;
			}
			if (uk >= (int)v2.size())
			{
				break;
			}
			for (int j = uk; j < min(uk + 10, (int)v2.size()); j++)
			{
				minr = min(minr, ras(v1[i], v2[j]));
			}
		}
		vector < pair < ll, ll > > pok(r - l + 1);
		merge(v.begin() + l, v.begin() + m + 1, v.begin() + m + 1, v.begin() + r + 1, pok.begin(), cmp);
		copy(pok.begin(), pok.end(), v.begin() + l);
		return minr;
	}
}

vector < Point > SegmentIntersect(Point A, Point B, Point C, Point D)
{
	if (!isIntersectSegments(A, B, C, D))
	{
		return {};
	}
	if (isOnLine(A, B, C) && isOnLine(A, B, D))
	{
		if (isOnSegment(C, A, B) && isOnSegment(D, A, B))
		{
			return { C, D };
		}
		if (isOnSegment(B, A, C) && isOnSegment(D, A, C))
		{
			return { B, D };
		}
		if (isOnSegment(B, A, D) && isOnSegment(C, A, D))
		{
			return { B, C };
		}
		if (isOnSegment(A, B, C) && isOnSegment(D, B, C))
		{
			return { A, D };
		}
		if (isOnSegment(A, B, D) && isOnSegment(C, B, D))
		{
			return { A, C };
		}
		if (isOnSegment(A, C, D) && isOnSegment(B, C, D))
		{
			return { A, B };
		}
	}
	return { findLinesIntersection(A, B, C, D) };
}

Point X;

bool sort_by_or_angle(Point B, Point C)
{
	if (((B - X) ^ (C - X)) != 0)
	{
		return ((B - X) ^ (C - X)) > 0;
	}
	else
	{
		return len(B, X) < len(C, X);
	}
}

vector < Point > findConvexHull(vector < Point > p1)
{
	if (p1.empty())
	{
		return {};
	}
	sort(p1.begin(), p1.end());
	vector < Point > p = { p1[0] };
	for (int i = 1; i < p1.size(); i++)
	{
		if (!areEqual(p1[i], p1[i - 1]))
		{
			p.push_back(p1[i]);
		}
	}
	int n = (int)p.size();
	TCoord miny = INF, minx = -INF;
	int num = -1;
	for (int i = 0; i < n; i++)
	{
		if (p[i].y < miny || (p[i].y == miny && p[i].x >= minx))
		{
			num = i;
			miny = p[i].y;
			minx = p[i].x;
		}
	}
	swap(p[0], p[num]);
	X = p[0];
	sort(p.begin() + 1, p.end(), sort_by_or_angle);
	stack < int > st;
	st.push(0);
	st.push(1);
	for (int i = 2; i < p.size(); i++)
	{
		bool expr = true;
		while (st.size() >= 2)
		{
			int idx = st.top();
			st.pop();
			int idx1 = st.top();
			st.pop();
			if (((p[i] - p[idx]) ^ (p[idx1] - p[idx])) >= 0)
			{
				st.push(idx1);
				st.push(idx);
				break;
			}
			else
			{
				st.push(idx1);
			}
		}
		st.push(i);
	}
	vector < Point > ans;
	while (!st.empty())
	{
		ans.push_back(p[st.top()]);
		st.pop();
	}
	return ans;
}

vector < pair < ld, ld >  > CircleSegmentIntersection(Point A, Point B, Point O, ld r)
{
	if (areEqual(A, B))
	{
		if (areEqual((A - O) * (A - O), r * r))
		{
			return { {A.x, A.y} };
		}
		else
		{
			return {};
		}
	}
	if (r < eps)
	{
		if (isOnSegment(O, A, B))
		{
			return { {O.x, O.y} };
		}
		else
		{
			return {};
		}
	}
	Point A1 = A - O;
	Point B1 = B - O;
	ld x1 = A1.x;
	ld y1 = A1.y;
	ld x2 = B1.x;
	ld y2 = B1.y;
	ld t2 = x1 * x1 + y1 * y1 + x2 * x2 + y2 * y2 - 2 * x1 * x2 - 2 * y1 * y2;
	ld t1 = -2 * x1 * x1 - 2 * y1 * y1 + 2 * x1 * x2 + 2 * y1 * y2;
	ld t0 = x1 * x1 + y1 * y1 - r * r;
	if (t2 < 0)
	{
		t0 = -t0;
		t1 = -t1;
		t2 = -t2;
	}
	ld d = t1 * t1 - 4 * t2 * t0;
	if (isLessThan(d, 0))
	{
		return {};
	}
	if (areEqual(d, 0))
	{
		if (isNotMoreThan(0, -t1) && isNotMoreThan(-t1, 2 * t2))
		{
			ld t = ((ld)-t1) / (2 * t2);
			return { {O.x + (1 - t) * x1 + t * x2, O.y + (1 - t) * y1 + t * y2} };
		}
		else
		{
			return {};
		}
	}
	if (isMoreThan(d, 0))
	{
		vector < pair < ld, ld > > ans;
		if (isNotMoreThan(t1, sqrtl(ld(d)))
			&& isNotMoreThan(sqrtl(ld(d)), (2 * t2 + t1)))
		{
			ld t = (-t1 + sqrtl(ld(d))) / (2 * t2);
			ans.push_back({ O.x + (1 - t) * x1 + t * x2, O.y + (1 - t) * y1 + t * y2 });
		}
		if (isNotMoreThan(t1, -sqrtl(ld(d))) && isNotMoreThan(-sqrtl(ld(d)), (2 * t2 + t1)))
		{
			ld t = (-t1 - sqrtl(ld(d))) / (2 * t2);
			ans.push_back({ O.x + (1 - t) * x1 + t * x2, O.y + (1 - t) * y1 + t * y2 });
		}
		if (A1.x == B1.x)
		{
			if (A1.y < B1.y && ans.size() == 2)
			{
				swap(ans[0], ans[1]);
			}
		}
		else
		{
			if (A1.x < B1.x && ans.size() == 2)
			{
				swap(ans[0], ans[1]);
			}
		}
		return ans;
	}
}

void pok(Point A, Point B, Point C, Point D, vector < Point > & v)
{
	vector < Point > v1 = SegmentIntersect(A, B, C, D);
	for (auto el : v1)
	{
		v.push_back(el);
	}
}

TCoord STriangle(Point A, Point B, Point C)
{
	return abs((B - A) ^ (C - A)) / 2;
}

bool inTriangle(Point p, Point A, Point B, Point C)
{
	return areEqual(STriangle(p, A, B) + STriangle(p, A, C) + STriangle(p, C, B), STriangle(A, B, C));
}

TCoord SPolygon(vector < Point > v)
{
	TCoord s = 0;
	for (int i = 2; i < v.size(); i++)
	{
		s += STriangle(v[0], v[i - 1], v[i]);
	}
	return s;
}

TCoord findTrianglesUnion(Point A, Point B, Point C, Point A1, Point B1, Point C1)
{
	TCoord ans = STriangle(A, B, C) + STriangle(A1, B1, C1);
	vector < Point > v;
	pok(A, B, A1, B1, v);
	pok(A, B, A1, C1, v);
	pok(A, B, B1, C1, v);
	pok(A, C, A1, B1, v);
	pok(A, C, A1, C1, v);
	pok(A, C, B1, C1, v);
	pok(B, C, A1, B1, v);
	pok(B, C, A1, C1, v);
	pok(B, C, B1, C1, v);
	if (inTriangle(A, A1, B1, C1))
	{
		v.push_back(A);
	}
	if (inTriangle(B, A1, B1, C1))
	{
		v.push_back(B);
	}
	if (inTriangle(C, A1, B1, C1))
	{
		v.push_back(C);
	}
	if (inTriangle(A1, A, B, C))
	{
		v.push_back(A1);
	}
	if (inTriangle(B1, A, B, C))
	{
		v.push_back(B1);
	}
	if (inTriangle(C1, A, B, C))
	{
		v.push_back(C1);
	}
	vector < Point > v1 = findConvexHull(v);
	ans -= SPolygon(v1);
	return ans;
}






