CC=gcc
CFLAGS=-Wall
LDFLAGS=$(shell sdl-config --libs) -lSDL_image
OBJDIR=Obj
EXEC=Robot.exe
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
HEADER=$(wildcard *.h)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf Obj/*.o *.o $(EXEC)

run: $(EXEC)
	./$(EXEC) appart.txt