//Drew Gotshalk
//Testing try from the homework problems
// With this example, tri seems to do its job correctly and give the obvious solution of 1 for all x. So all in all for this example it works correctly.

#include <iostream>
#include <vector>


using namespace std;


int main()
{
	int n, i;
	double xmult;
	n = 100;
	vector<double> a(n, 0); // first row
	vector<double> d(n, 0); // second row
	vector<double> c(n, 0); // third row 
	vector<double> b(n, 0); // right hand side vector
	vector<double> x(n, 0); // solutions vector
	a[0] = 0.5;
	d[0] = 1;
	c[0] = 0.5;
	b[0] = 1.5;
	for (i = 1; i < 99; i++)
	{
		a[i] = 0.5;
		d[i] = 1; 
		c[i] = 0.5;
		b[i] = 2;
	}
	b[99] = 1.5;
	d[99] = 1;

	
	for (i = 1; i < n; i++) {
		xmult = a[i - 1] / d[i - 1];
		d[i] = d[i] - xmult * c[i - 1];
		b[i] = b[i] - xmult * b[i - 1];
	}
	x[n-1] = b[n-1] / d[n-1];
	for (i = n - 2; i > -1; i--) {
		x[i] = (b[i] - c[i] * x[i + 1]) / d[i];
	}
	for (i = 0; i < n; i++)
		cout << "x_" << i+1 << ": " << x[i] << endl;
	system("pause");
	return 0;
}