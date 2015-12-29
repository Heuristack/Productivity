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

##==
#
# QuickFIX
#
##==
cd $RP_HOME/quickfix.git
./configure --prefix=$LOCAL_USR --exec-prefix=$LOCAL_USR
make
make install

##===----------------------------------------------------------------------===##

