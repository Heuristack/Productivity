include $(ALGO_HOME)/Makefile

MAIN = sorting_test
MAIN = matrix_test
MAIN = threed_test
MAIN = dice_test
MAIN = heap_test
main: $(MAIN)

homedir = .
sources = $(basename $(notdir $(wildcard $(homedir)/*_test.c)))
exepost = .exe
exepost =
objects = $(addsuffix $(exepost), $(sources))

LIBS = -lsorting -lmatrix -lprob -lcomb -ladts

all: $(objects)

%$(exepost): %.c
	$(CC) $(CFLAGS) -I$(ALGO) -I$(ALGO_INCLUDE) $< -o $@ -L$(ALGO) $(LIBS)

.PHONY: clean

clean:
	rm -rf *.o *_test

test:
	sorting_test < ../data/sort.txt
	matrix_test
	threed_test ../data/trid.txt
	dice_test
	heap_test
	queue_test
	stack_test
	pqueue_test
	permutation_test
	perm_test
	comb_test
