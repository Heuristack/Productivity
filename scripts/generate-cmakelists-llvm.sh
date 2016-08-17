!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#         generate cmakelists for clion to analyze llvm source codes
#
#
##===----------------------------------------------------------------------===##


##===----------------------------------------------------------------------===##
#
# prepare
#
##==
echo "Notes: 1.run this scripts under project workspace; 2.symbolic link llvm should be created first;" 1>&2
echo "..." 1>&2

proj=llvm
if [ "$1" != "" ]; then proj=$1; fi

mkdir t
##===----------------------------------------------------------------------===##
#
# collect
#
##==

find -H llvm.build/include -type d -maxdepth 0 >> t/llvm.include0.txt
find -H llvm.git/include   -type d -maxdepth 0 >> t/llvm.include0.txt

find -H llvm.git/lib          -type f -name "*.h" -or -name "*.cpp" -or -name "*.inc" >> t/llvm.lib.txt
find -H llvm.git/include/llvm -type f -name "*.h" -or -name "*.cpp" -or -name "*.inc" >> t/llvm.lib.txt


find -H llvm.build/tools/clang/include -type d -maxdepth 0 >> t/clang.include0.txt
find -H llvm.git/tools/clang/include   -type d -maxdepth 0 >> t/clang.include0.txt

find -H llvm.git/tools/clang/lib           -type f -name "*.h" -or -name "*.cpp" -or -name "*.inc" >> t/clang.lib.txt
find -H llvm.git/tools/clang/include/clang -type f -name "*.h" -or -name "*.cpp" -or -name "*.inc" >> t/clang.lib.txt

find -H llvm.git/tools/clang/tools/driver  -type f -name "*.h" -or -name "*.cpp" >> t/clang.main.txt


##===----------------------------------------------------------------------===##
#
# construct 
#
##==

echo "cmake_minimum_required(VERSION 3.3)" 
echo "project($proj)" 
echo

echo 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")'
echo "set(CMAKE_INCLUDE_CURRENT_DIR true)" 
echo

echo "set(SOURCES"
cat t/llvm.lib.txt
cat t/clang.lib.txt
cat t/clang.main.txt
echo ")"
echo

echo "include_directories("
cat t/llvm.include0.txt
cat t/clang.include0.txt
echo ")"
echo


echo 'add_executable(tbricks "${SOURCES}")'
echo

##===----------------------------------------------------------------------===##
#
# clean up
#
##==
rm -rf t
echo "OK!" 1>&2
echo "Hints: 1.delete unuseful includes!; 2 delete t directory;" 1>&2
##===----------------------------------------------------------------------===##

