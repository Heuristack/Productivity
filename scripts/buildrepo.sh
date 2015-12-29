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
cd -

##===----------------------------------------------------------------------===##

