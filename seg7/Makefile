CXX = g++
CFLAGS = -O2 -std=c++11 -pedantic -Wall
LFLAGS = -lSDL2 -lSDL2_gfx

seg7: main.cpp scene.cpp seg7.c seg7enc.c
	$(CXX) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f seg7
