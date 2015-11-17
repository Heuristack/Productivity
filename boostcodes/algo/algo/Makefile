include $(ALGO_HOME)/Makefile

MAIN = libadts.a
main: $(MAIN)

homedir = .
objpost = .o

sortingsources = $(basename $(notdir $(wildcard $(homedir)/sorting*.c)))
sortingobjects = $(addsuffix $(objpost), $(sortingsources))

stacksources = $(basename $(notdir $(wildcard $(homedir)/stack*.c)))
stackobjects = $(addsuffix $(objpost), $(stacksources))
queuesources = $(basename $(notdir $(wildcard $(homedir)/queue*.c)))
queueobjects = $(addsuffix $(objpost), $(queuesources))
pqueuesources = $(basename $(notdir $(wildcard $(homedir)/priority_queue*.c)))
pqueueobjects = $(addsuffix $(objpost), $(pqueuesources))
heapsources = $(basename $(notdir $(wildcard $(homedir)/heap*.c)))
heapobjects = $(addsuffix $(objpost), $(heapsources))

permsources = $(basename $(notdir $(wildcard $(homedir)/perm*.c)))
permobjects = $(addsuffix $(objpost), $(permsources))
combsources = $(basename $(notdir $(wildcard $(homedir)/comb*.c)))
combobjects = $(addsuffix $(objpost), $(combsources))

matrixsources = $(basename $(notdir $(wildcard $(homedir)/matrix*.c)))
matrixobjects = $(addsuffix $(objpost), $(matrixsources))

probsources = $(basename $(notdir $(wildcard $(homedir)/prob*.c)))
probobjects = $(addsuffix $(objpost), $(probsources))



LIBS = libadts.a libsorting.a libmatrix.a libcomb.a libprob.a
all: $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libadts.a: $(stackobjects) $(queueobjects) $(pqueueobjects) $(heapobjects)
	$(AR) $@ $^

libsorting.a: $(sortingobjects)
	$(AR) $@ $^

libmatrix.a: $(matrixobjects)
	$(AR) $@ $^

libcomb.a: $(combobjects) $(permobjects)
	$(AR) $@ $^

libprob.a: $(probobjects)
	$(AR) $@ $^


.PHONY: clean

clean:
	rm -rf *.o *.a
