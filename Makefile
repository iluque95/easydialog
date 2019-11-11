CC=gcc
CXX=g++-5
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)A

CPPFLAGS=-Wall -ansi -lesin #-std=c++11

PROGRAM=main

SRCS=$(PROGRAM).cpp
OBJS=$(subst .cpp,.o,$(SRCS))

DIRS=build

$(shell mkdir -p $(DIRS))

all: $(PROGRAM).e

$(PROGRAM).e: $(OBJS)
	$(CXX) -o build/$(PROGRAM).e build/$(OBJS)

$(PROGRAM).o: 
	$(CXX) -Wall -g -c $(PROGRAM).cpp -o build/$(PROGRAM).o

phone: $(PROGRAM).o
	$(CXX) -c src/phone.cpp -o build/phone.o
	$(CXX) -o build/phone.e build/main.o build/phone.o $(CPPFLAGS)

clean:
	$(RM) build/$(OBJS)

distclean: clean
	$(RM) build/$(PROGRAM).e