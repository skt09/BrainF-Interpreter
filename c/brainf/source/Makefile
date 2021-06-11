
CC=gcc

CFLAGS=-Ofast

brain: *.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o brain
