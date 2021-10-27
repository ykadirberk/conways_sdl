FIRST_POS = ./src/*.cpp
INCLUDE_DIR = -I"C:\SDL2\developer\include\SDL2"
COMPILER_INST = -std=c++11 -Os #these things try to make the program smaller
STATIC_LINKING = -w -Wl,-subsystem,windows -static-libstdc++ -static-libgcc -Wl,-Bstatic -static -lstdc++ -lpthread -Wl,-Bdynamic
OBJECTS_POS = *.o
DESTINATION_POS =./release/app
LIBRARY_DIR = -L"C:\SDL2\developer\lib"
LINKING_INST = -lmingw32 -lSDL2main -lSDL2 -ldxguid
all: $(FIRST_POS)
	g++ -c $(FIRST_POS) $(INCLUDE_DIR) $(COMPILER_INST)
	g++  $(OBJECTS_POS) -g -o $(DESTINATION_POS) $(LIBRARY_DIR) $(STATIC_LINKING) $(LINKING_INST)
	del $(OBJECTS_POS)