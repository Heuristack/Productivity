#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                            build repositories 
#
#
##===----------------------------------------------------------------------===##
cd $RP_HOME

##==
#
# boost
#
##==
cd boost.git
./bootstrap.sh
./b2 --prefix=$LOCAL_USR --exec-prefix=$LOCAL_USR install
cd -

##==
#
# QuickFIX
#
##==
cd quickfix.git
./bootstrap
./configure --prefix=$LOCAL_USR --exec-prefix=$LOCAL_USR
make
make install
cd -

##==
#
# QuantLib
#
##==
cd quantlib.git
./autogen.sh
./configure --enable-static --with-boost-include=$LOCAL_INL --with-boost-lib=$LOCAL_LIB --prefix=$LOCAL_USR
make
make install
cd -

##===----------------------------------------------------------------------===##

