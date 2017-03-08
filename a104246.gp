seq(N) = {
  my(a = vector(N, k, 8), T = k->(k*(k+1)*(k+2))\6);
  for (n = 1, N,
    my (k1 = sqrtnint((6*n)\8, 3), k2 = sqrtnint(6*n, 3));
    while(n < T(k2), k2--); if (n == T(k2), a[n] = 1; next());
    for (k = k1, k2, a[n] = min(a[n], a[n - T(k)] + 1))); a;
};
seq(102)
