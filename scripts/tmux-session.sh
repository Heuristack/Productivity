#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                        tmux session shortcut helper
#
#
##===----------------------------------------------------------------------===##


##==
#
# Function : tmux session shortcut helper function
#
##==
function tmux_session()
{
    session=$1
    F10=$2

    if [ "$session" == "" ]; then session="t"; fi
    if [ "$F10" == "" ]; then F10="mac"; fi
    tmux has-session -t "$session" &> /dev/null

    if [ "$?" != "0" ]; then 
        tmux new -s $session -n $F10
    else 
        tmux attach -t $session; 
    fi
}

##==
#
# Program Name: 
#
##==
prog_name=$(basename "$0")
host_name=$(hostname -s)
tmux_session $prog_name $host_name

##===----------------------------------------------------------------------===##

