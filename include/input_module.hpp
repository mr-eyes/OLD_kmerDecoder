#include <string>
#include <iostream>
#include <queue>
#include <set>

typedef struct mkmh_minimizer
{
  uint64_t pos;
  uint32_t length;
  std::string seq;
  bool operator<(const mkmh_minimizer &rhs) const { return seq < rhs.seq; };
} mkmh_minimizer;

typedef struct mkmh_kmer_list_t
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
} mkmh_kmer_list_t;

class InputModule
{
public:
  static InputModule *initialize(uint8_t m, uint8_t n, uint8_t k); // Skipmers
  static InputModule *initialize(int k, int w);                    // Minimizers
  static InputModule *initialize(uint kSize);                      // Default
  virtual void getKmers(std::queue<std::string> &kmers, std::string &seq) = 0;
};

class InputModuleSkipmers : InputModule
{
private:
  uint8_t m, n, k;
  uint S;

public:
  InputModuleSkipmers(uint8_t m, uint8_t n, uint8_t k)
  {
    if (n < 1 or n < m or k < m or k > 31 or k % m != 0)
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
  void getKmers(std::queue<std::string> &kmers, std::string &x);
  static InputModule *initialize(uint8_t m, uint8_t n, uint8_t k);
};

class InputModuleDefault : InputModule
{
private:
  int kSize;

public:
  InputModuleDefault(int kSize)
  {
    this->kSize = kSize;
  }
  void getKmers(std::queue<std::string> &kmers, std::string &x);
  static InputModule *initialize(uint kSize);
};

class InputModuleMinimzers : InputModule
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
  InputModuleMinimzers(int k, int w)
  {
    this->k = k;
    this->w = w;
  }
  std::vector<mkmh_minimizer> getMinimizers(std::string &seq);
  void getKmers(std::queue<std::string> &kmers, std::string &x);
  static InputModule *initialize(int k, int w);
};
