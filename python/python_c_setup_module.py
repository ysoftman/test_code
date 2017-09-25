# title : C 모듈 빌드
# author : ysoftman
# desc : C 모듈 빌드

from distutils.core import setup, Extension

module1 = Extension('MyModule',
                    sources=['python_c_test.cpp'])

setup(name='MyPackage',
      version='1.0',
      description='This is a test package',
      ext_modules=[module1])
