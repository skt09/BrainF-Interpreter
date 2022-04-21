
CC=gcc

CFLAGS=-Ofast

brainf: *.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o brainf
