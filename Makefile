CXX=g++-5
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)A

CPPFLAGS=-Wall -ansi -lesin -std=c++11 -g

PROGRAM=main

SRCS=$(PROGRAM).cpp src/phone.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

DIRS=build

$(shell mkdir -p $(DIRS))

all: $(PROGRAM).e phone call_registry clean
	
$(PROGRAM).e: $(OBJS)
	$(CXX) -o build/$(PROGRAM).e build/$(OBJS) $(CPPFLAGS)

$(PROGRAM).o: 
	$(CXX) -Wall -g -c $(PROGRAM).cpp -o build/$(PROGRAM).o $(CPPFLAGS)

phone:
	@echo Compiling $@ ... 
	$(CXX) -c src/phone.cpp -o build/phone.o $(CPPFLAGS)
	$(CXX) -c phone_test.cpp -o build/phone_main.o $(CPPFLAGS)
	$(CXX) -o build/phone.e build/phone_main.o build/phone.o $(CPPFLAGS)
	$(RM) build/*.o
	@echo OK!

call_registry:
	@echo Compiling $@ ...
	$(CXX) -c src/phone.cpp -o build/phone.o $(CPPFLAGS) 
	$(CXX) -c src/call_registry.cpp -o build/call_registry.o $(CPPFLAGS)
	$(CXX) -c call_registry_test.cpp -o build/call_registry_main.o $(CPPFLAGS)
	$(CXX) -o build/call_registry.e build/call_registry_main.o build/call_registry.o build/phone.o $(CPPFLAGS)
	$(RM) build/*.o
	@echo OK!

clean:
	$(RM) build/*.o

distclean: clean
	$(RM) build/$(PROGRAM).e