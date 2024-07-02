#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Menu{
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    bool init();
    void render();
    void handleEvents(bool& isRunning, bool& showMainMenu);

private:
    SDL_Renderer* renderer;
    SDL_Texture* newGameButtonTexture;
    SDL_Texture* optionsButtonTexture;
    SDL_Texture* quitButtonTexture;
    SDL_Texture* titleTexture;

    SDL_Rect newGameButtonRect;
    SDL_Rect optionsButtonRect;
    SDL_Rect quitButtonRect;
    SDL_Rect titleRect;

    void renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect, int x,
                    int y);
    std::string getProjectRoot();
};

#endif
