#include <string>
#include "skipmers.hpp"
#include <iostream>
#include <queue>

void Default::get_kmers(std::queue<std::string> &kmers, std::string &seq)
{
    for (int i = 0; i < seq.size() - this->kSize + 1; i++)
    {
        kmers.push(seq.substr(i, this->kSize));
    }
}

void Skipmers::getSkipmers(std::queue<std::string> &kmers, std::string &seq)
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
        // std::cout << skipmer << std::endl;
        kmers.push(skipmer);
    }
}
