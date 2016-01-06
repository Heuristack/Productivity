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
./bootstrap.sh --prefix=$LOCAL_USR 
./b2 -aq install
cd - &> /dev/null

##==
#
# QuickFIX
#
##==
cd quickfix.git
./bootstrap
./configure --prefix=$LOCAL_USR 
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

if [ "$(uname)" == "Linux" ]; then 
export ACE_ROOT=$RP_HOME/ace.git/ACE 
importstring='#include "ace/config-linux.h"'
fi

headerconfig=$ACE_ROOT/ace/config.h ; > $headerconfig
echo $importstring >> $headerconfig


importstring='include $(ACE_ROOT)/include/makeinclude/platform_macosx_mavericks.GNU'
prefixstring='INSTALL_PREFIX = $(LOCAL_USR)'
if [ "$(uname)" == "Linux" ]; then 
importstring="include $ACE_ROOT/include/makeinclude/platform_linux.GNU"
fi

makeinclude=$ACE_ROOT/include/makeinclude/platform_macros.GNU ; > $makeinclude
echo $importstring >> $makeinclude
echo $prefixstring >> $makeinclude

cd $ACE_ROOT
bin/mwc.pl -type gnuace ace.mwc
make
make install
cd - &> /dev/null

##==
#
# WiredTigher
#
##==
cd wiredtiger.git
./build_posix/reconf
./configure --prefix=$LOCAL_USR --includedir=$LOCAL_USR/include/wiredtiger
make
make install
cd - &> /dev/null

##===----------------------------------------------------------------------===##

