//Drew Gotshalk
// My attempt at naive gauss in the textbook. The fully connected one i think?

#include <iostream>
#include <cmath>


using namespace std;

int main()
{
	int i, j, k, n;
	double sum, xmult;

	n = 4;
	double *x = new double[n];
	double a[4][4] = { {3, -13, 9, 3}, {-6, 4, 1, -18}, {6, -2, 1, 4}, {12, -8, 6, 10} };
	int x[4];
	double s[4];
	double b[4] = { -19, -34 ,16 , 26 };


	for (k = 0; k < n-1; k++) {
		for (i = k + 1; i < n; i++) {
			xmult = a[i][k] / a[k][k];
			a[i][k] = xmult;
			for (j = k + 1; j < n; j++) {
				a[i][j] = a[i][j] - (xmult*a[k][j]);
			}
			b[i] = b[i] - (xmult*b[k]);
		}
	}
	
	x[n-1] = b[n-1] / a[n-1][n-1];
	
	for (i = n - 2; i >=0; i--) {
		sum = b[i];
		for (j = i + 1; i < n; i++) {
			sum = sum - a[i][j] * x[j];
		}
		x[i] = sum / a[i][i];
	}
	
	for (int i = 0; i < n; i++) {
		cout << " a[" << i << "][0 to n]: ";
		for (int j = 0; j < n; j++)
			cout << "\t" << a[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i < n; i++)
		cout << "b[" << i << "]= " << b[i] << " \tx[" << i << "]= " << x[i] << endl;
	system("pause");
	return 0;
}