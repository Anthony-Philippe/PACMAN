#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
};

#endif //GAME_H
