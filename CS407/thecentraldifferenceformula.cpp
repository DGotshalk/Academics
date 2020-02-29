//Drew gotshalk
//First!
//Edited for lab 13

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	int i, imax, n = 30;
	long double error, y, x = 0.5, h = 1, emax = 0, pasterror;
	y = (1 / 2 * h)*(sin(x + h) - sin(x - h));
	pasterror = fabs(cos(x) - y) + 1;
	for (int i = 0; i < n; i++)
	{
		
		y = ((sin(x + h) - sin(x - h))/ 2 * h); // thisis the central difference formula
		h = .25*h; // gets closer to 0
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

