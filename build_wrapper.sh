rm -rf *cxx *so *gch *pyc 
swig -c++ -python kmerDecoder.i
python setup.py build_ext --inplace