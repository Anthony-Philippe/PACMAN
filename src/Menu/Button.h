// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Button{
public:
    Button(SDL_Renderer* renderer, const std::string& text, int x, int y, int w, int h);
    ~Button();

    void render();
    bool isClicked(int mouseX, int mouseY);

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Color textColor = {255, 255, 255, 255};
};

#endif
