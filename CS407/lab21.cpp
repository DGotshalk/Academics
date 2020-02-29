//Drew Gotshalk
// LAb 21
// we want to use the interval [1,2.77] and derivatives up to x5
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{

	int k;
	long double h, t, x, x1, x2, x3, x4, x5;
	int n = 9001;
	double a = 1, b = 2.77;
	x = 0.20466;
	h = ((2.77-1)/9001);
	t = a;
	cout << 0 << " " << t << " " << x << endl;
	for (int k = 0; k < n; ++k)
	{
		x1 = x+ x*x;

		x2 = 2 * x*x1 + x1;

		x3 = 2*x*x2 + x2 + 2*x2*x1;

		x4 = x3 + 6*x1*x2 + 2*x*x3;

		x5 = 2 * x*x4 + x4 +  6*x2*x2 + 8 * x3*x1;

		x = x + h * (x1 + .5*h*(x2 + (1/3)*h*(x3 + (1 / 4)*h*(x4 + (1/ 5)*h*x5))));

		t = a + k * h;
		cout << k << " " << t << " " << x << endl;
	}
	// answer is off by just a lil bit, maybe around 4
	//probbly roudning error of multiplying the h values
	// my english is not the best but i made it this far 

	system("pause");
	return 0;
}