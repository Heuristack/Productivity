#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                            clone packages 
#
#
##===----------------------------------------------------------------------===##
cd $RP_HOME

##==
#
# download boost tar package and decompress it
#
##==
latest_boost=https://downloads.sourceforge.net/project/boost/boost/1.60.0/boost_1_60_0.tar.bz2
wget $latest_boost
tar jxvf boost_1_60_0.tar.bz2
ln -sfn boost_1_60_0 boost.release

##==
#
# download ACE tar package and decompress it
#
##==
latest_ace=http://download.dre.vanderbilt.edu/previous_versions/ACE-6.3.3.tar.gz
wget $latest_ace
tar zxvf ACE-6.3.3.tar.gz
ln -sfn ACE_wrappers ace.release

##===----------------------------------------------------------------------===##

