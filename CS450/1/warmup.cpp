//warmup
//Drew Gotshalk
//2020-01-15
#include <iostream>
#include <cmath>

double approximation(int n){
        double iteration = 0;
        for(int i = 0; i <n+1;++i )
                iteration += (std::pow(-1,i)/(2*i+1));
        return 4*iteration;
}

int main(){        
        bool end = false;
        while(end == false){
                std::cout << "please input a positive value of n for approximation (-1 to end the loop)" << std::endl;
                int n;
                std::cin >> n;
                if (n == -1){
                        end = true;
                }
                else{
                        double pi;
                        pi = approximation(n);
                        std::cout<< "the approximate evaluation of pi at " << n << " times is "<< pi << "\n" << std::endl; 
                }
        }
        return 0;
}
