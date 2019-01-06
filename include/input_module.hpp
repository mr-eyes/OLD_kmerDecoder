#include <string>
#include <iostream>
#include <queue>

class InputModule
{
public:
  static InputModule *initialize(uint8_t m, uint8_t n, uint8_t k);
  static InputModule *initialize(uint kSize);
  virtual void getKmers(std::queue<std::string> &kmers, std::string &x) = 0;
};

class InputModuleSkipmers : InputModule
{
private:
  uint8_t m, n, k;
  int S;

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
