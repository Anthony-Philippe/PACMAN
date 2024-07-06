// Button.cpp
#include "Button.h"

Button::Button(SDL_Renderer* renderer, const std::string& text, int x, int y, int w, int h) : renderer(renderer){
    rect = {x, y, w, h};

    TTF_Font* font = TTF_OpenFont("../assets/fonts/namco.ttf", 200);
    if (!font){
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Button::~Button(){
    SDL_DestroyTexture(texture);
}

void Button::render(){
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Button::isClicked(int mouseX, int mouseY){
    return mouseX > rect.x && mouseX < rect.x + rect.w && mouseY > rect.y && mouseY < rect.y + rect.h;
}
