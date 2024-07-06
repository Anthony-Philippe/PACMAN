// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Button.h"

enum class MenuState{
    MAIN_MENU,
    OPTIONS_MENU,
    HOW_TO_PLAY,
    RULES,
    STATS
};

class Menu{
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void render();
    void handleEvent(SDL_Event& e);

    bool isRunning() const;
    bool isLeaveSelected() const;

    MenuState getState() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* backgroundTexture;
    std::vector<Button*> mainMenuButtons;
    std::vector<Button*> optionsMenuButtons;
    bool running;
    bool leaveSelected;
    MenuState state;

    void initTitles();
    SDL_Texture* TitleTexture;
    SDL_Texture* loadTexture(const std::string& path);

    void renderMainMenu();
    void renderOptionsMenu();
    void renderHowToPlay();
    void renderRules();
    void renderStats();

    void handleMainMenuEvent(SDL_Event& e);
    void handleOptionsMenuEvent(SDL_Event& e);
};

#endif
