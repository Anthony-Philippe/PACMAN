// Menu.cpp
#include "Menu.h"

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer), running(true), leaveSelected(false),
                                     state(MenuState::MAIN_MENU){
    backgroundTexture = loadTexture("../assets/images/background.jpg");
    if (!backgroundTexture){
        std::cerr << "Failed to load background texture!" << std::endl;
        running = false;
    }

    constexpr int w = 1280, h = 720;

    mainMenuButtons.push_back(new Button(renderer, "new game", w / 2 - 200, h / 2 + 125, 400, 50));
    mainMenuButtons.push_back(new Button(renderer, "options", w / 2 - 175, h / 2 + 200, 350, 50));
    mainMenuButtons.push_back(new Button(renderer, "quit", w - 175 - 65, h - 80, 125, 40));

    optionsMenuButtons.push_back(new Button(renderer, "rules", w / 2 - 137, h / 2 + 100, 225, 40));
    optionsMenuButtons.push_back(new Button(renderer, "settings", w / 2 - 150, h / 2 + 165, 250, 40));
    optionsMenuButtons.push_back(new Button(renderer, "stats", w / 2 - 137, h / 2 + 235, 225, 40));
    optionsMenuButtons.push_back(new Button(renderer, "back", w - 200, h - 80, 150, 40));

    TitleTexture = loadTexture("../assets/images/title.png");
}

Menu::~Menu(){
    for (auto button : mainMenuButtons){
        delete button;
    }
    for (auto button : optionsMenuButtons){
        delete button;
    }
    SDL_DestroyTexture(TitleTexture);
}

SDL_Texture* Menu::loadTexture(const std::string& path){
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface){
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Menu::render(){
    SDL_RenderClear(renderer);
    if (backgroundTexture){
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    }

    if (TitleTexture){
        SDL_Rect dstRect = {1280 / 2 - 275, 720 / 8, 550, 125};
        SDL_RenderCopy(renderer, TitleTexture, nullptr, &dstRect);
    }

    switch (state){
    case MenuState::MAIN_MENU:
        renderMainMenu();
        break;
    case MenuState::NEW_GAME:
        // renderNewGame();
        break;
    case MenuState::OPTIONS_MENU:
        renderOptionsMenu();
        break;
    case MenuState::HOW_TO_PLAY:
        renderHowToPlay();
        break;
    case MenuState::RULES:
        renderRules();
        break;
    case MenuState::STATS:
        renderStats();
        break;
    }

    SDL_RenderPresent(renderer);
}

void Menu::handleEvent(SDL_Event& e){
    switch (state){
    case MenuState::MAIN_MENU:
        handleMainMenuEvent(e);
        break;
    case MenuState::OPTIONS_MENU:
        handleOptionsMenuEvent(e);
        break;
    case MenuState::HOW_TO_PLAY:
    case MenuState::RULES:
    case MenuState::STATS:
        if (e.type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (optionsMenuButtons[3]->isClicked(x, y)){
                state = MenuState::OPTIONS_MENU;
            }
        }
        break;
    }
}

void Menu::renderMainMenu(){
    for (auto button : mainMenuButtons){
        button->render();
    }
}

void Menu::renderNewGame(){
    // Placeholder
}

void Menu::renderOptionsMenu(){
    for (auto button : optionsMenuButtons){
        button->render();
    }
}

void Menu::renderHowToPlay(){
    optionsMenuButtons[3]->render();
}

void Menu::renderRules(){
    optionsMenuButtons[3]->render();
}

void Menu::renderStats(){
    optionsMenuButtons[3]->render();
}

void Menu::handleMainMenuEvent(SDL_Event& e){
    if (e.type == SDL_QUIT){
        running = false;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (mainMenuButtons[0]->isClicked(x, y)){
            state = MenuState::NEW_GAME;
        }
        else if (mainMenuButtons[1]->isClicked(x, y)){
            state = MenuState::OPTIONS_MENU;
        }
        else if (mainMenuButtons[2]->isClicked(x, y)){
            leaveSelected = true;
            running = false;
        }
    }
}

void Menu::handleOptionsMenuEvent(SDL_Event& e){
    if (e.type == SDL_QUIT){
        running = false;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (optionsMenuButtons[0]->isClicked(x, y)){
            state = MenuState::HOW_TO_PLAY;
        }
        else if (optionsMenuButtons[1]->isClicked(x, y)){
            state = MenuState::RULES;
        }
        else if (optionsMenuButtons[2]->isClicked(x, y)){
            state = MenuState::STATS;
        }
        else if (optionsMenuButtons[3]->isClicked(x, y)){
            state = MenuState::MAIN_MENU;
        }
    }
}

bool Menu::isRunning() const{
    return running;
}

bool Menu::isLeaveSelected() const{
    return leaveSelected;
}

MenuState Menu::getState() const{
    return state;
}
