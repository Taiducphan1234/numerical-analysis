# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitclone-lastrun.txt" AND EXISTS "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitinfo.txt" AND
  "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitclone-lastrun.txt" IS_NEWER_THAN "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/autodiff/autodiff.git" "autodiff-src"
    WORKING_DIRECTORY "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/autodiff/autodiff.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe"
          checkout "v0.6.4" --
  WORKING_DIRECTORY "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v0.6.4'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitinfo.txt" "C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/Users/Hello/CLionProjects/numerical analysis/cmake-build-debug/_deps/autodiff-subbuild/autodiff-populate-prefix/src/autodiff-populate-stamp/autodiff-populate-gitclone-lastrun.txt'")
endif()
