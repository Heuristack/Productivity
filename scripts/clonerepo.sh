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

function clonerepo()
{
    reponame=$1
    if [ -d $reponame.git ]; then echo "already exist: $reponame"; return; fi
    git clone $remote/$reponame.git $reponame.git
}

repolist+=(quickfix)
repolist+=(boost)

for reponame in ${repolist[@]}
do
    clonerepo $reponame
done

##===----------------------------------------------------------------------===##

