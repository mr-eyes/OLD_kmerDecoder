#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <string>
#include <cstring>
#include <sstream>
#include <locale>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <omp.h>
#include <assert.h>
#include <bitset>
#include "input_module.hpp"

using namespace std;

InputModule *InputModuleMinimzers::initialize(int k, int w)
{
    return new InputModuleMinimzers(k, w);
}

void InputModuleMinimzers::kmerize(char *seq, const int &seq_len, const int &k, char **kmers, int &kmer_num)
{
    char **ret = new char *[seq_len - k];
    kmer_num = seq_len - k;
    for (int i = 0; i < kmer_num; ++i)
    {
        ret[i] = new char[k + 1];
        memcpy(ret[i], seq + i, k);
    }
}
/* Returns the forward kmers of a sequence */
vector<string> InputModuleMinimzers::kmerize(string seq, int k)
{
    vector<string> ret(seq.length() - k, "");

#pragma omp parallel for
    for (int i = 0; i < seq.length() - k; i++)
    {
        string s = seq.substr(i, k);
        //#pragma omp atomic read
        ret[i] = s;
        //ret.push_back(s);
        //ret.push_back(reverse(reverse_complement(s)));
    }
    return ret;
};

InputModuleMinimzers::mkmh_kmer_list_t InputModuleMinimzers::kmerize(char *seq, int seq_len, int k)
{
    mkmh_kmer_list_t ret;
    ret.kmers = new char *[seq_len - k];
    ret.k = k;
    ret.length = seq_len - k;

    for (int i = 0; i < ret.length; ++i)
    {
        char *km = new char[k + 1];
        memcpy(km, seq + i, k);
        ret.kmers[i] = new char[k + 1];
        ret.kmers[i] = km;
        ret.kmers[i][k] = '\0';
    }
    return ret;
};

/** Returns an mkmh_minimizer struct, equivalent to a tuple(kmer, position, kmer length), for every position in the genome **/
vector<mkmh_minimizer> InputModuleMinimzers::kmer_tuples(string seq, int k)
{
    vector<string> kmers = this->kmerize(seq, k);
    vector<mkmh_minimizer> tups(kmers.size());
    for (int i = 0; i < kmers.size(); i++)
    {
        mkmh_minimizer mm;
        mm.seq = kmers[i];
        mm.pos = i;
        mm.length = k;
        tups[i] = mm;
    }

    return tups;
}

template <typename T>
vector<T> InputModuleMinimzers::v_set(vector<T> kmers)
{
    set<T> s = set<T>(kmers.begin(), kmers.end());
    vector<T> ret = vector<T>(s.begin(), s.end());
    return ret;
}

/** Finds the (w, k) minimizers of a string **/
vector<mkmh_minimizer> InputModuleMinimzers::getMinimizers(string &seq)
{
    vector<mkmh_minimizer> ret;
    vector<mkmh_minimizer> kmert = kmer_tuples(seq, this->k);
    int i = 0;
    for (i = 0; i + this->w < kmert.size(); ++i)
    {
        // get and sort kmers in window (i, i + w)
        vector<mkmh_minimizer> window_kmers(kmert.begin() + i, kmert.begin() + i + this->w);
        std::sort(window_kmers.begin(), window_kmers.end());
        ret.push_back(*(window_kmers.begin()));
    }
    return v_set(ret);
}

void InputModuleMinimzers::getKmers(std::queue<std::string> &kmers, std::string &seq)
{
    vector<mkmh_minimizer> ret;
    vector<mkmh_minimizer> kmert = kmer_tuples(seq, this->k);
    int i = 0;
    for (i = 0; i + this->w < kmert.size(); ++i)
    {
        // get and sort kmers in window (i, i + w)
        vector<mkmh_minimizer> window_kmers(kmert.begin() + i, kmert.begin() + i + this->w);
        std::sort(window_kmers.begin(), window_kmers.end());
        ret.push_back(*(window_kmers.begin()));
    }
    for (auto z : v_set(ret))
    {
        kmers.push(z.seq);
    }
}