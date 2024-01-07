CC=gcc
CFLAGS=-Wall -g
LIBS=-lgdi32

all: your_app

your_app: main.o
	$(CC) $(CFLAGS) -o your_app main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f your_app main.o
