#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <cmath>

void handlePlayerInput(const Uint8* keys) {
    if (keys[SDL_SCANCODE_LEFT] && playerX > 0) playerX -= PLAYER_SPEED;
    if (keys[SDL_SCANCODE_RIGHT] && playerX < 800 - 70) playerX += PLAYER_SPEED;
    if (keys[SDL_SCANCODE_UP] && playerY > 0) playerY -= PLAYER_SPEED;
    if (keys[SDL_SCANCODE_DOWN] && playerY < 600 - 70) playerY += PLAYER_SPEED;
}

void playerShoot(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && canShoot) {
            Mix_PlayChannel(-1, soundEffect, 0);
            int spacing = BULLET_SIZE + 5;
            int totalWidth = BULLET_QUANTITY * spacing - spacing;
            int startX = playerX + (70 / 2) - (totalWidth / 2) - (BULLET_SIZE / 2);
            for (int i = 0; i < BULLET_QUANTITY; i++) {
                bullets.push_back({startX + i * spacing, playerY, BULLET_QUANTITY});
                }
                canShoot = false;
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                canShoot = true;
            }
        }
}

void updatePlayerBullets() {
    for (auto& bullet : bullets) bullet.y -= BULLET_SPEED;
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                  [](Bullet& b) { return b.y < 0; }),
                  bullets.end());
}

void renderPlayer(SDL_Renderer* renderer) {
    SDL_Rect playerRect = {playerX, playerY, 70, 70};
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

    for (const auto& bullet : bullets) {
        SDL_Rect b = {bullet.x, bullet.y, BULLET_SIZE, 3 * BULLET_SIZE};
        SDL_RenderCopy(renderer, currentBulletTexture, NULL, &b);
    }
}

