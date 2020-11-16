CXX = g++
CFLAGS = -O2 -std=c++11 -pedantic -Wall
LFLAGS = -lSDL2 -lSDL2_gfx

gfx: main.cpp scene.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f gfx
