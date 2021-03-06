#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                       bootstrap script for linux
#
#
##===----------------------------------------------------------------------===##


##==
#
# enter home directory
#
##==
cd


##==
#
# build directory hierarchy
#
##==
mkdir -p local/applications
mkdir -p local/libraries
mkdir -p local/bin
mkdir -p local/etc
mkdir -p local/usr
mkdir -p local/usr/bin
mkdir -p local/usr/include
mkdir -p local/usr/lib
mkdir -p local/usr/share

mkdir -p repositories
mkdir -p projects

mkdir -p archive
mkdir -p downloads
mkdir -p temporaries
mkdir -p trash


##==
#
# build symbolic links to directories
#
##==
ln -snf temporaries             tmp
ln -snf productivity/scripts    bin
ln -snf productivity/snippets   snippets
ln -snf productivity/codebase   codebase


##==
#
# build symbolic links to files
#
##==
ln -snf productivity/runcoms/bashrc .bash_profile
ln -snf productivity/runcoms/vimrc  .vimrc
ln -snf productivity/runcoms/tmuxrc .tmux.conf


##===----------------------------------------------------------------------===##

