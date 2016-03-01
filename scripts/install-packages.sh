#!/bin/bash
##===----------------------------------------------------------------------===##
#
#
#                  package list: libraries and utilities
#
#
##===----------------------------------------------------------------------===##

package_manager=brew
package_list+=(boost)

##==
#
# update list
#
##==
$package_manager update

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

