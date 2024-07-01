#include <iostream>
#include "./Game/Game.h"

using namespace std;

int main(){
    Game game;

    if (!game.init("PACMAN", 1366, 768)){
        cout << "Failed to initialize game!" << endl;
        return -1;
    }

    game.run();

    return 0;
}
