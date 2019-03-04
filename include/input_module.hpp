#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <set>

typedef struct mkmh_minimizer
{
  uint64_t pos;
  uint32_t length;
  std::string seq;
  bool operator<(const mkmh_minimizer &rhs) const { return seq < rhs.seq; };
} mkmh_minimizer;

/* 
  --------------------------------------------------------
              Derived Class : SkipMers
  --------------------------------------------------------
*/

class InputModule
{
public:
  virtual void setParms(const std::vector<int> &parms) = 0;
  virtual void getKmers(std::string &seq) = 0;
  virtual ~InputModule(){};
};

class InputModuleSkipmers : public InputModule
{
private:
  int m, n, k;
  int S;

public:
  InputModuleSkipmers() {}
  InputModuleSkipmers(uint8_t m, uint8_t n, uint8_t k)
  {
    if (n < 1 or n < m or k < m)
    {
      std::cout << "Error: invalid skip-mer shape! m= " << m << " n=" << n << " k= " << k << std::endl
                << "Conditions: 0 < m <= n, k <= 31 , k must multiple of m." << std::endl;

      exit(1);
    }

    this->m = m;
    this->n = n;
    this->k = k;
    this->S = k + ((k - 1) / m) * (n - m);
  }
  
  void getKmers(std::string &x);
  void setParms(const std::vector<int> &parms);
  virtual ~InputModuleSkipmers() {}
};

/* 
  --------------------------------------------------------
              Derived Class : Default
  --------------------------------------------------------
*/

class InputModuleDefault : public InputModule
{
protected:
  int kSize;

public:
  InputModuleDefault() {}
  InputModuleDefault(int kSize)
  {
    this->kSize = kSize;
  }
  void getKmers(std::string &x);
  void setParms(const std::vector<int> &parms);
  virtual ~InputModuleDefault() {}
};

/* 
  --------------------------------------------------------
              Derived Class : Minimzers
  --------------------------------------------------------
*/

class InputModuleMinimzers : public InputModule
{
private:
  int k, w;
  struct mkmh_kmer_list_t
  {
    char **kmers;
    int length;
    int k;

    mkmh_kmer_list_t(){

    };

    mkmh_kmer_list_t(int length, int k)
    {
      length = length;
      k = k;
      kmers = new char *[length];
    };

    ~mkmh_kmer_list_t()
    {
      for (int i = 0; i < length; ++i)
      {
        delete[] kmers[i];
      }
      delete[] kmers;
    };
  };

protected:
  std::vector<mkmh_minimizer> kmer_tuples(std::string seq, int k);
  mkmh_kmer_list_t kmerize(char *seq, int seq_len, int k);
  std::vector<std::string> kmerize(std::string seq, int k);
  void kmerize(char *seq, const int &seq_len, const int &k, char **kmers, int &kmer_num);
  template <typename T>
  std::vector<T> v_set(std::vector<T> kmers);

public:
  InputModuleMinimzers() {}
  InputModuleMinimzers(int k, int w)
  {
    this->k = k;
    this->w = w;
  }
  std::vector<mkmh_minimizer> getMinimizers(std::string &seq);
  void getKmers(std::string &x);
  void setParms(const std::vector<int> &parms);
  virtual ~InputModuleMinimzers(){};
};

/* 
  --------------------------------------------------------
              Factory Class : InputModuleFactory
  --------------------------------------------------------
*/

class InputModuleFactory
{
public:
  static InputModule *newInputModule(const std::string description)
  {
    if (description == "default")
    {
      return new InputModuleDefault;
    }
    else if (description == "skipmers")
    {
      return new InputModuleSkipmers;
    }
    else if (description == "minimzers")
    {
      return new InputModuleMinimzers;
    }
    else
    {
      std::cerr << "choose only {mode} ⊂ {default, skipemers, minimzers}" << std::endl;
      exit(0);
    }
  }
};
