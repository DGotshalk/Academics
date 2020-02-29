// Drew Gotshalk
// This is coding the Newtowns Method
// switch instances of f
// n = 22 x: 2.17456 hx: -4.44089e-16 for f(x)
// x = 1 n = 6 x: 0.79128 gx: -4.44089e-16
// x = 2 n = 6 x: 1.61803 gx: -5.32907e-15
// x = 2 n = 5 x: 2.09455 hx: -8.88178e-16
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;
double f(double x)
{
	return pow(x, 3) - 2 * pow(x, 2) + x - 3;
}
double fpp(double x)
{
	return 3 * pow(x, 2) - 4 * x + x;
}
double g(double x)
{
	return pow(x, 4) + 2 * pow(x, 3) - 7 * pow(x, 2) + 3;
}
double gpp(double x)
{
	return 4 * pow(x, 3) + 6 * pow(x, 2) - 14 * x;
}
double h(double x) 
{
	return pow(x, 3) - 2 * x - 5;
}
double hpp(double x)
{
	return 3 * pow(x, 2) - 2;
}
int main()
{
	int n, nmax = 30;
	double x, hx, hp, d, epsilon = numeric_limits<double>::epsilon();
	x = 2;
	hx = h(x);
	cout << 0 << " x: " << x << " hx: " << hx << endl;
	for (n = 0; n < nmax; n++)
	{
		hp = hpp(x);
		if (fabs(hp) < epsilon)
		{
			cout << "small derivative" << endl;
			system("pause");
			return 0;
		}
		d = hx / hp;
		x = x - d;
		hx = h(x);
		cout << n+1 << " x: " << x << " hx: " << hx << endl;
		if (fabs(d) < epsilon) 
		{
			cout << "we have converged";
			system("pause");
			return 0;
		}
	}
	system("pause");
	return 0;
}