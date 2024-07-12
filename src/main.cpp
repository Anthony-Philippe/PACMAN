#include <SDL2/SDL.h>
#include <iostream>
#include "Map/Map.h"

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Pacman Map", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window){
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Map map(renderer);
    if (!map.loadMap("Map/map.txt")){
        std::cerr << "Failed to load map" << std::endl;
    }

    bool isRunning = true;
    SDL_Event event;
    while (isRunning){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
        }

        SDL_RenderClear(renderer);
        map.render();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
