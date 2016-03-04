#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                            clone repositories 
#
#
##===----------------------------------------------------------------------===##
cd $RP_HOME
remote=https://github.com/Heuristack

##==
#
# function to clone repo
#
##==
function clonerepo()
{
    reponame=$1
    remote=$2
    if [ -d $reponame.git ]; then echo "already exist: $reponame"; return; fi
    git clone $remote/$reponame.git $reponame.git
}

if false; then echo "skip ... until fi";
##==
#
# clone boost from boostorg and add remote linking to heuristack
#
##==
if [ -d boost.git ]; then echo "already exist: boost"; else
git clone --recursive https://github.com/boostorg/boost.git boost.git; fi

modulelist+=(asio)

for module in ${modulelist[@]}
do
    cd boost.git/libs/$module
    if [[ "$(git remote)" =~ "target" ]]; then echo "already exist: $module (remote 'target')"; 
    else git remote add target $remote/boost-$module.git; git get develop; fi
    cd - &> /dev/null
done
    
##==
#
# clone repos from heuristack
#
##==

repolist+=(quickfix)
repolist+=(quantlib)
repolist+=(git)
repolist+=(xv6)
repolist+=(ace)
repolist+=(wiredtiger)
repolist+=(libpcap)
repolist+=(tcpdump)
repolist+=(nginx)
repolist+=(googletest)
repolist+=(protobuf)

for reponame in ${repolist[@]}
do
    clonerepo $reponame $remote
done

##==
#
# clone mpc and build symbolic link for building ace
#
##==
if [ -d mpc.git ]; then echo "already exist: mpc"; else
git clone https://github.com/DOCGroup/MPC.git mpc.git; fi
if [ -d ace.git ]; then ln -snf ace.git atcd.git; fi

##==
#
# clone llvm, clang, and libcxx
#
##==
if [ -d llvm.git ]; then echo "already exist: llvm"; else
git clone http://llvm.org/git/llvm.git llvm.git; fi

pushd . &> /dev/null; cd llvm.git;

cd tools
git clone http://llvm.org/git/clang.git
cd - &> /dev/null

cd projects
git clone http://llvm.org/git/libcxx.git
git clone http://llvm.org/git/libcxxabi.git
git clone http://llvm.org/git/compiler-rt.git
git clone http://llvm.org/git/openmp.git
git clone http://llvm.org/git/test-suite.git
cd - &> /dev/null

popd &> /dev/null

##==
#
# clone lttng tools, ust, and modules for
#
##==
lttng_remote=git://git.lttng.org

lttng_repolist+=(lttng-tools)
lttng_repolist+=(lttng-ust)
lttng_repolist+=(lttng-modules)

for reponame in ${lttng_repolist[@]}
do
    clonerepo $reponame $lttng_remote
done

##==
#
# libdispatch (GCD)
#
##==
clonerepo libdispatch git://git.macosforge.org 

fi
##==
#
# Wireshark
#
##==
git clone https://code.wireshark.org/review/wireshark

##===----------------------------------------------------------------------===##

