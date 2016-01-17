#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#        template to get remote sources to local building environment
#
#
##===----------------------------------------------------------------------===##
cd $HOME

##==
#
# parameters to specify remote host, remote place and local place
#
##==
userid=
remote=
origin=
target=

##==
#
# function to remote synchronize a source tree to proper place
#
##==
function get_remote_sources_syn()
{
    tree=$1
    rsync $userid@$remote:$origin/$tree $target
}

##==
#
# synchronize the 'tree' by calling the function above
#
##==
# get_remote_sources_syn tree

##===----------------------------------------------------------------------===##

