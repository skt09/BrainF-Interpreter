
CC=gcc

CFLAGS=-Ofast

LFLAGS=-lm

brain: *.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ $(LFLAGS)

clean:
	rm *.o brain
