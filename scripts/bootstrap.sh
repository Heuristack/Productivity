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
mkdir -p Log

##==
#
# build symbolic links to directories
#
##==
ln -snf productivity/snippets snippets
ln -snf productivity/scripts  Application/bin
ln -snf Temporaries           tmp

##==
#
# build symbolic links to files
#
##==
ln -snf productivity/runcoms/bashrc .bash_profile
ln -snf productivity/runcoms/vimrc  .vimrc
ln -snf productivity/runcoms/tmuxrc .tmux.conf


##===----------------------------------------------------------------------===##

