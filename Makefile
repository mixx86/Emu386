CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude

TARGET = build/Emu386

OBJ = build/main.o build/args.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/args.o: src/args.c
	$(CC) $(CFLAGS) -c src/args.c -o build/args.o

clean:
	rm -rf build

.PHONY: all clean
