CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -O3 -std=c++11
LDFLAGS=-g
LDLIBS=

SRCS=mersenne_twister.cc fastfunc.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: tool

tool: $(OBJS)
	    g++ $(LDFLAGS) -o tool $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	    rm -f ./.depend
		    $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	    $(RM) $(OBJS)

dist-clean: clean
	    $(RM) *~ .dependtool

include .depend
