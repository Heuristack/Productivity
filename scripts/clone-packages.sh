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
tar xvjf boost_1_60_0.tar.bz2
ln -sfn boost_1_60_0 boost.release


##===----------------------------------------------------------------------===##

