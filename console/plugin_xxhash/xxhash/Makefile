
CC=g++
CFLAGS=
SOURCES=main.cpp xxhash.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hash


all:
	$(CC) $(SOURCES) -o $(EXECUTABLE)


install:
	cp ./hash ../bin/hash

clean:
	rm hash ../bin/hash *.o
