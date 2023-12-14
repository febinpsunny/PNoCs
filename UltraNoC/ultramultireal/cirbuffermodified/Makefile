
CC = g++
OBJS = circularbuffer.o
FLAGS = -fopenmp
SEQFLAGS = -O3 

EXEC = test 

all: $(EXEC)

test: main.cpp circularbuffer.o
	$(CC) -o test main.cpp $(OBJS) 

circularbuffer.o: circularbuffer.cpp
	$(CC) -o $@ -c circularbuffer.cpp

clean:
	rm -f $(EXEC) $(OBJS)
