#include "input_module.hpp"
#include <iostream>
#include <queue>

int main()
{

    int count = 0;

    std::queue<std::string> kmers;
    std::queue<std::string> skipmers;
    std::queue<std::string> minimzers;

    std::string seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGGACGTAGCCTATATTTTGCAACGCGTGAC";

    /* 
    --------------------------------------------------------
                            Skipmers
    --------------------------------------------------------
    */

    const std::vector<int> skipmers_params = {3, 3, 27}; // params = {m, n, k}
    InputModule *skp = InputModuleFactory::newInputModule("skipmers");
    skp->setParms(skipmers_params);
    skp->getKmers(skipmers, seq);

    std::cout << "\n[*] Skipmers -----\n";
    while (!skipmers.empty())
    {
        std::cout << ++count << ": " << skipmers.front() << std::endl;
        skipmers.pop();
    }

    /* 
    --------------------------------------------------------
                        Default kmers
    --------------------------------------------------------
    */

    const std::vector<int> kmers_params = {15}; // params = {k}
    InputModule *df = InputModuleFactory::newInputModule("default");
    df->setParms(kmers_params);
    df->getKmers(kmers, seq);

    count = 0;
    std::cout << "\n[*] Kmers -----\n";
    while (!kmers.empty())
    {
        std::cout << ++count << ": " << kmers.front() << std::endl;
        kmers.pop();
    }

    /* 
    --------------------------------------------------------
                            Minimzers kmers
    --------------------------------------------------------
    */

    const std::vector<int> minimzers_params = {5, 10}; // params = {k, w}
    InputModule *mini = InputModuleFactory::newInputModule("minimzers");
    mini->setParms(minimzers_params);
    mini->getKmers(minimzers, seq);

    count = 0;
    std::cout << "\n[*] Minimzers -----\n";
    while (!minimzers.empty())
    {
        std::cout << ++count << ": " << minimzers.front() << std::endl;
        minimzers.pop();
    }

    /* 
    --------------------------------------------------------
                            Minimzers kmers triples
    --------------------------------------------------------
    */
    // std::cout << "\n[*] Minimzers kmers triples -----\n" << std::endl;

    // InputModuleMinimzers *mini_triples = new InputModuleMinimzers(5, 10);
    // vector<mkmh_minimizer> mh = mini_triples->getMinimizers(seq);
    // for (auto z : mh)
    // {
    //     cout << "pos: " << z.pos << "  len: " << z.length << "  seq: " << z.seq << endl;
    // }
}