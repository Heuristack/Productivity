OS = $(shell uname)

ifeq ($(OS), Darwin)
CC = clang
WARN = -Weverything
else ifeq ($(OS), Linux)
CC = gcc -std=gnu99
WARN = -Wall
endif
NOWARN = -w
AR = ar cru
CFLAGS = $(NOWARN)

ALGO = $(ALGO_HOME)/algo

