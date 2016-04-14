#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                       bootstrap script for osx
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
mkdir -p Local/applications
mkdir -p Local/libraries
mkdir -p Local/bin
mkdir -p Local/etc
mkdir -p Local/usr
mkdir -p Local/usr/bin
mkdir -p Local/usr/include
mkdir -p Local/usr/lib
mkdir -p Local/usr/share

mkdir -p Repositories
mkdir -p Projects

mkdir -p Archive
mkdir -p Downloads
mkdir -p Temporaries


##==
#
# build symbolic links to directories
#
##==
ln -snf temporaries               tmp
ln -snf productivity/scripts      bin
ln -snf productivity/snippets     snippets
ln -snf productivity/codebase     codebase
ln -snf productivity/bibliography bibliography


##==
#
# build symbolic links to files
#
##==
ln -snf productivity/runcoms/bashrc  .bash_profile
ln -snf productivity/runcoms/vimrc   .vimrc
ln -snf productivity/runcoms/tmuxrc  .tmux.conf
ln -snf productivity/runcoms/inputrc .inputrc


##===----------------------------------------------------------------------===##

