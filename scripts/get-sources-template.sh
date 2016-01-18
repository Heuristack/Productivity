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
syncat=
origin=
target=$origin

##==
#
# function to remote synchronize a source tree to proper place
#
##==
function get_remote_sources_sync()
{
    tree=$1

    options+=" --verbose"
    options+=" --archive"
    options+=" --recursive"
    options+=" --update"

    rsync $options $userid@$remote:$syncat/$origin/$tree $target
}

##==
#
# synchronize the 'tree' by calling the function above
#
##==
# get_remote_sources_sync  tree
##==

##===----------------------------------------------------------------------===##

