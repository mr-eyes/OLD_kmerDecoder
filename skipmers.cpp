#include <string>
#include "skipmers.hpp"
#include <iostream>

void Skipmers::setPars(uint8_t m, uint8_t n, uint8_t k)
{

    if (n < 1 or n < m or k < m or k > 31 or k % m != 0)
    {
        std::cout << "Error: invalid skip-mer shape! m=" << m << " n=" << n << " k=" << k << std::endl
                  << "Conditions: 0 < m <= n, k <= 31 , k must multiple of m." << std::endl;
                  
        exit(1);
    }

    this->m = m;
    this->n = n;
    this->k = k;
    this->S = k + ((k - 1) / m) * (n - m);
}

void Skipmers::getSkipmers(std::string &seq)
{
    std::string skipmer = "";
    
    for (int i = 0; i < seq.size() - this->S + 1; i++)
    {
        skipmer.clear();
        for(int j = i; j < i + this->S; j += this->n){
            skipmer.append(seq.substr(j, this->m));
        }
        std::cout << skipmer << std::endl;
    }
}
