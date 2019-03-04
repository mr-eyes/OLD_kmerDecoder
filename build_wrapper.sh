rm -rf build/ *cxx *so *gch *pyc 
swig -c++ -python -py3 kmerDecoder.i
python3 setup.py build_ext --inplace