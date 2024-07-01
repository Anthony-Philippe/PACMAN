#include "Game.h"
#include <iostream>

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr), backgroundTexture(nullptr){}

Game::~Game(){
    clean();
}

bool Game::init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)){
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Surface* bgSurface = IMG_Load("../assets/images/HOME_bg.jpg");
    if (bgSurface == nullptr){
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    if (backgroundTexture == nullptr){
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void Game::run(){
    while (isRunning){
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            isRunning = false;
        }
    }
}

void Game::update(){
    // Update game logic here
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
