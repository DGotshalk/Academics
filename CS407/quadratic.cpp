#include <iostream>
#include <cmath>
int main()
{
	long double a, b, c;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;
	long double r1, r2;
	r1 = (-1 * b + sqrt(pow(b, 2) - (4 * a*c))) / (2 * a);
	r2 = (-1 * b - sqrt(pow(b, 2) - (4 * a*c))) / (2 * a);
	std::cout << r1 << " " << r2 << "\n";
	std::cin.ignore(256, '\n');
	std::cin.get();
	return 0;
}