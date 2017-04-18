CC=g++
CFLAGS=-c -I/usr/include/SDL2 -std=c++17 -Wall
LDFLAGS= -lfltk -lfltk_images
SOURCES= $(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)


all: a.out

a.out:$(OBJECTS)
	$(CC) $(LDFLAGS) -o a.out $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm *.o
	rm a.out