// Game.h
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Menu/Menu.h"

class Game{
public:
    Game();
    ~Game();

    bool init(const std::string& title, int width, int height);
    void run();
    void clean();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Menu* menu;
    bool running;

    void handleEvents();
    void update();
    void render();
};

#endif
