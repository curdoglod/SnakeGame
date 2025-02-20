UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    CC = clang++
    CFLAGS = -std=c++17 -Iinclude -IGameLib/include -I/opt/homebrew/include `sdl2-config --cflags` `pkg-config --cflags SDL2_ttf SDL2_image`
else
    CC = g++
    CFLAGS = -std=c++17 -Iinclude -IGameLib/include `sdl2-config --cflags` `pkg-config --cflags SDL2_ttf SDL2_image`
endif

LIB_NAME = libGameLib.a
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
AR = ar rcs

.PHONY: all clean

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(LIB_NAME)