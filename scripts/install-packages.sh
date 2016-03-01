#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                  package list: libraries and utilities
#
#
##===----------------------------------------------------------------------===##

package_manager=brew

##==
#
# boost
#
##==
package_list+=(boost)

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

