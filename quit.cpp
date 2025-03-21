#include "quit.h"
#include "information.h"

void quit(){
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(currentBulletTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemiesTexture);
    SDL_DestroyTexture(upgradeTexture);
    SDL_DestroyTexture(bossBulletTexture);
    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(bossTexture[i]);
    }
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(bulletTextures[i]);
    }
    Mix_HaltMusic();
    Mix_FreeMusic(bgMusic);
    Mix_FreeChunk(soundEffect);
    Mix_FreeChunk(boomEffect);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
