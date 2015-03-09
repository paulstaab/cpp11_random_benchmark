CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -O3 -std=c++11 -march=native
LDFLAGS=-g
LDLIBS=

SRCS=benchmark.cc fastfunc.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: benchmark

benchmark: $(OBJS)
	    g++ $(LDFLAGS) -o benchmark $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	    rm -f ./.depend
		    $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	    $(RM) $(OBJS)

dist-clean: clean
	    $(RM) *~ .dependtool

include .depend
