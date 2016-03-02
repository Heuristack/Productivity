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
# apt
#
##==
cat /etc/apt/sources.list

##==
#
# boost library
#
##==
package_list+=(libboost-all-dev)

##==
#
# lttng tools, modules, and ust
#
##==
package_list+=(lttng-modules-dkms)
package_list+=(liblttng-ust-dev)
package_list+=(lttng-tools)

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

