#include "game.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    initGame();

    SDL_Event event;
    while (menu) {
        showMenu(renderer, menuTexture, menu, running);

        if (running) {
            gameLoop();
            running = false;
        }
        startGame();
    }

    cleanupGame();
    return 0;
}
