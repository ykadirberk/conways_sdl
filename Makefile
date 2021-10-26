OBJS = ./src/*.cpp
CC = g++
INCLUDE_PATHS = -I"C:\SDL2\developer\include\SDL2"
LIBRARY_PATHS = -L"C:\SDL2\developer\lib"
#COMPILER_FLAGS = -w -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
OBJ_NAME = ./release/app
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)