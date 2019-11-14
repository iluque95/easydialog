CXX=g++-5
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)A

CPPFLAGS=-Wall -ansi -lesin #-std=c++11

PROGRAM=main

SRCS=$(PROGRAM).cpp src/phone.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

DIRS=build

$(shell mkdir -p $(DIRS))

all: $(PROGRAM).e phone clean
	
$(PROGRAM).e: $(OBJS)
	$(CXX) -o build/$(PROGRAM).e build/$(OBJS) $(CPPFLAGS)

$(PROGRAM).o: 
	$(CXX) -Wall -g -c $(PROGRAM).cpp -o build/$(PROGRAM).o

phone:
	@echo Compiling $@ ... 
	$(CXX) -c src/phone.cpp -o build/phone.o
	$(CXX) -c phone.cpp -o build/phone_main.o
	$(CXX) -o build/phone.e build/phone_main.o build/phone.o $(CPPFLAGS)
	$(RM) build/*.o
	@echo OK!

clean:
	$(RM) build/*.o

distclean: clean
	$(RM) build/$(PROGRAM).e