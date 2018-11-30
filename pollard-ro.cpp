template <class T>
T pollard_rho (T n, unsigned iterations_count = 100000)
{
	T
		b0 = rand() % n,
		b1 = b0,
		g;
	mulmod (b1, b1, n);
	if (++b1 == n)
		b1 = 0;
	g = gcd (abs (b1 - b0), n);
	for (unsigned count=0; count<iterations_count && (g == 1 || g == n); count++)
	{
		mulmod (b0, b0, n);
		if (++b0 == n)
			b0 = 0;
		mulmod (b1, b1, n);
		++b1;
		mulmod (b1, b1, n);
		if (++b1 == n)
			b1 = 0;
		g = gcd (abs (b1 - b0), n);
	}
	return g;
}
