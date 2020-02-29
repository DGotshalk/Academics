//Drew Gotshalk
//Test it again from the homework
// I wasnt expecting these to be the answers, but i have verified the x's up to the 40th position to be correct within 3 decimal places when i plug them back into the original matrix. This thing is amazing!


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
	a[0] = 1;
	d[0] = 4;
	c[0] = -1;
	b[0] = -20;
	for (i = 1; i < 99; i++)
	{
		a[i] = 1;
		d[i] = -4;
		c[i] = 1;
		b[i] = 40;
		if (i == 98)
			a[i] = -1;
	}
	b[99] = -20;
	d[99] = 1;


	for (i = 1; i < n; i++) {
		xmult = a[i - 1] / d[i - 1];
		d[i] = d[i] - xmult * c[i - 1];
		b[i] = b[i] - xmult * b[i - 1];
	}
	x[n - 1] = b[n - 1] / d[n - 1];
	for (i = n - 2; i > -1; i--) {
		x[i] = (b[i] - c[i] * x[i + 1]) / d[i];
	}
	for (i = 0; i < n; i++)
		cout << "x_" << i+1 << ": " << x[i] << endl;
	system("pause");
	return 0;
}