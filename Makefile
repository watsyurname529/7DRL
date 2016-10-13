#Makefile!

CPP = clang++
CPPFLAGS = -std=c++11 -O2 -Wall

DEBUG = -g -DDEBUG=1
LDFLAGS = -L lib/ -ltcod -ltcodxx -Wl,-rpath=lib/
INCLUDES = -I include/

SOURCEDIR = src
BUILDDIR = build
EXECUTABLE = a.out

SOURCES = src/engine.cpp src/generate_bsp.cpp src/generate_cellular.cpp src/main.cpp src/map.cpp src/object.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJECTS) -o $@ 

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

debug: CPPFLAGS += $(DEBUG)
debug: $(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)
