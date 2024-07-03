#include "Menu.h"
#include <iostream>
#include <filesystem>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), newGameButtonTexture(nullptr), optionsButtonTexture(nullptr),
                                     quitButtonTexture(nullptr), titleTexture(nullptr){}

Menu::~Menu(){
    if (newGameButtonTexture) SDL_DestroyTexture(newGameButtonTexture);
    if (optionsButtonTexture) SDL_DestroyTexture(optionsButtonTexture);
    if (quitButtonTexture) SDL_DestroyTexture(quitButtonTexture);
    if (titleTexture) SDL_DestroyTexture(titleTexture);
}

bool Menu::init(){
    TTF_Font* font = TTF_OpenFont((getProjectRoot() + "/assets/fonts/namco.ttf").c_str(), 24);
    if (!font){
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Color white = {255, 255, 255};

    int windowWidth = 1366;
    int windowHeight = 768;

    renderText("new game", font, white, &newGameButtonTexture, &newGameButtonRect, windowWidth / 2,
               windowHeight / 2);
    renderText("options", font, white, &optionsButtonTexture, &optionsButtonRect, windowWidth / 2,
               windowHeight / 2 + 50);
    renderText("quit", font, white, &quitButtonTexture, &quitButtonRect, windowWidth / 2, windowHeight / 2 + 100);

    TTF_CloseFont(font);

    TTF_Font* titleFont = TTF_OpenFont((getProjectRoot() + "/assets/fonts/crackman.ttf").c_str(), 64);
    if (!titleFont){
        std::cerr << "Failed to load title font: " << TTF_GetError() << std::endl;
        return false;
    }

    renderText("PAC-MAN", titleFont, white, &titleTexture, &titleRect, windowWidth / 2, 100);

    TTF_CloseFont(titleFont);

    return true;
}

void Menu::render(){
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
    SDL_RenderCopy(renderer, newGameButtonTexture, nullptr, &newGameButtonRect);
    SDL_RenderCopy(renderer, optionsButtonTexture, nullptr, &optionsButtonRect);
    SDL_RenderCopy(renderer, quitButtonTexture, nullptr, &quitButtonRect);
}

void Menu::handleEvents(bool& isRunning, bool& showMainMenu){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            isRunning = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= newGameButtonRect.x && x <= newGameButtonRect.x + newGameButtonRect.w &&
                y >= newGameButtonRect.y && y <= newGameButtonRect.y + newGameButtonRect.h){
                std::cout << "New game button clicked" << std::endl;
                // Logic for starting a new game
            }
            if (x >= optionsButtonRect.x && x <= optionsButtonRect.x + optionsButtonRect.w &&
                y >= optionsButtonRect.y && y <= optionsButtonRect.y + optionsButtonRect.h){
                std::cout << "Options button clicked" << std::endl;
                showMainMenu = false; // Update to show the options menu
            }
            if (x >= quitButtonRect.x && x <= quitButtonRect.x + quitButtonRect.w &&
                y >= quitButtonRect.y && y <= quitButtonRect.y + quitButtonRect.h){
                std::cout << "Quit button clicked" << std::endl;
                isRunning = false;
            }
        }
    }
}

void Menu::renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect, int x,
                      int y){
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->w = surface->w;
    rect->h = surface->h;
    rect->x = x - rect->w / 2;
    rect->y = y - rect->h / 2;
    SDL_FreeSurface(surface);
}

std::string Menu::getProjectRoot(){
    return std::filesystem::current_path().parent_path().string();
}
