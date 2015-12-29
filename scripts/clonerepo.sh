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
# clone boost from boostorg and add remote linking to heuristack
#
##==
git clone --recursive https://github.com/boostorg/boost.git boost.git

modulelist+=(asio)

for module in ${modulelist[@]}
do
    cd boost.git/libs/$module
    git remote add target $remote/boost-$module.git
    cd -
done
    
##==
#
# clone repos from heuristack
#
##==
function clonerepo()
{
    reponame=$1
    if [ -d $reponame.git ]; then echo "already exist: $reponame"; return; fi
    git clone $remote/$reponame.git $reponame.git
}

repolist+=(quickfix)
repolist+=(quantlib)
repolist+=(git)
repolist+=(xv6)
repolist+=(ace)

for reponame in ${repolist[@]}
do
    clonerepo $reponame
done

##==
#
# clone mpc and build symbolic link for building ace
#
##==
git clone https://github.com/DOCGroup/MPC.git mpc.git
if [ -d ace.git ]; then ln -snf ace.git atcd.git; fi


##===----------------------------------------------------------------------===##

