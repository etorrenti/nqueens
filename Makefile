CC=gcc
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=src/nqueens.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=nqueens
LIBS= -lgaul -lgaul_util -lm

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm $(OBJECTS) $(EXECUTABLE)

.c.o:
	$(CC) $(CFLAGS) $< -o $@