#include <iostream>
#include <fstream>
#include <SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MULTIPLIER 10

int prev[16 * MULTIPLIER][9 * MULTIPLIER];
int render[16 * MULTIPLIER][9 * MULTIPLIER];

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Couldn't initialize SDL_Video: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(
            "Conway's Game of Life", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    bool exit = false;
    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                exit = true;
            }
        }

        SDL_Delay(100);
    }
    return EXIT_SUCCESS;
}