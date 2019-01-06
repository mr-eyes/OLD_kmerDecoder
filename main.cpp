#include "skip.hpp"
#include <iostream>

using namespace std;

int main()
{

    string seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGG";

    Skipmers sk = Skipmers();
    sk.setPars(2,3,14);
    sk.getSkipmers(seq);

    
}