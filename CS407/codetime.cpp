//Drew Gotshalk
//lab 11a
//code time my dude
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void Coef(int n, vector<double> x, vector<double> &y, vector<double> &a)
{
	int i, j;
	for (i = 0; i < n; i++) {
		a.push_back(y[i]);
	}
	for (j = 1; j < n; j++) {
		for (i = n-1; i > j; i--) {
			a[i] = (a[i] - a[i - 1]) / (x[i] - x[i - j]);
		}
	}
}
double Eval(int n, vector<double> &x, vector<double> &a, double t)
{
	int i;
	double temp = a[n-1];
	for (i = n - 2; i <= 0; i--)
		temp = temp * (t - x[i]) + a[i];
	return temp;
}
int main() {

	double t, e, h, p, emax, pmax, tmax;
	int j, k, n, jmax;
	vector<double> x;
	vector<double> y;
	vector<double> a;
	n = 9;
	h = 1.6875 / n;
	for (k = 0; k < n; k++)
	{
		x.push_back(h * k);
		y.push_back(sin(x[k]));
	}
	Coef(n, x, y, a);
	cout << "a[i] array after Coef call " << endl;
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << endl;
	emax = 0;
	cout << emax << endl;

	for (j = 0; j < 4 * n; j++) {
		t = j * h / 4;
		p = Eval(n, x, a, t);
		e = fabs(sin(t) - p);
		cout << "outputting j,y,p,sin(t),e" << endl;
		cout <<"j:"<< j << " "<< "t:" << t << " "  << "p:"<< p << " " << "sin(t):" <<sin(t) << " " << "e:" << e << endl;
		if (e > emax) {
			jmax = j;
			tmax = t;
			pmax = p;
			emax = e;
		}
	}
	cout << "outputing a:" << endl;
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << endl;
	cout << "outputting max values " << endl;
	cout << "jmax:" << jmax << " tmax:" << tmax << " pmax:" << pmax << " emax:" << emax << endl;
	system("pause");
	return 0;




}