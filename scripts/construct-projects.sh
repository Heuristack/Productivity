#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                         construct projects
#
#
##===----------------------------------------------------------------------===##
cd $PJ_HOME

##==
#
# construct "integration" clion project
#
##==
project_name=integration
project_type=clion
project=$project_name.$project_type
if [ -d $project ]; then echo "already exist: $project_name"; exit; fi
mkdir $project && cd $project
ln -snf $PD_HOME/cmakelists/$project_name-cmakelists.txt cmakelists.txt
ln -snf $PD_HOME/samples samples
ln -snf $PD_HOME/snippets snippets
ln -snf $PD_HOME/codebase codebase
ln -snf $PD_HOME/boostcodes boostcodes
cd - &> /dev/null

##===----------------------------------------------------------------------===##

