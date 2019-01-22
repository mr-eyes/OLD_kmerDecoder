#include <string>
#include <iostream>
#include <queue>
#include "input_module.hpp"

/* 
  --------------------------------------------------------
              Derived Class : Default
  --------------------------------------------------------
*/

void InputModuleDefault::setParms(const std::vector<int> &params)
{
    int kSize = params.at(0);
    this->kSize = kSize;
}

void InputModuleDefault::getKmers(std::queue<std::string> &kmers, std::string &seq)
{
    for (int i = 0; i < seq.size() - this->kSize + 1; i++)
    {
        kmers.push(seq.substr(i, this->kSize));
    }
}

/* 
  --------------------------------------------------------
              Derived Class : SkipMers
  --------------------------------------------------------
*/

void InputModuleSkipmers::setParms(const std::vector<int> &params)
{
    int m, n, k;

    m = params.at(0);
    n = params.at(1);
    k = params.at(2);

    if (n < 1 or n < m or k < m or k > 31 or k % m != 0)
    {
        std::cerr << "Error: invalid skip-mer shape! m= " << m << " n=" << n << " k= " << k << std::endl
                  << "Conditions: 0 < m <= n, k <= 31 , k must multiple of m." << std::endl;

        exit(1);
    }
    this->m = m;
    this->n = n;
    this->k = k;
    this->S = k + ((k - 1) / m) * (n - m);
}

void InputModuleSkipmers::getKmers(std::queue<std::string> &kmers, std::string &seq)
{
    if (seq.size() <= this->S)
    {
        std::cerr << "S size is larger than kmer Size\nAborting..." << std::endl;
        exit(1);
    }
    std::string skipmer = "";

    for (int i = 0; i < seq.size() - this->S + 1; i++)
    {
        skipmer.clear();
        for (int j = i; j < i + this->S; j += this->n)
        {
            skipmer.append(seq.substr(j, this->m));
        }
        kmers.push(skipmer);
    }
}
