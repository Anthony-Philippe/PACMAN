#include "Ghost.h"

Ghost::Ghost(SDL_Renderer* renderer, const std::string& texturePath, int x, int y, int ghostType)
    : renderer(renderer), posX(x), posY(y), velX(0), velY(0), direction(UP), speed(2), ghostNumber(ghostType){
    std::random_device rd;
    mt = std::mt19937(rd());
    directionDistribution = std::uniform_int_distribution<int>(0, 3);

    texture = loadTexture(texturePath);
    if (!texture){
        std::cerr << "Failed to load texture!" << std::endl;
    }

    srcRect = {ghostNumber * 32, 64, 32, 32};
    dstRect = {posX, posY, 32, 32};
}

Ghost::~Ghost(){
    SDL_DestroyTexture(texture);
}

SDL_Texture* Ghost::loadTexture(const std::string& path){
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface){
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Ghost::render(){
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

void Ghost::move(){
    posX += velX;
    posY += velY;

    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX > 800 - dstRect.w) posX = 800 - dstRect.w;
    if (posY > 600 - dstRect.h) posY = 600 - dstRect.h;

    dstRect.x = posX;
    dstRect.y = posY;

    updateTexture();

    if (rand() % 100 < 2){
        // 2% chance to change direction
        changeDirection();
    }
}

void Ghost::setSpeed(int newSpeed){
    speed = newSpeed;

    if (velX > 0) velX = speed;
    else if (velX < 0) velX = -speed;
    if (velY > 0) velY = speed;
    else if (velY < 0) velY = -speed;
}

void Ghost::updateTexture(){
    switch (direction){
    case RIGHT: srcRect.y = 160;
        break;
    case LEFT: srcRect.y = 128;
        break;
    case UP: srcRect.y = 64;
        break;
    case DOWN: srcRect.y = 96;
        break;
    }
}

void Ghost::changeDirection(){
    int newDirection = directionDistribution(mt);
    switch (newDirection){
    case 0: direction = RIGHT;
        velX = speed;
        velY = 0;
        break;
    case 1: direction = LEFT;
        velX = -speed;
        velY = 0;
        break;
    case 2: direction = UP;
        velX = 0;
        velY = -speed;
        break;
    case 3: direction = DOWN;
        velX = 0;
        velY = speed;
        break;
    }
}
