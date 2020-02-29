//drew gotshalk
// lab 20
// bspline eval and coef

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Bspline2coef(int n, vector<double> t, vector<double> y, vector<double>& a, vector<double>& h)
{
	double ything, delta, p, q;

	//vector<double> a(n+1,0);
	//vector<double> h(n+1,0);
	//vector<double> t(n,0);
	//vector<double> y(n,0);

	for (int i = 1; i < n; i++)
	{
		h[i] = t[i] - t[i - 1];
	}
	h[0] = h[1];
	h[n] = h[n - 1];
	delta = -1;
	ything = 2 * y[0];
	p = delta * ything;
	q = 2;
	for (int i = 1; i < n; ++i)
	{
		double r = h[i + 1] / h[i];
		delta = -r * delta;
		ything = -r * ything + (r + 1)*y[i];
		p = p + ything * delta;
		q = q + delta * delta;
	}
	a[0] = -(p / q);
	for (int i = 1; i < n + 1; i++) {
		a[i] = ((h[i - 1] + h[i])*y[i - 1] - h[i] * a[i - 1]) / h[i - 1];
	}
}

double Bspline2eval(int n, vector<double>t, vector<double>a, vector<double> h, double x)
{
	double d, e;
	int i;
	for (i = n - 2; i > -1; --i) {
		if (x - t[i] >= 0)
			break;
	}
	i = i + 1;
	d = (a[i + 1] * (x - t[i - 1]) + a[i] * (t[i] - x + h[i + 1])) / (h[i] + h[i + 1]);
	e = (a[i] * (x - t[i - 1] + h[i - 1]) + a[i - 1] * (t[i - 1] - x + h[i])) / (h[i - 1] + h[i]);
	double BSPLINE2EVAL = (d*(x - t[i - 1]) + e * (t[i] - x)) / h[i];
	return BSPLINE2EVAL;
}

int main()
{
	int n = 20;
	vector<double> t = { 0.0,0.6,1.5,1.7,1.9,2.1,2.3,2.6,2.8,3.0,3.6,4.7,5.2,5.7,5.8,6.0,6.4,6.9,7.6,8.0 };
	vector<double> y = { -0.8,-0.34,0.59,0.59,0.23,0.1,0.28,1.03,1.5,1.44,0.74,-0.82,-1.27,-0.92,-0.92,-1.04,-0.79,-0.06,1.0,0.0 };
	vector<double> a(n + 1, 0);
	vector<double> h(n + 1, 0);
	Bspline2coef(n, t, y, a, h);
	vector<double> plot_points;
	double bspline;
	for (int i = 0; i < n; i++) {
		bspline = Bspline2eval(n, t, a, h, i);
		plot_points.push_back(bspline);
	}
	cout << endl;
	for (int i = 0; i < plot_points.size(); ++i) { cout << plot_points[i] << ", "; }
	cout << endl;
	system("pause");
	return 0;
}