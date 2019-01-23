%module kmerDecoder
%{  
    #include "include/input_module.hpp"
%}

%include stdint.i
%include std_string.i
%include std_queue.i
%include std_vector.i


// For passing python variables by reference
// --------------------------------------------
%apply std::string& INOUT {std::string& seq};
// --------------------------------------------

%template(strQueue) std::queue<std::string>;
%template(IntVector) std::vector<int>;



/* 
  --------------------------------------------------------
              Base Class : InputModule
  --------------------------------------------------------
*/

class InputModule
{
public:
  virtual void setParms(const std::vector<int> &parms) = 0;
  virtual void getKmers(std::queue<std::string> &kmers, std::string &seq) = 0;
  virtual ~InputModule(){};
};

/* 
  --------------------------------------------------------
              Derived Class : SkipMers
  --------------------------------------------------------
*/

class InputModuleSkipmers : public InputModule
{
private:
  int m, n, k;
  int S;

public:
  InputModuleSkipmers() {}
  void getKmers(std::queue<std::string> &kmers, std::string &seq);
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
  void getKmers(std::queue<std::string> &kmers, std::string &seq);
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
  std::vector<mkmh_minimizer> getMinimizers(std::string &seq);
  void getKmers(std::queue<std::string> &kmers, std::string &seq);
  void setParms(const std::vector<int> &parms);
  virtual ~InputModuleMinimzers(){};
};