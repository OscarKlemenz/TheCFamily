CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: byn

byn: byn.o beggar.o riffle.o
	$(CC) $(CFLAGS) -o $@ $^

byn.o: byn.c
	$(CC) $(CFLAGS) -c $<

beggar.o: beggar.c
	$(CC) $(CFLAGS) -c $<

riffle.o: riffle.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o byn