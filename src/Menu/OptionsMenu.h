#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class OptionsMenu{
public:
    OptionsMenu(SDL_Renderer* renderer);
    ~OptionsMenu();

    bool init();
    void render();
    void handleEvents(bool& isRunning, bool& showMainMenu);

private:
    SDL_Renderer* renderer;
    TTF_Font* buttonFont;
    SDL_Texture* gameRulesButtonTexture;
    SDL_Texture* statisticsButtonTexture;
    SDL_Texture* howToPlayButtonTexture;
    SDL_Texture* backButtonTexture;

    SDL_Rect gameRulesButtonRect;
    SDL_Rect statisticsButtonRect;
    SDL_Rect howToPlayButtonRect;
    SDL_Rect backButtonRect;

    void renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect, int x,
                    int y);
    std::string getProjectRoot();
};

#endif // OPTIONS_MENU_H
