#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
	int n;
	//cout << "this code is made to solve n linear equations with n unknowns, so please inptut n" << endl;
	//cin >> n;
	
	/*
	double** a = new double*[n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];
	int *l;
	l = new int[n];
	double *s;
	s = new double[n];
	
	for (int i = 0; i < n; i++) {
		cout << "please enter coefficionts for the " << i + 1 << " row" << endl;
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	
	double *b;
	b = new double[n];
	
	
	for (int i = 0; i < n; i++) {
		cout << "please enter right hand side for the " << i + 1 << " row" << endl;
		cin >> b[i];
	}
	*/
	//hardcoded the values here, above was for testing random vatraibles


		n = 4;
		double *x = new double[n];
		double a[4][4] = { {0.4096, 0.1234, 0.3678, 0.2943}, {0.2246, 0.3872, 0.4015, 0.1129}, {0.3645, 0.1920, 0.3781, 0.0643}, {0.1784, 0.4002, 0.2786, 0.3927} };
		int l[4];
		double s[4];
		double b[4] = { 0.4043, 0.1550 ,0.4240,0.2557 };
		
		//this program selects a row to start as the pivot point and then eliminates the leading variable of another row
		//and then it does it again until we only have a single leading variable, and then we back subsitite . 
		

	// This is the Gauss portion of this equation.
	int i, j, k;
	double r, rmax, smax, xmult;
	for (i = 0; i < n; i++) {
		l[i] = i;
		smax = 0;
		for (j = 0; j < n; j++)
			smax = max(smax, fabs(a[i][j]));
		s[i] = smax;
	}
	for (k = 0; k < n - 1; k++) {
		rmax = 0;
		for (i = k; i < n; i++) {
			r = fabs(a[l[i]][k]/ s[l[i]]);
			if (r > rmax) {
				rmax = r;
				j = i;
			}
		}
		swap(l[j], l[k]);
		for (i =k+1; i<n;i++){
			xmult = a[l[i]][k] / a[l[i]][k];
			a[l[i]][k] = xmult;
			for (j = k + 1; j < n; j++) {
				a[l[i]][j] = a[l[i]][j] - xmult * a[l[k]][j];
			}
		}
	}
	//This is the end of the Gauss thing, now onto the solve section
	//Start of the solve section
	double sum;
	for (k = 1; k < n - 1; k++) {
		for (i = k + 1; i < n; i++) {
			b[l[i]] = b[l[i]] - a[l[i]][k] * b[l[k]];
		}
	}
	x[n - 1] = b[l[n - 1]] / a[l[n - 1]][n - 1];
	for (i = n - 2; i >= 0; i--) {
		sum = b[l[i]];
		for (j = i + 1; j < n; j++) {
			sum = sum - a[l[i]][j] * x[j];
		}
		x[i] = sum / a[l[i]][i];
	}
	//end of the Solve section


	for (int i = 0; i < n; i++) {
		cout  << " a[" << i << "][0 to n]: ";
		for (int j = 0; j < n; j++)
			cout << "\t"<<a[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i < n; i++)
		cout << "b[" << i << "]= " << b[i] << " \tx[" << i << "]= " << x[i] << endl;
	system("pause");
	return 0;
	
}