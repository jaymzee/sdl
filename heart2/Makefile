CC = g++
CFLAGS = -O2 -std=c++17 -pedantic -Wall
LFLAGS = -lSDL2 -lSDL2_ttf
OBJS = heart2

all: $(OBJS)

heart2: main.cpp scene.cpp text.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o $(OBJS)
