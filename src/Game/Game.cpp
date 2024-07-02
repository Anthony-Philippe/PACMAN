#include "Game.h"
#include "../Menu/Menu.h"
#include "../Menu/OptionsMenu.h"
#include <iostream>
#include <filesystem>

std::string getProjectRoot(){
    return std::filesystem::current_path().parent_path().parent_path().string();
}

Game::Game() : isRunning(false), showMainMenu(true), window(nullptr), renderer(nullptr), backgroundTexture(nullptr),
               menu(nullptr), optionsMenu(nullptr){}


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

    if (TTF_Init() == -1){
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
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

    menu = new Menu(renderer);
    if (!menu->init()){
        std::cerr << "Menu initialization failed" << std::endl;
        return false;
    }

    optionsMenu = new OptionsMenu(renderer);
    if (!optionsMenu->init()){
        std::cerr << "OptionsMenu initialization failed" << std::endl;
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
    if (showMainMenu){
        menu->handleEvents(isRunning, showMainMenu);
    }
    else{
        optionsMenu->handleEvents(isRunning, showMainMenu);
    }
}

void Game::update(){
    // Update game logic here
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    if (showMainMenu){
        menu->render();
    }
    else{
        optionsMenu->render();
    }
    SDL_RenderPresent(renderer);
}


void Game::clean(){
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    if (menu) delete menu;
    if (optionsMenu) delete optionsMenu;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
