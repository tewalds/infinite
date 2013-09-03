.PHONY: clean fresh

CPPFLAGS	+= -O3 -funroll-loops -Wall -march=native

all: infinite

infinite: infinite.o

infinite.o: infinite.cpp bitcount.h time.h xorshift.h

clean:
	rm -f infinite *.o

fresh: clean all
