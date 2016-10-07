#Makefile!

CPP = clang++
CPPFLAGS = -std=c++11 -O2 -Wall

DEBUG = -g
LDFLAGS = -L lib/ -ltcod -ltcodxx -Wl,-rpath=lib/
INCLUDES = -I include/

all: main

main: 
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) src/*.cpp 

debug:
	$(CPP) $(DEBUG) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) src/*.cpp 

clean:
	$(RM) a.out
