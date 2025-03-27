CC = gcc
TARGET = build/chippy
CFLAGS = $(shell sdl2-config --cflags) -Wall -g
LDFLAGS = $(shell sdl2-config --libs)
SRCS = src/main.c src/load_rom.c src/instructions/ins_clear_screen.c
OBJS = build/main.o build/load_rom.o build/instructions/ins_clear_screen.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)