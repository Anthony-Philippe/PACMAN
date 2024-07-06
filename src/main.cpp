#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "./Entity/Ghost.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool initSDL(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Ghost Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr){
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr){
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

void closeSDL(){
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

int main(){
    if (!initSDL()){
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    // Créer un fantôme à une position initiale
    Ghost ghost(gRenderer, "../assets/sprites/spritesheet.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    bool quit = false;
    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }

        // Mettre à jour la direction du fantôme
        ghost.updateDirection();

        // Mettre à jour le mouvement du fantôme
        ghost.move();

        // Effacer l'écran
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        // Rendre le fantôme
        ghost.render();

        // Mettre à jour l'affichage
        SDL_RenderPresent(gRenderer);
    }

    closeSDL();
    return 0;
}
