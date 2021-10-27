#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MULTIPLIER 10

bool prev[9 * MULTIPLIER][16 * MULTIPLIER];
bool rend[9 * MULTIPLIER][16 * MULTIPLIER];

const int edge = SCREEN_WIDTH / (16 * MULTIPLIER);

void calculate();
void render();
void applyrules(int x, int y);
void fill(std::ifstream* stream);

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int main(int argc, char **argv) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Couldn't initialize SDL_Video: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream ifile("input.txt");
    fill(&ifile);

    window = SDL_CreateWindow(
            "Conway's Game of Life", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    bool exit = false;
    int mouseX = 0, mouseY = 0;
    Uint64 timer = 0;
    Uint64 prevTimer = SDL_GetTicks();
    Uint32 deltaTime = 0;
    Uint32 counter = 0;
    bool buttondown = false;
    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                exit = true;
            }
            if( e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState( &mouseX, &mouseY );
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                buttondown = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                buttondown = false;
            }
        }

        if (buttondown) {
            rend[mouseY / edge][mouseX / edge] = 1;
        }
        
        SDL_SetRenderDrawColor(renderer, 0xEF, 0xEF, 0xEF, 0xFF);
        if (counter >= 125) {
            counter = 0;
            SDL_RenderClear(renderer);
            render();
            calculate();
        }
        SDL_RenderPresent(renderer);

        
        prevTimer = timer;
        timer = SDL_GetTicks();
        deltaTime = timer - prevTimer;
        counter += deltaTime;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
    return EXIT_SUCCESS;
}

void calculate() {
    for (int i = 0; i < 9 * MULTIPLIER; i++) {
        for (int j = 0; j < 16 * MULTIPLIER; j++) {
            applyrules(j, i);
        }
    }
}

void render() {
    SDL_Rect rect = {0, 0, edge, edge};
    for (int i = 0; i < 9 * MULTIPLIER; i++) {
        for (int j = 0; j < 16 * MULTIPLIER; j++) {
            if (rend[i][j] == 0) {
                continue;
            }
            rect.x = j * edge;
            rect.y = i * edge;
            SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x80, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    for (int i = 0; i < 9 * MULTIPLIER; i++) {
        for (int j = 0; j < 16 * MULTIPLIER; j++) {
            prev[i][j] = rend[i][j];
        }
    }
}

void fill(std::ifstream* stream) {
    for (int i = 0; i < 9 * MULTIPLIER; i++) {
        for (int j = 0; j < 16 * MULTIPLIER; j++) {
            prev[i][j] = 0;
            rend[i][j] = 0;
        }
    }

    std::string temp;
    for (int i = 0; i < 9 * MULTIPLIER; i++) {
        std::getline(*stream, temp);
        for (int j = 0; j < 16 * MULTIPLIER; j++) {
            rend[i][j] = (temp[j]) - ((int)'0');
        }
        temp.clear();
    }
}

void applyrules(int x, int y) {
    int lifes = 0;
    int istart = -1, jstart = -1, istop = 1, jstop = 1;
    if(y == 0) {
        istart = 0;
    }
    if (x == 0) {
        jstart = 0;
    }
    if (y == 9 * MULTIPLIER - 1) {
        istop = 0;
    }
    if (x == 16 * MULTIPLIER - 1) {
        jstop = 0;
    }
    for (int i = istart; i <= istop; i++) {
        for (int j = jstart; j <= jstop; j++) {
            if (j == 0 && i == 0) {
                continue;
            }
            if (prev[y + i][x + j] == 1) {
                lifes++;
            }
        }
    }
    if (lifes >= 4 || lifes <= 1) {
        rend[y][x] = 0;
    }
    if (lifes == 3) {
        rend[y][x] = 1;
    }
}