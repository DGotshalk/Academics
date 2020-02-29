//Drew gotshalk
//First!
//This program is a simulation of taking the derivative of sin as h gets close to zero. The problem is at some point h gets so small that it becomes indistinguishable from 0, causing unintended behaviors.
//Edited for lab 13

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	int i, imax, n = 50;
	long double error, y, x = 0.5, h = 1, emax = 0, pasterror;
	h = 0.25*h; // gets closer to 0
	y = (sin(x + h) - sin(x)) / h; // the derivative. 
	pasterror = fabs(cos(x) - y) + 1;
	for (i = 0; i < n; i++)
	{
		 // gets closer to 0
		y = (sin(x + h) - sin(x)) / h; // the derivative. 
		h = 0.25*h;
		error = fabs(cos(x) - y); // the difference between our derivative and the value we know to be the derivative 
		if (error > pasterror)
		{
			emax = pasterror;
			imax = i - 1;
			break;
		}
		else {
			pasterror = error;
			std::cout << "I:" << i + 1 << " \nh:" << h << " \ny:" << y << " \nError:" << error << "\n\n";
			if (error > emax)
			{
				emax = error;
				imax = i;
			}
		}
	}
	std::cout << "Imax:" << imax << " Emax:" << emax << "\n";
	system("pause");
	return 0;
}