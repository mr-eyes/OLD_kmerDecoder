#include "input_module.hpp"
#include <iostream>
#include <queue>

using namespace std;

int main()
{
    std::queue<std::string> kmers;
    std::queue<std::string> skipmers;

    string seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGG";

    InputModule *skp = InputModule::initialize(2, 3, 14);
    skp->getKmers(skipmers, seq);

    InputModule *df = InputModule::initialize(15);
    df->getKmers(kmers, seq);

    int count = 0;
    std::cout << "KMERS --------------- \n" << std::endl;
    while (!kmers.empty())
    {
        std::cout << ++count << ": " << kmers.front() << std::endl;
        kmers.pop();
    }
    count = 0;
    std::cout << "\nSKIPMERS --------------- \n" << std::endl;
    while (!skipmers.empty())
    {
        std::cout << ++count << ": " << skipmers.front() << std::endl;
        skipmers.pop();
    }

    std::cout << "\nMINIMZERS k-mer triples--------------- \n"
              << std::endl;
    InputModuleMinimzers *mini = new InputModuleMinimzers(5, 10);
    vector<mkmh_minimizer> mh = mini->getMinimizers(seq);
    for (auto z : mh)
    {
        cout << "pos: " << z.pos << "  len: " << z.length << "  seq: " << z.seq << endl;
    }
}