##############################################
# TITLE: Makefile for
# AUTHOR: LiYing
# DATE:
# NOTE:
##############################################

# make 									# make the first target found in the makefile
# make -n 								# display, not run
# make -p -f /dev/null 2>/dev/null		# view the contents of the built-in rules
# make -j10 							# use make in parallel mode with maximum of 10 parallel mode
# make -q								# returns a zero status code if the target file is up-to-date

# $@									# the file name of the target
# $%									# the target member name when the target is an archive memeber
# $<									# the name of the first prerequisite
# $?									# the name of all the prereqs newer than the target
# $^ 									# the name of all the prereqs with space between them (without duplicates)
# $+									# the name of all the prereqs with space between them (with duplicates)
# $*									# the sterm with which an implicit rule matches


string = "hello world!!"

hello: ; @echo $(string)
	@echo $(string)

