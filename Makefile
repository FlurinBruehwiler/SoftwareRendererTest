CC=gcc
CFLAGS=-I"C:\Programming\mingw_dev_lib\include\SDL2"
LDFLAGS=-LC:\Programming\mingw_dev_lib\lib -lmingw32 -lSDL2main -lSDL2

SOURCES=main.c renderer.c renderer.h structs.h math.c math.h
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm -f $(EXECUTABLE)
