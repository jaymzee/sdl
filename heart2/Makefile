CXX = g++
CFLAGS = -O2 -std=c++17 -pedantic -Wall
LFLAGS = -lSDL2 -lSDL2_ttf

heart2: main.cpp scene.cpp text.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f heart2
