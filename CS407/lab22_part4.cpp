//lab 22 runge kutta moments
//this is part 4 
#define _USE_MATH_DEFINES
#include <iostream>
#include <functional>
#include <cmath>
#include <tuple>
#include <vector>
using namespace std;

typedef tuple<int, double, double,double > RK4tup;

double f(double t, double x)
{

	return x + pow(x,2);
}

vector<RK4tup> Rk4(function<double(double, double)> f, double t, double x, double h, int n) {
	vector<RK4tup> output;
	double K1, K2, K3, K4, ta;
	output.push_back(make_tuple(0, t, x, pow(M_E, t) / (16 - pow(M_E, t))));
	ta = t;
	for (int j = 1; j < n; ++j)
	{
		K1 = h * f(t, x);
		K2 = h * f(t + h / 2, x + K1 / 2);
		K3 = h * f(t + h / 2, x + K2 / 2);
		K4 = h * f(t + h / 2, x + K3 / 2);
		x = x + (K1 + 2*K2 + 2*K3 + K4) / 6;
		t = ta + j * h;
		output.push_back(make_tuple(j, t, x, pow(M_E, t) / (16 - pow(M_E, t))));
	}
	return output;
}
//main fits as test_rk4
int main()
{
	//auto f1 = [](double x, double y) -> double{ return 2 + pow(x - y - 1, 2); };
	int n = 72;
	double a = 1, b = 2.77, x = 0.20466341728915526943;
	double h = (b - a) / n;
	double t = a;
	vector <RK4tup> output;
	output = Rk4(f, t, x, h, n);
	for (int i = 0; i < output.size(); ++i)
	{
		cout << get<0>(output[i]) << " " << get<1>(output[i]) << " " << get<2>(output[i]) << " "<< get<3>(output[i]) << endl;
	}
	system("pause");
	return 0;
}