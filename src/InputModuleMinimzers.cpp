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


/* 
  --------------------------------------------------------
              Derived Class : Minimizers
  --------------------------------------------------------
*/

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
std::vector<std::string> InputModuleMinimzers::kmerize(std::string seq, int k)
{
    std::vector<std::string> ret(seq.length() - k, "");

#pragma omp parallel for
    for (int i = 0; i < seq.length() - k; i++)
    {
        std::string s = seq.substr(i, k);
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
std::vector<mkmh_minimizer> InputModuleMinimzers::kmer_tuples(std::string seq, int k)
{
    std::vector<std::string> kmers = this->kmerize(seq, k);
    std::vector<mkmh_minimizer> tups(kmers.size());
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
std::vector<T> InputModuleMinimzers::v_set(std::vector<T> kmers)
{
    std::set<T> s = std::set<T>(kmers.begin(), kmers.end());
    std::vector<T> ret = std::vector<T>(s.begin(), s.end());
    return ret;
}

/** Finds the (w, k) minimizers of a std::string **/
std::vector<mkmh_minimizer> InputModuleMinimzers::getMinimizers(std::string &seq)
{
    std::vector<mkmh_minimizer> ret;
    std::vector<mkmh_minimizer> kmert = kmer_tuples(seq, this->k);
    int i = 0;
    for (i = 0; i + this->w < kmert.size(); ++i)
    {
        // get and sort kmers in window (i, i + w)
        std::vector<mkmh_minimizer> window_kmers(kmert.begin() + i, kmert.begin() + i + this->w);
        std::sort(window_kmers.begin(), window_kmers.end());
        ret.push_back(*(window_kmers.begin()));
    }
    return v_set(ret);
}

void InputModuleMinimzers::setParms(const std::vector<int> &params)
{
    int k, w;
    this->k = params.at(0);
    this->w = params.at(1);
}

void InputModuleMinimzers::getKmers(std::queue<std::string> &kmers, std::string &seq)
{
    std::vector<mkmh_minimizer> ret;
    std::vector<mkmh_minimizer> kmert = kmer_tuples(seq, this->k);
    int i = 0;
    for (i = 0; i + this->w < kmert.size(); ++i)
    {
        // get and sort kmers in window (i, i + w)
        std::vector<mkmh_minimizer> window_kmers(kmert.begin() + i, kmert.begin() + i + this->w);
        std::sort(window_kmers.begin(), window_kmers.end());
        ret.push_back(*(window_kmers.begin()));
    }
    for (auto z : v_set(ret))
    {
        kmers.push(z.seq);
    }
}