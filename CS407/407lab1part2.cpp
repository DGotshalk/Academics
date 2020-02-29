//In Soviet Russia, Program Spells You
//Drew Gotshalk.

#include <iostream>
#include <string>

int main()
{
	std::string first[4] = { "Cheb", "Ceb", "Tscheb", "Tcheb" };
	std::string second[2] = { "y","i" };
	std::string third[5] = { "shev", "schef", "cev", "cheff", "scheff" };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			for (int h = 0; h < 5; h++) {
				std::cout << first[i] << second[j] << third[h] << "\n";
			}
		}
	}
	system("pause");
	return 0;
}