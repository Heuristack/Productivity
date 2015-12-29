#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                            setup git aliases
#
#
##===----------------------------------------------------------------------===##

git config --global user.name heuristack
git config --global user.email heuristack@gmail.com

git config --global alias.s status
git config --global alias.b branch
git config --global alias.r remote
git config --global alias.d diff -w

git config --global alias.get pull --rebase origin
git config --global alias.put push target

##===----------------------------------------------------------------------===##

