#include "input_module.hpp"
#include <iostream>
#include <queue>

using namespace std;

int main()
{

    int count = 0;

    string seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGGACGTAGCCTATATTTTGCAACGCGTGACA";
    /* 
    --------------------------------------------------------
                            Skipmers
    --------------------------------------------------------
    */

    const vector<int> skipmers_params = {2, 3, 14}; // params = {m, n, k}
    InputModule *skp = InputModuleFactory::newInputModule("skipmers");
    skp->setParms(skipmers_params);

    skp->getKmers(seq);

    std::cout << "\n[*] Skipmers -----\n";
    std::cout << seq << endl;

    return 0;

}