CC=gcc
CFLAGS=
LDFLAGS=$(shell sdl-config --libs) -lSDL_image
OBJDIR=Obj
EXEC=Robot.exe
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c 
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -rf Obj/*.o *.o $(EXEC)

run: $(EXEC)
	./$(EXEC) appart.txt