
CC = gcc
OBJS = timer.o
FLAGS = -fopenmp
SEQFLAGS = -O3 

EXEC = knapSeq 

all: $(EXEC)

knapSeq: knap.c timer.o
	$(CC)  $(SEQFLAGS) -o knapSeq knap.c $(OBJS) 

timer.o: timer.c
	$(CC) -o $@ -c timer.c

clean:
	rm -f $(EXEC) $(OBJS)
