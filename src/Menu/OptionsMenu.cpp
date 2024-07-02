#include "OptionsMenu.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>

OptionsMenu::OptionsMenu(SDL_Renderer* renderer) : renderer(renderer), gameRulesButtonTexture(nullptr),
                                                   statisticsButtonTexture(nullptr), howToPlayButtonTexture(nullptr),
                                                   backButtonTexture(nullptr){}

OptionsMenu::~OptionsMenu(){
    if (gameRulesButtonTexture) SDL_DestroyTexture(gameRulesButtonTexture);
    if (statisticsButtonTexture) SDL_DestroyTexture(statisticsButtonTexture);
    if (howToPlayButtonTexture) SDL_DestroyTexture(howToPlayButtonTexture);
    if (backButtonTexture) SDL_DestroyTexture(backButtonTexture);
}

bool OptionsMenu::init(){
    TTF_Font* font = TTF_OpenFont((getProjectRoot() + "/assets/fonts/namco.ttf").c_str(), 24);
    if (!font){
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Color white = {255, 255, 255};

    int windowWidth = 1366;
    int windowHeight = 768;

    renderText("Games rules", font, white, &gameRulesButtonTexture, &gameRulesButtonRect, windowWidth / 2,
               windowHeight / 2 - 75);
    renderText("Statistics", font, white, &statisticsButtonTexture, &statisticsButtonRect, windowWidth / 2,
               windowHeight / 2 - 25);
    renderText("How to play", font, white, &howToPlayButtonTexture, &howToPlayButtonRect, windowWidth / 2,
               windowHeight / 2 + 25);
    renderText("Back", font, white, &backButtonTexture, &backButtonRect, windowWidth / 2, windowHeight / 2 + 75);

    TTF_CloseFont(font);

    return true;
}

void OptionsMenu::render(){
    SDL_RenderCopy(renderer, gameRulesButtonTexture, nullptr, &gameRulesButtonRect);
    SDL_RenderCopy(renderer, statisticsButtonTexture, nullptr, &statisticsButtonRect);
    SDL_RenderCopy(renderer, howToPlayButtonTexture, nullptr, &howToPlayButtonRect);
    SDL_RenderCopy(renderer, backButtonTexture, nullptr, &backButtonRect);
}

void OptionsMenu::handleEvents(bool& isRunning, bool& showMainMenu){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            isRunning = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= gameRulesButtonRect.x && x <= gameRulesButtonRect.x + gameRulesButtonRect.w &&
                y >= gameRulesButtonRect.y && y <= gameRulesButtonRect.y + gameRulesButtonRect.h){
                std::cout << "Games rules button clicked" << std::endl;
            }
            if (x >= statisticsButtonRect.x && x <= statisticsButtonRect.x + statisticsButtonRect.w &&
                y >= statisticsButtonRect.y && y <= statisticsButtonRect.y + statisticsButtonRect.h){
                std::cout << "Statistics button clicked" << std::endl;
            }
            if (x >= howToPlayButtonRect.x && x <= howToPlayButtonRect.x + howToPlayButtonRect.w &&
                y >= howToPlayButtonRect.y && y <= howToPlayButtonRect.y + howToPlayButtonRect.h){
                std::cout << "How to play button clicked" << std::endl;
            }
            if (x >= backButtonRect.x && x <= backButtonRect.x + backButtonRect.w &&
                y >= backButtonRect.y && y <= backButtonRect.y + backButtonRect.h){
                std::cout << "Back button clicked" << std::endl;
                showMainMenu = true; // Update to show the main menu
            }
        }
    }
}

void OptionsMenu::renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect,
                             int x, int y){
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->w = surface->w;
    rect->h = surface->h;
    rect->x = x - rect->w / 2;
    rect->y = y - rect->h / 2;
    SDL_FreeSurface(surface);
}

std::string OptionsMenu::getProjectRoot(){
    return std::filesystem::current_path().parent_path().string();
}
