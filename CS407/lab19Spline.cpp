//Drew gOtshalk
//LAb 19


#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;



void spline_3_coef(int n, vector<double> & t, vector<double> &y, vector<double> &z)
{
	vector<double> h(n - 1, 0);
	vector<double> b(n - 1, 0);
	vector<double> u(n - 1, 0);
	vector<double> v(n - 1, 0);
	for (int i = 0; i < n - 1; ++i)
	{
		h[i] = t[i + 1] - t[i];
		b[i] = (y[i + 1] - y[i]) / h[i];
	}
	u[1] = 2 * (h[0] + h[1]);
	v[1] = 6 * (b[1] - b[0]);
	for (int i = 2; i < n - 1; ++i)
	{
		u[i] = 2 * (h[i] + h[i - 1]) - pow(h[i - 1], 2) / u[i - 1];
		v[i] = 6 * (b[i] - b[i - 1]) - h[i - 1]*v[i-1] / u[i - 1];
	}
	z[n - 1] = 0;
	for (int i = n - 2; i > 0; --i)
	{
		z[i] = (v[i] - h[i] * z[i + 1]) / u[i];
	}
	z[0] = 0;
}

double spline_3_eval(int n, vector<double> & t, vector<double> &y, vector<double> &z, double x)
{
	double temp,h;
	int i;
	for (i = n - 2; i > -1; --i)
	{
		if (x - t[i] >= 0) { break; }
	}
	h = t[i + 1] - t[i];
	temp = (z[i] / 2)+(x - t[i])*(z[i + 1] - z[i]) / (6 * h);

	return y[i] + (x - t[i])*temp;
}

int main() // Test spline
{
	double e, h, x;
	int n, i;
	n = 9;
	vector<double> t(n, 0);
	vector<double> y(n, 0);
	vector<double> z(n, 0);
	double a = 0;
	double b = 1.6875;
	h = (b - a) / n;
	for (i = 0; i < n; ++i)
	{
		t[i] = a + i * h;
		y[i] = sin(t[i]);
	}
	spline_3_coef(n, t, y, z);
	double temp = 0;
	for (int j = 0; j < 4 * n; j++)
	{
		x = a + j * h / 4;
		e = fabs(sin(x) - spline_3_eval(n, t, y, z, x));
		if (e > temp) { temp = e;}
		cout << "j: " << j << " x: " << x << " e: " << e << endl;
	}
	system("pause");

	return 0;
}