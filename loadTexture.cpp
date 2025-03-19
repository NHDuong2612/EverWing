#include "loadTexture.h"
#include <iostream>

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        std::cout << "Không thể tải hình ảnh! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void renderScore(SDL_Renderer* renderer, int score) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    const int blockSize = 10;
    const int blocksPerRow = 50;
    for (int i = 0; i < score / 10; ++i) {
        int x = 10 + (i % blocksPerRow) * (blockSize + 5);
        int y = 10 + (i / blocksPerRow) * (blockSize + 5);
        SDL_Rect scoreBlock = {x, y, blockSize, blockSize};
        SDL_RenderFillRect(renderer, &scoreBlock);
    }
}

