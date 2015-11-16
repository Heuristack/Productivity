#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#
#
#
##===----------------------------------------------------------------------===##



##==
#
# build directory hierarchy
#
##==
mkdir -p $HOME/Local/bin
mkdir -p $HOME/Local/etc
mkdir -p $HOME/Local/usr
mkdir -p $HOME/Local/usr/bin
mkdir -p $HOME/Local/usr/include
mkdir -p $HOME/Local/usr/lib
mkdir -p $HOME/Local/usr/share

mkdir -p $HOME/Repositories
mkdir -p $HOME/Projects

mkdir -p $HOME/Archive
mkdir -p $HOME/Downloads
mkdir -p $HOME/Temp

##==
#
# build symbolic links
#
##==
ln -snf $HOME/productivity/runcoms/bashrc $HOME/.bash_profile
ln -snf $HOME/productivity/runcoms/vimrc  $HOME/.vimrc
ln -snf $HOME/productivity/runcoms/tmuxrc $HOME/.tmux.conf


##===----------------------------------------------------------------------===##

