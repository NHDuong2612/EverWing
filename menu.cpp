#include "menu.h"
#include "information.h"

void showMenu(SDL_Renderer* renderer, SDL_Texture* menuTexture, bool& menu, bool& running) {
    SDL_Event e;
    while (menu && !running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                menu = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.x >= playButton.x && e.button.x <= playButton.x + playButton.w &&
                    e.button.y >= playButton.y && e.button.y <= playButton.y + playButton.h) {
                    running = true;
                }
            }
        }
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}
