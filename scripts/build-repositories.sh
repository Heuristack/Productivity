#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                            build repositories 
#
#
##===----------------------------------------------------------------------===##
cd $RP_HOME

if false; then echo "skip ... until fi";
##==
#
# Boost
#
##==
cd boost.release
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
#./configure --enable-static --with-boost-include=$LOCAL_DYL/boost/include --with-boost-lib=$LOCAL_DYL/boost/lib --prefix=$LOCAL_USR
make
make install
cd - &> /dev/null

##==
#
# ACE - Mavericks
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

##==
#
# libpcap
#
##==
cd libpcap.git
./configure --prefix=$LOCAL_USR
make
make install
command rm -f $LOCAL_INC/pcap-*.h
cd - &> /dev/null

##==
#
# tcpdump
#
##==
cd tcpdump.git
LDFLAGS=-L$LOCAL_LIB ./configure --sbindir=$LOCAL_APP/tcpdump --mandir=/dev/null
make
make install
cd - &> /dev/null

##==
#
# nginx
#
##==
cd nginx.git
auto/configure --prefix=$LOCAL_APP/nginx
make
make install
cd - &> /dev/null

##==
#
# xv6 on linux
#
##==
if [ "$(uname)" == "Linux" ]; then 
cd xv6.git
make
cd - &> /dev/null
fi

##==
#
# googletest
#
##==
pushd .
cd googletest.git;
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=$LOCAL_USR ..
make
make install
cd - &> /dev/null
rm -rf build
popd

##==
#
# google protobuf
#
##==
cd protobuf.git
./autogen.sh
./configure --prefix=$LOCAL_USR
make
make install
cd - &> /dev/null

##==
#
# LLVM (Uninstallation: make uninstall)
# Note: 14G+ is required for build
#
##==
if [ -d llvm.build ]; then mkdir llvm.build; fi
cd llvm.build
if false; then echo "The LLVM project no longer supports building with configure & make.";
../llvm.git/configure --prefix=$LOCAL_USR
make
make install
fi

cmake -DCMAKE_INSTALL_PREFIX=$LOCAL_USR ../llvm.git
cmake --build .
cmake --build . --target install

cd - &> /dev/null

fi
##==
#
# Berkeley DB
#
##==
BDB_version=6.1.26
cd db-${BDB_version}/build_unix
../dist/configure --prefix=$LOCAL_USR --includedir=$LOCAL_INC/berkeleydb
make
make install
cd - &> /dev/null

##==
#
# Berkeley DB XML (simple build)
#
##==
BDBXML_buildmode=simple
BDBXML_version=6.0.18
cd dbxml-${BDBXML_version}
if [ $BDBXML_buildmode == "simple" ]; then  buildall.sh --prefix=$LOCAL_USR; 
else 
:
fi
cd - &> /dev/null

exit
##==
#
# LTTng
#
##==
if [ "$(uname)" == "Linux" ]; then 
cd lttng-tools.git
./bootstrap
./configure -prefix=$LOCAL_USR
make
make install
ldconfig
cd - &> /dev/null

cd lttng-ust.git
./bootstrap
./configure -prefix=$LOCAL_USR
make
make install
ldconfig
cd - &> /dev/null

cd lttng-modules.git
make
make modules_install
depmod -a
cd - &> /dev/null
fi

##==
#
# Wireshark
#
##==

##==
#
# libdispatch
#
##==

##===----------------------------------------------------------------------===##

