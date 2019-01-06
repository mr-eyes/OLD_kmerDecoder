#include <string>
#include "skipmers.hpp"
#include <iostream>

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
