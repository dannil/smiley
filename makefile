CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=src/*.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=smiley

all: $(SOURCES) $(EXECUTABLE)

clean :
	rm -f $(objects) $(EXECUTABLE)

.PHONY: all clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
