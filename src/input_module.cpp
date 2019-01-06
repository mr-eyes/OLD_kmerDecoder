#include <string>
#include <iostream>
#include <queue>
#include "input_module.hpp"

// BASE
InputModule *InputModule::initialize(uint kSize)
{
    return InputModuleDefault::initialize(kSize);
}

InputModule *InputModule::initialize(uint8_t m, uint8_t n, uint8_t k)
{
    return InputModuleSkipmers::initialize(m, n, k);
}

// DERIVED: InputModuleDefault
InputModule *InputModuleDefault::initialize(uint kSize)
{
    return new InputModuleDefault(kSize);
}

void InputModuleDefault::getKmers(std::queue<std::string> &kmers, std::string &seq)
{
    for (int i = 0; i < seq.size() - this->kSize + 1; i++)
    {
        kmers.push(seq.substr(i, this->kSize));
    }
}

// DERIVED: InputModuleSkipmers

InputModule *InputModuleSkipmers::initialize(uint8_t m, uint8_t n, uint8_t k)
{
    return new InputModuleSkipmers(m, n, k);
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
