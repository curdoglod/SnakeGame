CC = g++
CFLAGS = -std=c++17 -Iinclude -IGameLib/include `sdl2-config --cflags` `pkg-config --cflags SDL2_ttf SDL2_image`
LIBS = -LGameLib -lGameLib `sdl2-config --libs` `pkg-config --libs SDL2_ttf SDL2_image`
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: GameLib/libGameLib.a $(TARGET) clean

GameLib/libGameLib.a:
	cd GameLib && make

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o
	cd GameLib && make clean

re: clean all

.PHONY: all clean
