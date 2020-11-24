CXX = g++
CXXFLAGS = -O2 -std=c++11 -pedantic -Wall -msse4
LFLAGS = -lSDL2 -lSDL2_gfx

box: main.cpp scene.cpp matrix4x4s.c print_sse.c
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f box
