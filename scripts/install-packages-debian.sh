#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                  package list: libraries and utilities
#
#
##===----------------------------------------------------------------------===##

package_manager=apt-get

##==
#
# boost library
#
##==
package_list+=(libboost-all-dev)

##==
#
# install packages
#
##==
for package in ${package_list[@]}
do
    $package_manager install $package
done


##===----------------------------------------------------------------------===##

