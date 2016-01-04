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
./b2 --help
./b2 --prefix=$LOCAL_USR --exec-prefix=$LOCAL_USR -aq install
cd - &> /dev/null

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
cd - &> /dev/null

##==
#
# QuantLib
#
##==
cd quantlib.git
./autogen.sh
./configure --enable-static --with-boost-include=$LOCAL_INC --with-boost-lib=$LOCAL_LIB --prefix=$LOCAL_USR
make
make install
cd - &> /dev/null

##==
#
# ACE
#
##==

importstring='#include "ace/config-macosx-mavericks.h"'
echo $importstring > $ACE_ROOT/ace/config.h

importstring='include $(ACE_ROOT)/include/makeinclude/platform_macosx_mavericks.GNU'
prefixstring='INSTALL_PREFIX = $(LOCAL_USR)'

makeinclude=$ACE_ROOT/include/makeinclude/platform_macros.GNU

: > $makeinclude
echo $importstring >> $makeinclude
echo $prefixstring >> $makeinclude

cd $ACE_ROOT
bin/mwc.pl -type gnuace ace.mwc
make
make install
cd - &> /dev/null

##===----------------------------------------------------------------------===##

