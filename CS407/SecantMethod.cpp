//Drew Gotshalk
//lab 10

#include <iostream>
#include <cmath>
#include <limits>
//these 3 functions together found all of the roots of the equations. AMAZING

using namespace std;
double f(double x) {
	return pow(x, 3) - 5 * x + 3;
}
double fpp(double x) {
	return 3 * pow(x, 2) - 5;
}

void secantmethod(double a, double b, int nmax)
{
	double epsilon = numeric_limits<double>::epsilon();
	double fa, fb, d;
	fa = f(a);
	fb = f(b);
	if (fabs(fa) > fabs(fb)) {
		swap(a, b);
		swap(fa, fb);
	}
	cout << "0 " << "a: " << a << "fa: " << fa << endl;
	for (int n = 1; n < nmax; n++) {
		if (fabs(fa) > fabs(fb)) {
			swap(a, b);
			swap(fa, fb);
		}
		d=(b-a)/(fb-fa);
		b = a;
		fb = fa;
		d = d * fa;
		if (fabs(d) < epsilon)
		{
			cout << "convergence" << endl;
			return;
		}
		a = a - d;
		fa = f(a);
		cout << n  << " a: " << a << " hx: " << fa << endl;
	}

}
void newtonsmethod( int nmax)
{
	double x, fx, fp, d, epsilon = numeric_limits<double>::epsilon();
	x = 2;
	fx = f(x);
	cout << 0 << " x: " << x << " fx: " << fx << endl;
	for (int n = 0; n < nmax; n++)
	{
		fp = fpp(x);
		if (fabs(fp) < epsilon)
		{
			cout << "small derivative" << endl;
			return;
		}
		d = fx / fp;
		x = x - d;
		fx = f(x);
		cout << n + 1 << " x: " << x << " fx: " << fx << endl;
		if (fabs(d) < epsilon)
		{
			cout << "we have converged";
			return;
		}
	}

}
void bisection(double a, double b, int nmax)
{
	double c, fa, fb,fc, d, epsilon = numeric_limits<double>::epsilon(), error;
	fa = f(a);
	fb = f(b);
	if ((fa > 0 && fb > 0) || (fa < 0 && fb < 0)) {
		cout << "a: " << a << " b: " << b << " fa: " << fa << " fb: " << fb << endl;
		cout << "Function has same signs at a and b" << endl;
		return;
	}
	error = b - a;
	for (int n = 0; n < nmax; n++) {
		error = error / 2;
		c = a + error;
		fc = f(c);
		cout << "n: " << n << " c: " << c << " fc: " << fc << " error: " << error << endl;
		if (fabs(error) < epsilon) {
			cout << "convergence" << endl;
			return;
		}
		if ((fa < 0 && fc > 0) || (fa > 0 && fc < 0)) {
			b = c;
			fb = fc;
		}
		else {
			a = c;
			fa = fc;
		}
	}
	return;

}
int main()
{
	double a = -3;
	double b = 3;
	int nmax = 30;
	cout << "secant method" << endl;
	secantmethod(a, b, nmax);
	cout << "newtons method" << endl;
	newtonsmethod(nmax);
	cout << "bisection method" << endl;
	bisection(a, b, nmax);

	system("pause");
	return 0;
}