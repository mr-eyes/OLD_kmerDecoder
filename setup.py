from distutils.core import setup, Extension


kmerDecoder_module = Extension('_kmerDecoder',
                               sources=[
                                   'kmerDecoder_wrap.cxx', 'src/input_module.cpp', 'src/InputModuleMinimzers.cpp'],
                               include_dirs=["include"], language='c++'
                               )

setup(name='kmerDecoder',
      version='0.1',
      author="Mohamed Abuelanin",
      description="""kmerDecoder python wrapper""",
      ext_modules=[kmerDecoder_module],
      py_modules=["kmerDecoder"],
      )
