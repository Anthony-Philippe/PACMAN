#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include <string>

class Pacman{
public:
    Pacman(SDL_Renderer* renderer, const std::string& texturePath, int x, int y);
    ~Pacman();

    void handleEvent(SDL_Event& e);
    void move();
    void render();
    void setSpeed(int speed);

private:
    SDL_Texture* loadTexture(const std::string& path);
    void updateTexture();

    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect srcRect, dstRect;
    int posX, posY;
    int prevPosX, prevPosY;
    int velX, velY;
    int speed;

    enum Direction{ RIGHT, LEFT, UP, DOWN } direction;

    bool mouthOpen;
    int frameCounter;
    const int frameDelay = 10;
};

#endif
