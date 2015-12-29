#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                            build repositories 
#
#
##===----------------------------------------------------------------------===##

##==
#
# boost
#
##==
cd $RP_HOME/boost.git
./bootstrap.sh
./b2 --prefix=$LOCAL_USR --exec-prefix=$LOCAL_USR install

##==
#
# QuickFIX
#
##==
cd $RP_HOME/quickfix.git
./bootstrap
./configure --prefix=$LOCAL_USR --exec-prefix=$LOCAL_USR
make
make install

##===----------------------------------------------------------------------===##

