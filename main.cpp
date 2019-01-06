#include "skipmers.hpp"
#include <iostream>

using namespace std;

int main()
{
    string seq = "CCCAGATCTCTTCAGTTTTTATGCCTCATTCTGTGAAAATTGCTGTAGTCTCTTCCAGTT";
    Skipmers sk = Skipmers(1, 3, 31);
    sk.getSkipmers(seq);
}