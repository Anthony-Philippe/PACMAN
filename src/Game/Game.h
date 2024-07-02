#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../Menu/Menu.h"
#include "../Menu/OptionsMenu.h"

class Game{
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:
    bool isRunning;
    bool showMainMenu;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    Menu* menu;
    OptionsMenu* optionsMenu;
};

#endif // GAME_H
