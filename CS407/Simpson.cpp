/// drew gotshalk
/// lab 16


#include <iostream>
#include <cmath>
#include <functional>



double Simpson(std::function<double(double)> f, double a, double b, long double epsilon, double level, double level_max){
	double c, d, e, h;
	double one_simpson, two_simpson, simpson_result, left_simpson, right_simpson;
	level = level + 1;
	h = b - a;
	c = (a + b) / 2;
	one_simpson = h * (f(a) + 4 * f(c) + f(b)) / 6;
	d = (a + c) / 2;
	e = (c + b) / 2;
	two_simpson = h * (f(a) + 4 * f(d) + 2 * f(c) + 4 * f(e) + f(b)) / 12;
	if (level >= level_max){
		simpson_result = two_simpson;
		std::cout << "maximum level reached" << std::endl;
	}
	else {
		if (fabs(two_simpson - one_simpson) < 15 * epsilon)
			simpson_result = two_simpson + (two_simpson - one_simpson) / 15;
		else {
			left_simpson = Simpson(f, a, c, epsilon / 2, level, level_max);
			right_simpson = Simpson(f, c, b, epsilon / 2, level, level_max);
			simpson_result = left_simpson + right_simpson;
		}
	}
	return(simpson_result);
}

int main() {
	long double epsilon = std::pow(10, -5) / 2;
	auto f = [](double x) {return 1 / (1 + std::pow(x, 2));};
	auto g = [](double x) {return std::sqrt(1- std::pow(x, 2)) - x; };
	std::cout << "a)" << 4 * Simpson(f, 0, 1, epsilon, 0, 4) << std::endl;

	std::cout << "b)" << 8 * Simpson(g, 0, 1/std::sqrt(2) , epsilon, 0, 4) << std::endl;
	system("pause");
	return 0;
}