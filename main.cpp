#include "skipmers.hpp"
#include <iostream>

using namespace std;

int main()
{
    string seq = "ATGAGGGGGATGCCCCTCTTTGAGCCCAAGG";
    Skipmers sk = Skipmers(2, 3, 14);
    sk.getSkipmers(seq);
}