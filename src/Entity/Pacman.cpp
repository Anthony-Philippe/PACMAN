#include "Pacman.h"

Pacman::Pacman(SDL_Renderer* renderer, const std::string& texturePath, int x, int y)
    : renderer(renderer), posX(x), posY(y), velX(0), velY(0) {

    texture = loadTexture(texturePath);
    if (!texture) {
        std::cerr << "Failed to load texture!" << std::endl;
    }

    srcRect = { 0, 0, 32, 32 }; // Assume Pac-Man sprite is 32x32 pixels
    dstRect = { posX, posY, 32, 32 };
}

Pacman::~Pacman() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Pacman::loadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Pacman::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP: velY -= 5; break;
        case SDLK_DOWN: velY += 5; break;
        case SDLK_LEFT: velX -= 5; break;
        case SDLK_RIGHT: velX += 5; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP: velY += 5; break;
        case SDLK_DOWN: velY -= 5; break;
        case SDLK_LEFT: velX += 5; break;
        case SDLK_RIGHT: velX -= 5; break;
        }
    }
}

void Pacman::move() {
    posX += velX;
    posY += velY;
    dstRect.x = posX;
    dstRect.y = posY;
}

void Pacman::render() {
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}