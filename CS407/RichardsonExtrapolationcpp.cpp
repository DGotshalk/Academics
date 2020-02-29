//This is the derivative function from the texbook
//drew gotshalk
//lab13
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void DerviativeA(double x, int n) // f(x)=sin(x)
{

	vector<vector<double>> d;
	for (int i = 0; i < n; i++)
		d.push_back(vector<double>(n, 0));
	double h = 1;
	int i, j;
	for (i = 0; i < n; i++)
	{
		d[i][0] = ((sin(x + h) - sin(x - h)) / 2 * h);
		for (j = 1; j < i; j++)
		{
			d[i][j] = d[i][j - 1] + (d[i][j - 1] - d[i - 1][j - 1]) / (pow(4, j) - 1);
		}
		h = h/2;
	}
	for (i = 0; i < n; i++) {
		cout << "this is the " << i + 1 << "row of the array: ";
		for (j = 0; i < n; i++)
			cout << d[i][j] << ", ";
		cout << endl;
	}
}
void DerviativeB(double x, int n) // f(x)=cos(x)
{

	vector<vector<double>> d;
	for (int i = 0; i < n; i++)
		d.push_back(vector<double>(n, 0));
	double h = 1;
	int i, j;
	for (i = 0; i < n; i++)
	{
		d[i][0] = ((cos(x + h) - cos(x - h)) / 2 * h);
		for (j = 1; j < i; j++)
		{
			d[i][j] = d[i][j - 1] + (d[i][j - 1] - d[i - 1][j - 1]) / (pow(4, j) - 1);
		}
		h = h / 2;
	}
	for (i = 0; i < n; i++) {
		cout << "this is the " << i + 1 << "row of the array: ";
		for (j = 0; i < n; i++)
			cout << d[i][j] << ", ";
		cout << endl;
	}
}
void DerviativeC(double x, int n) // f(x)=arctan(x)
{

	vector<vector<double>> d;
	for (int i = 0; i < n; i++)
		d.push_back(vector<double>(n, 0));
	double h = 1;
	int i, j;
	for (i = 0; i < n; i++)
	{
		d[i][0] = ((atan(x + h) - atan(x - h)) / 2 * h);
		for (j = 1; j < i; j++)
		{
			d[i][j] = d[i][j - 1] + (d[i][j - 1] - d[i - 1][j - 1]) / (pow(4, j) - 1);
		}
		h = h / 2;
	}
	for (i = 0; i < n; i++) {
		cout << "this is the " << i + 1 << "row of the array: ";
		for (j = 0; i < n; i++)
			cout << d[i][j] << ", ";
		cout << endl;
	}
}
void DerviativeD(double x, int n) // f(x)=abs(x)
{

	vector<vector<double>> d;
	for (int i = 0; i < n; i++)
		d.push_back(vector<double>(n, 0));
	double h = 1;
	int i, j;
	for (i = 0; i < n; i++)
	{
		d[i][0] = ((fabs(x + h) - fabs(x - h)) / 2 * h);
		for (j = 1; j < i; j++)
		{
			d[i][j] = d[i][j - 1] + (d[i][j - 1] - d[i - 1][j - 1]) / (pow(4, j) - 1);
		}
		h = h / 2;
	}
	for (i = 0; i < n; i++) {
		cout << "this is the " << i + 1 << "row of the array: ";
		for (j = 0; i < n; i++)
			cout << d[i][j] << ", ";
		cout << endl;
	}
}
void DerviativeE(double x, int n) // f(x)=sin(x)
{

	vector<vector<double>> d;
	for (int i = 0; i < n; i++)
		d.push_back(vector<double>(n, 0));
	double h = 1;
	int i, j;
	for (i = 0; i < n; i++)
	{
		d[i][0] = ((sin(x + h) - sin(x - h)) / 2 * h);
		for (j = 1; j < i; j++)
		{
			d[i][j] = d[i][j - 1] + (d[i][j - 1] - d[i - 1][j - 1]) / (pow(4, j) - 1);
		}
		h = h / 2;
	}
	for (i = 0; i < n; i++) {
		cout << "this is the " << i + 1 << "row of the array: ";
		for (j = 0; i < n; i++)
			cout << d[i][j] << ", ";
		cout << endl;
	}
}

int main() {
	int n = 10;
	cout << "a):" << endl << endl;
	DerviativeA(1.2309594154, n);
	cout << "b):" << endl << endl;
	DerviativeB(0, n);
	cout << "c):" << endl << endl;
	DerviativeC(1, n);
	cout << "d):" << endl << endl;
	DerviativeD(0, n);
	cout << "e):" << endl << endl;
	DerviativeE(0.5, n);
	system("pause");
	return 0;


}