//Drew Gotshalk
// My attempt at naive gauss in the textbook. The fully connected one i think?

#include <iostream>
#include <cmath>


using namespace std;

int main()
{
	int i, j, k, n;
	double sum, xmult;

	cout << "this code is made to solve n linear equations with n unknowns, so please inptut n" << endl;
	cin >> n;

	double** a = new double*[n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];
	double *b;
	b = new double[n];
	double *x;
	x = new double[n];
	for (int i = 0; i < n; i++) {
		cout << "please enter coefficionts for the " << i + 1 << " row" << endl;
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		cout << "please enter soltution for the " << i + 1 << " row" << endl;
		cin >> b[i];
	}


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
		cout << "i= " << i << " a[i][0 to n]: ";
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << "b[i]= " << b[i] << " x[i]= " << x[i] << endl;
	}
	system("pause");
	return 0;
}