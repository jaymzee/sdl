CC = gcc
CFLAGS = -I/usr/include/lua5.2 -Wall
LFLAGS = -llua5.2 -lSDL2 -lSDL2_ttf

demo : main.c draw.c lua.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
