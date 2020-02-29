//Drew Gotshalk
//implementing Tri for the textbook


#include <iostream>
#include <vector>


using namespace std;


int main()
{
	int n, i;
	double xmult;
	vector<double> a(n, 0); // first row
	vector<double> d(n, 0); // second row
	vector<double> c(n, 0); // third row 
	vector<double> b(n, 0); // right hand side vector
	vector<double> x(n, 0); // solutions vector

	

	for (i = 1; i < n; i++) {
		xmult = a[i - 1] / d[i - 1];
		d[i] = d[i] - xmult * c[i - 1];
		b[i] = b[i] - xmult * b[i - 1];
	}
	x[n-1] = b[n-1] / d[n-1];
	for (i = n - 2; i > -1; i--) {
		x[i] = (b[i] - c[i] * x[i + 1]) / d[i];
	}
	system("pause");
	return 0; 
}