
CC = g++
OBJS = benchmark.o
FLAGS = -fopenmp
SEQFLAGS = -O3 

EXEC = test 

all: $(EXEC)

test: main.cpp benchmark.o
	$(CC) -o test main.cpp $(OBJS) 

benchmark.o: benchmark.cpp
	$(CC) -o $@ -c benchmark.cpp

clean:
	rm -f $(EXEC) $(OBJS)
