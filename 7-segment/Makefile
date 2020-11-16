CXX = g++
CFLAGS = -O2 -std=c++11 -pedantic -Wall
LFLAGS = -lSDL2 -lSDL2_gfx

segment: main.cpp scene.cpp 7segment.c encode7.c
	$(CXX) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f segment
