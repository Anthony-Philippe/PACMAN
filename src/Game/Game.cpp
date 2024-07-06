// Game.cpp
#include "Game.h"

Game::Game() : window(nullptr), renderer(nullptr), menu(nullptr), running(false){}

Game::~Game(){
    clean();
}

bool Game::init(const std::string& title, int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1){
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_SHOWN);
    if (!window){
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer){
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    menu = new Menu(renderer);
    running = true;

    return true;
}

void Game::run(){
    while (running && menu->isRunning()){
        handleEvents();
        update();
        render();
    }

    if (menu->isLeaveSelected()){
        running = false;
    }
}

void Game::clean(){
    delete menu;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Game::handleEvents(){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        menu->handleEvent(e);
    }
}

void Game::update(){
    // Update game state
}

void Game::render(){
    menu->render();
}
