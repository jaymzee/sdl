CXX = g++
CFLAGS = -O2 -std=c++11 -pedantic -Wall
LFLAGS = -lSDL2 -lSDL2_ttf

heart2: main.cpp scene.cpp text.c
	$(CXX) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f heart2
