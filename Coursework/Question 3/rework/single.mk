CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: single

single: single.o beggar.o riffle.o
	$(CC) $(CFLAGS) -o $@ $^

single.o: single.c
	$(CC) $(CFLAGS) -c $<

beggar.o: beggar.c
	$(CC) $(CFLAGS) -c $<

riffle.o: riffle.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o single
