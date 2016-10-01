#Makefile!

CPP = clang++
CPPFLAGS = -std=c++11 -O2 -Wall

DEBUG = -g
LDFLAGS = -ltcod -ltcodxx
INCLUDES = -I include/

all: main

main: 
	$(CPP) $(DEBUG) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) src/*.cpp 

clean:
	$(RM) a.out
