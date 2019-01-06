#include <string>

class Skipmers{
private:
  uint8_t m, n, k;
  int S;

public:
  void setPars(uint8_t m, uint8_t n, uint8_t k);
  void getSkipmers(std::string &x);
};
