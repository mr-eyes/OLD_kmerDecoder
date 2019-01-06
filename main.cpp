#include "skipmers.hpp"
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    std::queue<std::string> kmers;
    std::queue<std::string> skipmers;

    string seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGG";
    Skipmers sk = Skipmers(2, 3, 14);

    sk.getSkipmers(skipmers, seq);

    Default df = Default(14);
    df.get_kmers(kmers, seq);
    
    int count = 0;
    while (!kmers.empty()){
        std::cout << ++count << ": " << kmers.front() << std::endl;
        kmers.pop();
    }
    count = 0;
    std::cout << "SKIPMERS ---------------------- \n" << std::endl;
    while (!skipmers.empty())
    {
        std::cout << ++count << ": " << skipmers.front() << std::endl;
        skipmers.pop();
    }
}