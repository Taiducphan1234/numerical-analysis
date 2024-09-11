# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-src"
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-build"
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix"
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/tmp"
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp"
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src"
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
