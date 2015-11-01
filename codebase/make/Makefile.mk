##===----------------------------------------------------------------------===##
#
#
#                            General Makefile  
#
#
##===----------------------------------------------------------------------===##
OS = $(shell uname)

ifeq ($(OS), Darwin)
C89 = clang -std=c89
C99 = clang -std=c99
C98 = clang++ -std=c++98
C11 = clang++ -std=c++11 -stdlib=libc++
WRN = -Weverything
else ifeq ($(OS), Linux)
C89 = gcc
C99 = gcc -std=gnu99
C98 = g++
C11 = g++
WRN = -Wall
endif

CFLAGS = $(WRN)


sourcehome = .
exepostfix = .exe
exepostfix =

sourcelist89 = $(basename $(notdir $(wildcard $(sourcehome)/*.c)))
executable89 = $(addsuffix $(exepostfix), $(sourcelist89))

sourcelist98 = $(basename $(notdir $(wildcard $(sourcehome)/*.cc)))
executable98 = $(addsuffix $(exepostfix), $(sourcelist98))

sourcelist11 = $(basename $(notdir $(wildcard $(sourcehome)/*.cpp)))
executable11 = $(addsuffix $(exepostfix), $(sourcelist11))


MAIN =
main: $(MAIN)

all: $(executable89) $(executable98) $(executable11)


%$(exepostfix): %.c
	$(C89) $(CFLAGS) -o $@ $<

%$(exepostfix): %.cc
	$(C98) $(CFLAGS) -o $@ $<

%$(exepostfix): %.cpp
	$(C11) $(CFLAGS) -o $@ $<


.PHONY: clean test

clean:
	rm -rf $(executable89) $(executable98) $(executable11)

test:
	$(MAIN)

##===----------------------------------------------------------------------===##

