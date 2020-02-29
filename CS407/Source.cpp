#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <algorithm>
using namespace std;

double sgn(double x)
{
	return (0 < x) - (x < 0);
}

double f(double t, double x)
{
	return 3 + 5 * sin(t) + 0.2*x;
}

void  Rk45(std::function<double(double, double)> f, double& t, double& x, double h, double& eps)
{
	double k1, k2, k3, k4, k5, k6, x4;
	double c20 = 0.25, c21 = 0.25;
	double c30 = 0.375, c31 = 0.09374, c32 = 0.28125;
	double c40 = 12.0 / 13.0, c41 = 1932.0 / 2197.0;
	double c42 = -7200.0 / 2197.0, c43 = 7296.0 / 2197.0;
	double c51 = 439.0 / 216.0, c52 = -8.0;
	double c53 = 3680.0 / 513.0, c54 = -845.0 / 4104.0;
	double c60 = 0.5, c61 = -8.0 / 27.0, c62 = 2.0;
	double c63 = -3544.0 / 2565.0, c64 = 1859.0 / 4104.0;
	double c65 = -0.275;
	double a1 = 25.0 / 216.0, a2 = 0.0, a3 = 1408.0 / 2565.0;
	double a4 = 2197.0 / 4104.0, a5 = -0.2;
	double b1 = 16.0 / 135.0, b2 = 0.0, b3 = 6656.0 / 12825.0;
	double b4 = 28561.0 / 56430.0, b5 = -0.18;
	double b6 = 2.0 / 55.0;
	k1 = h * f(t, x);
	k2 = h * f(t + c20 * h, x + c21 * k1);
	k3 = h * f(t + c30 * h, x + c31 * k1 + c32 * k2);
	k4 = h * f(t + c40 * h, x + c41 * k1 + c42 * k2 + c43 * k3);
	k5 = h * f(t + h, x + c51 * k1 + c52 * k2 + c53 * k3 + c54 * k4);
	k6 = h * f(t + c60 * h, x + c61 * k1 + c62 * k2 + c63 * k3 + c64 * k4 + c65 * k5);
	x4 = x + a1 * k1 + a3 * k3 + a4 * k4 + a5 * k5;
	x = x + b1 * k1 + b3 * k3 + b4 * k4 + b5 * k5 + b6 * k6;
	t = t + h;
	eps = std::fabs(x - x4);
	return;
}

void RK45_Adaptive(double t, double x, double h, double tb, int& itmax, double emax, double emin, double hmin, double hmax, int& iflag)
{
	double xsave, tsave, e, d;
	int n;
	double delta = pow(10, -5) / 2;
	cout << 0 << " " << h << " " << t << " " << x << endl;
	iflag = 1;
	int k = 0;
	while (k <= itmax)
	{
		k = k + 1;
		if (abs(h) < hmin) { h = sgn(h)*hmin; }
		if (abs(h) > hmax) { h = sgn(h)*hmax; }
		double d = fabs(tb - t);
		if (d <= abs(h))
		{
			iflag = 0;
			if (d <= delta * max(abs(tb), abs(t)))
			{
				break;
			}
			h = sgn(h)*d;
		}
		xsave = x;
		tsave = t;
		Rk45(f, t, x, h, e);
		cout << k << " " << h << " " << x << " " << h << " " << e << endl;
		if (iflag == 0) { break; }
		if (e < emin) { h = 2 * h; }
		if (e > emax)
		{
			h = h / 2;
			x = xsave;
			t = tsave;
			k = k - 1;
		}
	}
	return;
}

int main()
{
	int iflag = 0;
	int itmax = 1000;
	double t, x, h, tb;
	double emax = pow(10.0, -5);
	double emin = pow(10.0, -8);
	double hmin = pow(10.0, -6);
	double hmax = 1.0;
	t = 0.0;
	x = 0.0;
	h = 0.01;
	tb = 10.0;
	RK45_Adaptive(t, x, h, tb, itmax, emax, emin, hmin, hmax, iflag);
	cout << itmax << " " << iflag << endl;

	return 0;

}