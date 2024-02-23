CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: buffer.o producer_consumer.o
      $(CC) $(CFLAGS) -o pc buffer.o producer_consumer.o $(PTHREADS)
producer_consumer.o: producer_consumer.c
      $(CC) $(CFLAGS) -c producer_consumer.c $(PTHREADS)
buffer.o: buffer.c buffer.h
      $(CC) $(CFLAGS) -c buffer.c $(PTHREADS)
clean:
      rm -rf *.o
      rm -rf pc
