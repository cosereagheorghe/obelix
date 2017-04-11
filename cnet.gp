x='x; y='y;
\\ system("wget http://oeis.org/A106651/a106651.txt");
Fy = read("a106651.txt");
A106651_ser(N) = {
  my(y0 = 1 + O(x^N), y1=0, n=1);
  while(n++,
    y1 = y0 - subst(Fy, y, y0)/subst(deriv(Fy, y), y, y0);
    if (y1 == y0, break()); y0 = y1);
  y0;
};
z='z; t='t; u='u; c0='c0;
r1 = 2*t*u + 2*t^2*u + 2*t*u^2 + 2*t^2*u^2;
r2 = 4*t^2 + 4*t^3 + 4*t^2*u + 4*t^3*u;
r3 = -4*t^2 - 4*t^3 - 2*t*u - 6*t^2*u - 4*t^3*u - 2*t*u^2 - 2*t^2*u^2;
r4 = 2*t + 2*t^2 + 4*t^3 - u + t*u + 4*t^3*u + u^2 + t*u^2 - 2*t^2*u^2;
r5 = -2*t - 2*t^2 - 4*t^3 - 4*t*u - 2*t^2*u - 4*t^3*u + 2*t^2*u^2;
r6 = u + 2*t*u + 2*t^2*u - t*u^2;
Fz = r1*z^2 + (r3*c0 + r4)*z + r2*c0^2 + r5*c0 + r6;

seq0(N) = {
  my(t = 't+O('t^N),  u = 'u +O('u^N),
     c0 = subst(A106651_ser(N+1), 'x, 't),
  r1 = 2*t*u + 2*t^2*u + 2*t*u^2 + 2*t^2*u^2,
  r2 = 4*t^2 + 4*t^3 + 4*t^2*u + 4*t^3*u,
  r3 = -4*t^2 - 4*t^3 - 2*t*u - 6*t^2*u - 4*t^3*u - 2*t*u^2 - 2*t^2*u^2,
  r4 = 2*t + 2*t^2 + 4*t^3 - u + t*u + 4*t^3*u + u^2 + t*u^2 - 2*t^2*u^2,
  r5 = -2*t - 2*t^2 - 4*t^3 - 4*t*u - 2*t^2*u - 4*t^3*u + 2*t^2*u^2,
  r6 = u + 2*t*u + 2*t^2*u - t*u^2,
  Fz = r1*z^2 + (r3*c0 + r4)*z + r2*c0^2 + r5*c0 + r6);
  (-(r3*c0 + r4) - sqrt((r3*c0 + r4)^2 - 4*r1*(r2*c0^2 + r5*c0 + r6)))/(2*r1);
};

seq1(N) = {
  my(z0 = 1 + O(t^N) + O(u^N), z1=0, n=1,
     Fz = subst(Fz, 'c0, subst(A106651_ser(N+1), 'x, 't)));
  while(n++,
    z1 = z0 - subst(Fz, z, z0)/subst(deriv(Fz, z) , z, z0);
    if (z1 == z0, break()); z0 = z1);
  print("n = ", n);
  z0;
\\  vector(N, n, vector(n, k, polcoeff(polcoeff(z0, n-k), k-1)));
};
seq2(N) = {
  my(z0 = 1 + O(t^N), z1=0, n=1,
     Fz = subst(Fz, 'c0, subst(A106651_ser(N), 'x, 't)));
  while(n++,
    z1 = z0 - subst(Fz, z, z0)/subst(deriv(Fz, z) , z, z0);
    if (z1 == z0, break()); z0 = z1);
  print("n = ", n);
  z0;
\\  vector(N, n, vector(n, k, polcoeff(polcoeff(z0, n-k), k-1)));
};
